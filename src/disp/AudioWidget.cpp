//
// Created by pc on 08-11-21.
//

#include "AudioWidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QLabel>

namespace disp {

    AudioWidget::AudioWidget() : m_player("../songs/min.wav") {
        m_player.play();
        m_timer.start(1, this);

        m_layout           = new QFormLayout(this);
        m_wave_form_widget = new HistoryWidget(this, 200.0f, "Waveform");
        m_wave_form_widget->set_type(HistoryWidget::TYPE::POSITIVE_AND_NEGATIVE);
        m_spectrum_widget       = new SpectrumWidget(this);
        m_energy_widget         = new HistoryWidget(this, 0.005, "Energy");
        m_energy_dif_widget     = new HistoryWidget(this, 20.f, "d Energy");
        m_energy_dif_dif_widget = new HistoryWidget(this, 280.f, "d d Energy");
        m_energy_beat_widget    = new BeatWidget(this);
        m_layout->addRow(new QLabel{"Waveform", this}, m_wave_form_widget);
        m_layout->addRow(new QLabel{"Energy", this}, m_energy_widget);
        m_layout->addRow(new QLabel{"Energy Dif", this}, m_energy_dif_widget);
        m_layout->addRow(new QLabel{"Energy Dif Dif", this}, m_energy_dif_dif_widget);
        m_layout->addRow(new QLabel{"Spectrum", this}, m_spectrum_widget);
        m_layout->addRow(new QLabel{"Energy Beat", this}, m_energy_beat_widget);
        setLayout(m_layout);
        resize(800, 200);
    }

    void AudioWidget::keyPressEvent(QKeyEvent* e) {
        switch (e->key()) {
            case Qt::Key::Key_Space:
                m_player.play_or_pause();
            default:
                break;
        }
    }

    void AudioWidget::timerEvent([[maybe_unused]] QTimerEvent* e) {
        if (m_player.is_paused())
            return;

        m_sound_window.update(m_player);
        m_wave_form_widget->set_buffer(m_sound_window.intensities());
        m_spectrum_widget->set_buffer(m_sound_window.smoothed_dft_buffers().last_set());
        m_energy_widget->set_buffer(m_sound_window.energy_buffer());
        m_energy_dif_widget->set_buffer(m_sound_window.energy_dif_buffer());
        m_energy_dif_dif_widget->set_buffer(m_sound_window.energy_dif_dif_buffer());
        m_energy_beat_widget->set_beat_score(std::max(m_sound_window.energy_dif_buffer().last_set() / 7.0f, m_sound_window.energy_dif_dif_buffer().last_set() / 0.5f));
    }

} // namespace disp