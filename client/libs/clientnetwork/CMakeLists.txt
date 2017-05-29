if (NOT TARGET network)

    cmake_minimum_required(VERSION 3.7)
    project(clientnetwork)

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)

    include_directories(include)

    set(SOURCE_FILES include/data.h include/myclient.h source/data.cpp source/myclient.cpp test/test.cpp)

    find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

    add_library(clientnetwork STATIC ${SOURCE_FILES})
    qt5_use_modules(clientnetwork Core Widgets Gui Network)

    add_executable(test_clientnextwork ${SOURCE_FILES})
    qt5_use_modules(test_clientnextwork Core Widgets Gui Network)

    add_subdirectory(libs/localfilemanager)
    target_link_libraries(clientnetwork localfilemanager)
    target_link_libraries(test_clientnextwork localfilemanager)

endif()
