//
// Created by pc on 05-11-21.
//

#ifndef H_APP_PLAYER_H
#define H_APP_PLAYER_H

#include "LinearBuffer.h"

#include <SFML/Audio.hpp>
#include <cassert>
#include <string>

namespace audio {

    class Player {

      public:
        typedef LinearBuffer<float> AudioBuffer;

        explicit Player(const std::string& path_to_file);

        void                       init(const std::string& path_to_file);
        void                       play();
        void                       pause();
        void                       play_or_pause();
        [[nodiscard]] bool         is_paused() const;
        [[nodiscard]] unsigned int max_intensity() const;
        [[nodiscard]] size_t       current_offset() const;
        [[nodiscard]] AudioBuffer  normalized_buffer() const;

      private:
        bool              m_is_paused = true;
        unsigned          m_max_intensity;
        size_t            m_samples_rate;
        sf::Sound         m_sound;
        sf::SoundBuffer   m_sound_buffer;
        mutable sf::Clock m_clock;
        mutable size_t    m_last_sfml_offset = 0;
    };

} // namespace audio

#endif // H_APP_PLAYER_H
