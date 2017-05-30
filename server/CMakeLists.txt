cmake_minimum_required(VERSION 3.7)
project(Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

include_directories(include libs/include)
set(SOURCE_FILES source/main.cpp source/PhotoManager.cpp source/Photo.cpp source/User.cpp source/UserManager.cpp source/ServerManager.cpp libs/tcp/data.cpp libs/tcp/myserver.cpp include/ServerManager.h include/UserManager.h include/PhotoManager.h include/User.h include/Photo.h libs/include/data.h libs/include/myserver.h include/ServerManager.h)

add_executable(Server ${SOURCE_FILES})

find_package(Qt5 COMPONENTS Core Widgets Gui Sql REQUIRED)

qt5_use_modules(Server Core Widgets Gui Sql Network)

#add_subdirectory(uiutility)
#include_directories(uiutility/include)
#target_link_libraries(server utilitieslib)
