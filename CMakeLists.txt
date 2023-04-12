cmake_minimum_required(VERSION 3.22.0)
project(top_10_imdb VERSION 0.1.0)

add_subdirectory(lib/utils)

add_executable(top_10_imdb src/main.cpp)
target_link_libraries(top_10_imdb utils)