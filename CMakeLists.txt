cmake_minimum_required(VERSION 3.5)
project(poop)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Subtitle.h Subtitle.cpp mvtime.cpp mvtime.h SubtitleIO.cpp SubtitleIO.h SubtitleApp.h SubtitleApp.cpp Subtitles.cpp Subtitles.h)
add_executable(poop ${SOURCE_FILES})