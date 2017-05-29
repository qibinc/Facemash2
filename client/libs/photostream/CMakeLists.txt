if (NOT TARGET photostream)
    cmake_minimum_required(VERSION 3.7)
    project(photostream)

    set(CMAKE_CXX_STANDARD 11)

    set(SOURCE_FILES source/wechatstream.cpp include/wechatstream.h test/photostream_test.cpp)

    include_directories(include)

    add_library(photostream STATIC ${SOURCE_FILES})


    find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
    qt5_use_modules(photostream Core Widgets Gui)

    target_link_libraries(photostream ${PYTHON_LIBRARIES})

    add_subdirectory(libs/uiutility)
    include_directories(libs/uiutility/include)
    target_link_libraries(photostream uiutilitylib)

    add_subdirectory(libs/localfilemanager)
    include_directories(libs/localfilemanager/include)
    target_link_libraries(photostream localfilemanager)

    add_executable(photostream_test ${SOURCE_FILES})
    qt5_use_modules(photostream_test Core Widgets Gui)
    target_link_libraries(photostream_test ${PYTHON_LIBRARIES})
    target_link_libraries(photostream_test uiutilitylib)
    target_link_libraries(photostream_test localfilemanager)

endif()