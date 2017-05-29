if (NOT TARGET localfilemanager)

    cmake_minimum_required(VERSION 3.7)
    project(localfilemanager)

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)

    include_directories(include)

    set(SOURCE_FILES test/filemanager_test.cpp source/filescanner.cpp include/filescanner.h)

    add_library(localfilemanager STATIC ${SOURCE_FILES})
    find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
    qt5_use_modules(localfilemanager Core Widgets Gui)

    add_executable(filemanager_test ${SOURCE_FILES})
    qt5_use_modules(filemanager_test Core Widgets Gui)

endif()
