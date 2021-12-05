//
// Created by pc on 07-11-21.
//

#ifndef H_AUDIO_BUFFERBASE_H
#define H_AUDIO_BUFFERBASE_H

#include <array>
#include <numeric>

namespace audio {

    template <typename T, size_t Size>
    class BufferBase {

      public:
        static constexpr size_t size = Size;

        virtual const T& operator[](size_t index) const = 0;

        void clear() {
            m_data = {};
        }

        [[nodiscard]] T sum() const {
            if (Size == 0) {
                return T{};
            }
            return std::accumulate(this->m_data.begin(), this->m_data.end(), T{});
        }

        [[nodiscard]] T average() const {
            return sum() / Size;
        }

        [[nodiscard]] T energy() const {
            T result{};
            for (size_t i = 0; i != size; ++i) {
                result += std::abs(m_data[i]) * std::abs(m_data[i]);
            }
            return result;
        }

        [[nodiscard]] const std::array<T, size>& data() const {
            return m_data;
        }

      protected:
        std::array<T, Size> m_data;
    };

} // namespace audio

#endif // H_AUDIO_BUFFERBASE_H
