cmake_minimum_required(VERSION 2.8...3.13)
project(tp)
set(SOURCE_FILE tp.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

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

target_compile_options(tp PUBLIC -O2 -Wall -Wextra)

install(TARGETS tp
        DESTINATION /usr/local/bin)
