//
// Created by pc on 05-11-21.
//

#ifndef H_AUDIO_CIRCULARBUFFER_H
#define H_AUDIO_CIRCULARBUFFER_H

#include "BufferBase.h"

#include <array>
#include <cassert>
#include <numeric>
#include <vector>

namespace audio {

    template <typename T, size_t Size>
    class CircularBuffer : public BufferBase<T, Size> {

      public:
        void set(T t) {
            assert(m_index < Size);
            this->m_data[m_index] = t;
            ++m_index;
            m_index %= Size;
        }

        const T& look_back(size_t n) const {
            return this->m_data[(m_index + Size - n - 1) % Size];
        }

        const T& last_set() const {
            return look_back(0);
        }

        [[nodiscard]] const T& operator[](const size_t index) const {
            return this->m_data[(m_index + index + Size - 1) % Size];
        }

        [[nodiscard]] T& operator[](const size_t index) {
            return this->m_data[(m_index + index + Size - 1) % Size];
        }

        template <size_t N>
        CircularBuffer<T, Size - N> smoothed() const {
            CircularBuffer<T, Size - N> result;
            for (size_t i = 0; i != Size - N; ++i) {
                T r{};
                for (size_t j = 0; j != N; ++j) {
                    r += std::abs((*this)[i + j]);
                }
                result.set(r / N);
            }
            return result;
        }

      private:
        size_t m_index = 0;
    };

} // namespace audio

#endif // H_AUDIO_CIRCULARBUFFER_H
