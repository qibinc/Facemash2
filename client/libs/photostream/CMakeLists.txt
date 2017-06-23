if (NOT TARGET photostream)
    cmake_minimum_required(VERSION 3.7)
    project(photostream)

    set(CMAKE_CXX_STANDARD 11)

    set(SOURCE_FILES source/wechatstream.cpp include/wechatstream.h test/photostream_test.cpp)

    include_directories(include)
    add_library(photostream STATIC ${SOURCE_FILES})


    find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
    qt5_use_modules(photostream Core Widgets Gui)

    include_directories(${PYTHON_INCLUDE_DIR})
    target_link_libraries(photostream ${PYTHON_LIBRARIES})

    add_executable(photostream_test ${SOURCE_FILES})
    qt5_use_modules(photostream_test Core Widgets Gui)
    target_link_libraries(photostream_test ${PYTHON_LIBRARIES})

endif()