cmake_minimum_required(VERSION 3.7)
project(Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

include_directories(include)
set(SOURCE_FILES source/main.cpp)

add_executable(Server ${SOURCE_FILES})

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

qt5_use_modules(Server Core Widgets Gui)
#add_subdirectory(uiutility)
#include_directories(uiutility/include)
#target_link_libraries(Server utilitieslib)
