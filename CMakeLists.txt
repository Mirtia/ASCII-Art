cmake_minimum_required(VERSION 3.17.0)
project(ascii-art VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "--version: ${OpenCV_VERSION}")
message(STATUS "--libraries: ${OpenCV_LIBS}")
message(STATUS "--include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})
set(LIBS ${OpenCV_LIBS})

add_executable(${PROJECT_NAME} main.cpp ASCIIConverter.cpp ASCIIConverter.hpp util.hpp)
target_link_libraries(ascii-art ${LIBS})
