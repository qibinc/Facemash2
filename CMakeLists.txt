cmake_minimum_required(VERSION 3.7)
project(Facemash2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(client)
add_subdirectory(server)
