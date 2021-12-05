cmake_minimum_required(VERSION 3.20)
project(freq)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -pthread")

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS window graphics audio)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

link_libraries(OpenGL::GL sfml-window sfml-graphics Qt5::Core Qt5::Widgets)

add_executable(freq src/main.cpp src/audio/Player.cpp src/audio/Player.h src/audio/LinearBuffer.h src/audio/CircularBuffer.h src/audio/SoundWindow.cpp src/audio/SoundWindow.h src/audio/Functions.h src/audio/Complex.h src/audio/BufferBase.h src/audio/Functions.cpp src/audio/Types.h src/disp/AudioWidget.cpp src/disp/AudioWidget.h src/disp/SpectrumWidget.cpp src/disp/SpectrumWidget.h src/disp/HistoryWidget.cpp src/disp/HistoryWidget.h src/disp/WidgetBase.cpp src/disp/WidgetBase.h src/disp/BeatWidget.cpp src/disp/BeatWidget.h)

target_link_libraries(freq fftw3 OpenGL::GL sfml-window sfml-graphics sfml-audio)