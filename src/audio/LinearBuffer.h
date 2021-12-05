//
// Created by pc on 05-11-21.
//

#ifndef H_AUDIO_LINEARBUFFER_H
#define H_AUDIO_LINEARBUFFER_H

#include "BufferBase.h"

#include <SFML/Config.hpp>
#include <array>
#include <cassert>
#include <functional>
#include <numeric>

namespace audio {

    static constexpr size_t BUFFER_SIZE = 1024;

    template <typename T, size_t Size = BUFFER_SIZE>
    class LinearBuffer : public BufferBase<T, Size> {

      public:
        LinearBuffer() = default;

        explicit LinearBuffer(const T* source, size_t length = Size) {
            assert(length <= Size);
            for (size_t i = 0; i != length; ++i) {
                this->m_data[i] = *(source + i);
            }
        }

        template <class S, size_t NewSize = Size>
        LinearBuffer<S, NewSize> cast(std::function<S(const T)> transform = [](const T t) { return S{t}; }) const {
            return LinearBuffer<S, NewSize>{static_cast<const T*>(this->m_data.data()), transform};
        }

        template <class S>
        explicit LinearBuffer(
            const S* source, std::function<T(const S)> transform = [](const S s) { return s; }, size_t length = Size) {
            assert(length <= Size);
            for (size_t i = 0; i != length; ++i) {
                this->m_data[i] = transform(*(source + i));
            }
            for (size_t i = length; i != Size; ++i) {
                this->m_data[i] = T{};
            }
        }

        [[nodiscard]] std::array<T, Size>& buffer() {
            return this->m_data;
        }

        [[nodiscard]] LinearBuffer<T, Size> operator+(const LinearBuffer<T, Size>& other) {
            LinearBuffer<T, Size> result(*this);
            for (size_t i = 0; i != Size; ++i) {
                result[i] += other[i];
            }
            return result;
        }

        [[nodiscard]] LinearBuffer<T, Size> operator/(float divider) {
            LinearBuffer<T, Size> result(*this);
            for (size_t i = 0; i != Size; ++i) {
                result[i] /= divider;
            }
            return result;
        }

        [[nodiscard]] const T& operator[](size_t index) const final {
            assert(index < Size);
            return this->m_data[index];
        }

        [[nodiscard]] T& operator[](size_t index) {
            assert(index < Size);
            return this->m_data[index];
        }
    };

} // namespace audio

#endif // H_AUDIO_LINEARBUFFER_H
