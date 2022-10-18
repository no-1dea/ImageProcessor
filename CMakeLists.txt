cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        binary_io.cpp
        controller.cpp
        filters/abstract_matrix_filter.cpp
        filters/abstract_simple_filter.cpp
        filters/crop_filter.cpp
        filters/edge_detection_filter.cpp
        filters/gaussian_blur.cpp
        filters/gray_scale_filter.cpp
        filters/negative_filter.cpp
        filters/pixelization_effect_filter.cpp
        filters/sharpening_filter.cpp
        parser/parser.cpp
        picture.cpp)
