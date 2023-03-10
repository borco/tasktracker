cmake_minimum_required(VERSION 3.16)

project(tasktracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.6 REQUIRED COMPONENTS
    Core
    Quick
    QuickControls2
    Qml
    Test
)

set(QTIFW_VERSION "4.5") # Qt Installer Framework version
get_target_property(QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_QT_BIN_DIR_ "${QMAKE_EXECUTABLE}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_QT_BIN_DIR_}")
find_program(LINUXDEPLOY_EXECUTABLE linuxdeploy linuxdeploy-x86_64.AppImage HINTS "${_QT_BIN_DIR_}")
find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_QT_BIN_DIR_}")
find_program(CREATE_DMG_EXECUTABLE create-dmg)
find_program(BINARYCREATOR_EXECUTABLE binarycreator HINTS "${_QT_BIN_DIR_}/../../../Tools/QtInstallerFramework/${QTIFW_VERSION}/bin")

add_subdirectory(playground)
add_subdirectory(src)
add_subdirectory(tests)

# Directories where Qt Creator can find QML files.
# (Not needed for builds, but makes Qt Creator code completion happy.)
list(APPEND QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/src/tasktracker")
list(APPEND QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/src/tasktrackerlib")
list(APPEND QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/src/qtplogadapter")

# Prevent adding duplicate values at each run of CMake.
list(REMOVE_DUPLICATES QML_IMPORT_PATH)

set(QML_IMPORT_PATH
    "${QML_IMPORT_PATH}"
    CACHE STRING
    "Qt Creator extra qml import paths"
    FORCE
)
