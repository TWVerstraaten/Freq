//
// Created by pc on 05-11-21.
//

#include "SoundWindow.h"

#include "Functions.h"
#include "Player.h"

#include <fftw3.h>

namespace audio {

    SoundWindow::SoundWindow() {
    }

    void SoundWindow::update(const audio::Player& player) {
        const auto buffer = player.normalized_buffer();
        float      result = 0;
        for (size_t j = 0; j < 512; j += 4) {
            result += buffer[j];
        }
        m_intensities.set(player.max_intensity() * result / (64.0f * std::numeric_limits<sf::Int16>::max()));
        auto                     complex_buffer = buffer.cast<Complex>(audio::float_to_complex());
        decltype(complex_buffer) out;
        fftw_plan                p;
        p = fftw_plan_dft_1d(
            BUFFER_SIZE, reinterpret_cast<fftw_complex*>(&complex_buffer.buffer()[0]), reinterpret_cast<fftw_complex*>(&out.buffer()[0]), FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(p);
        fftw_destroy_plan(p);

        m_dft_buffers.set({LinearBuffer(out.cast<float, DftBuffer::size>(audio::complex_to_dB()))});
        m_smoothed_dft_buffers.set(m_dft_buffers.average());

        handle_energy();
    }

    const HistoryBuffer& SoundWindow::intensities() const {
        return m_intensities;
    }

    void SoundWindow::clear() {
        assert(false);
        //        m_intensities.clear();
        //        m_dft_buffers.clear();
        //        m_beat_buffer.clear();
    }

    const HistoryBuffer& SoundWindow::energy_buffer() const {
        return m_energy_buffer;
    }

    const HistoryBuffer& SoundWindow::energy_dif_buffer() const {
        return m_energy_dif_buffer;
    }

    void SoundWindow::handle_energy() {
        const auto energy = m_smoothed_dft_buffers.last_set().energy();
        m_energy_buffer.set(energy);

        float average_energy = 0.0f;
        for (const auto& dft : m_smoothed_dft_buffers.data()) {
            average_energy += dft.energy();
        }
        average_energy = average_energy / DftBuffer::size;
        m_energy_dif_buffer.set(energy > average_energy ? energy / average_energy : 0.0f);
        if (m_energy_dif_buffer.last_set() > m_energy_dif_buffer.look_back(1) && m_energy_dif_buffer.look_back(1) > 0.0f) {
            m_energy_dif_dif_buffer.set(m_energy_dif_buffer.last_set() / m_energy_dif_buffer.look_back(1) - 1.0f);
        } else {
            m_energy_dif_dif_buffer.set(0);
        }
    }

    const CircularBuffer<DftBuffer, 64>& SoundWindow::smoothed_dft_buffers() const {
        return m_smoothed_dft_buffers;
    }

    const HistoryBuffer& SoundWindow::energy_dif_dif_buffer() const {
        return m_energy_dif_dif_buffer;
    }

} // namespace audio