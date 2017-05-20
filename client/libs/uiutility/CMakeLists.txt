cmake_minimum_required(VERSION 3.7)
project(utilities)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES)

if (NOT TARGET uiutilitylib)
    add_library(uiutilitylib STATIC ${SOURCE_FILES})
endif()
