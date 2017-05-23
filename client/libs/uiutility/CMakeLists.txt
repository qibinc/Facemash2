cmake_minimum_required(VERSION 3.7)
project(utilities)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES source/clickablelabel.cpp include/clickablelabel.h source/photolabel.cpp include/photolabel.h source/photowindow.cpp include/photowindow.h source/photoeditmenu.cpp include/photoeditmenu.h)

if (NOT TARGET uiutilitylib)
    add_library(uiutilitylib STATIC ${SOURCE_FILES})
endif()

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
qt5_use_modules(uiutilitylib Core Widgets Gui)
