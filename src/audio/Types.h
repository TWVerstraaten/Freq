//
// Created by pc on 05-12-21.
//

#ifndef H_SRC_AUDIO_TYPES_H
#define H_SRC_AUDIO_TYPES_H

#include "CircularBuffer.h"
#include "LinearBuffer.h"

namespace audio {
    typedef LinearBuffer<float, 100>    DftBuffer;
    typedef CircularBuffer<float, 1500> HistoryBuffer;

} // namespace audio

#endif // H_SRC_AUDIO_TYPES_H
