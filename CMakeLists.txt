cmake_minimum_required(VERSION 3.16)

project(TogglTrackTasks VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS
    Quick
    REQUIRED
)

add_subdirectory(src/3rdparty/qtkeychain)
add_subdirectory(src/app)
