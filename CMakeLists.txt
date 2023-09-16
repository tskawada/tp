cmake_minimum_required(VERSION 2.8.3)
project(step1)
set(SOURCE_FILE main.cpp)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(main
    ${SOURCE_FILE}
)

target_link_libraries(main
    ${OpenCV_LIBRARIES}
)