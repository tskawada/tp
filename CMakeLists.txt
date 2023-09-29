cmake_minimum_required(VERSION 2.8.3)
project(step1)
set(SOURCE_FILE tp.cpp)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(tp
    ${SOURCE_FILE}
)

target_link_libraries(tp
    ${OpenCV_LIBRARIES}
)

target_compile_options(tp PUBLIC -O2 -Wall)