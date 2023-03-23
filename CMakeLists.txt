cmake_minimum_required(VERSION 3.22.0)
project(text_editor VERSION 0.1.0)

add_subdirectory(lib/utils)

add_executable(text_editor src/main.cpp)
target_link_libraries(text_editor utils)