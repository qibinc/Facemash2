if (NOT TARGET uiutilitylib)
    cmake_minimum_required(VERSION 3.7)
    project(utilities)

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)

    include_directories(include)

    set(SOURCE_FILES source/clickablelabel.cpp include/clickablelabel.h source/photolabel.cpp include/photolabel.h source/photowindow.cpp include/photowindow.h source/photoeditmenu.cpp include/photoeditmenu.h source/starcheck.cpp include/starcheck.h include/starcheckbox.cpp include/starcheckbox.h)

    add_library(uiutilitylib STATIC ${SOURCE_FILES})
    find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
    qt5_use_modules(uiutilitylib Core Widgets Gui)

    add_subdirectory(libs/localfilemanager)
    include_directories(libs/localfilemanager/include)
    target_link_libraries(uiutilitylib localfilemanager)

endif()
