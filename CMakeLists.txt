cmake_minimum_required(VERSION 2.8)
project(ProtoTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(SOURCE_FILES main.cpp)
add_executable(ProtoTest ${SOURCE_FILES})

set(OpenCV_STATIC ON)
find_package(OpenCV COMPONENTS core highgui REQUIRED)

link_directories(/usr/local/lib /usr/local/crowdsight/lib /usr/lib/x86_64-linux-gnu)
include_directories(include /usr/local/include /usr/include /usr/local/crowdsight/include)
target_link_libraries(ProtoTest ${OpenCV_LIBS}  crowdsight)
