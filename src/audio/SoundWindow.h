//
// Created by pc on 05-11-21.
//

#ifndef H_AUDIO_SOUNDWINDOW_H
#define H_AUDIO_SOUNDWINDOW_H

#include "Complex.h"
#include "CircularBuffer.h"
#include "LinearBuffer.h"
#include "Types.h"

#include <SFML/System/Clock.hpp>

namespace audio {

    class Player;

    class SoundWindow {

      public:
        SoundWindow();

        void                                               update(const Player& player);
        void                                               clear();
        [[nodiscard]] const HistoryBuffer&                 intensities() const;
        [[nodiscard]] const HistoryBuffer&                 energy_buffer() const;
        [[nodiscard]] const HistoryBuffer&                 energy_dif_buffer() const;
        [[nodiscard]] const HistoryBuffer&                 energy_dif_dif_buffer() const;
        [[nodiscard]] const CircularBuffer<DftBuffer, 64>& smoothed_dft_buffers() const;

      private:
        void handle_energy();

        HistoryBuffer                 m_intensities{};
        HistoryBuffer                 m_energy_buffer{};
        HistoryBuffer                 m_energy_dif_buffer{};
        HistoryBuffer                 m_energy_dif_dif_buffer{};
        CircularBuffer<DftBuffer, 10> m_dft_buffers{};
        CircularBuffer<DftBuffer, 64> m_smoothed_dft_buffers{};
    };

} // namespace audio

#endif // H_AUDIO_SOUNDWINDOW_H
