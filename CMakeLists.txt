cmake_minimum_required(VERSION 3.16)

project(toggltracktasks VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS
    Core
    Quick
    Qml
    REQUIRED
)

add_subdirectory(src/3rdparty/qtkeychain)
add_subdirectory(src/lib)
add_subdirectory(src/app)

# Directories where Qt Creator can find QML files.
# (Not needed for builds, but makes Qt Creator code completion happy.)
list(APPEND QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/src/lib")

# Prevent adding duplicate values at each run of CMake.
list(REMOVE_DUPLICATES QML_IMPORT_PATH)

set(QML_IMPORT_PATH
    "${QML_IMPORT_PATH}"
    CACHE STRING
    "Qt Creator extra qml import paths"
    FORCE
)
