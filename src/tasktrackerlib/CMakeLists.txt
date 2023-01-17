set(LIB_NAME TaskTrackerLib)

qt_add_library(${LIB_NAME}
    STATIC
)

qt_add_qml_module(${LIB_NAME}
    URI ${LIB_NAME}
    VERSION 1.0
    PLUGIN_TARGET ${LIB_NAME}Plugin
    RESOURCE_PREFIX "/"
    OUTPUT_DIRECTORY ${LIB_NAME}
    SOURCES
        config.cpp
        config.h
        foldercreator.cpp
        foldercreator.h
        folderlistmodel.cpp
        folderlistmodel.h
        task.cpp
        task.h
        taskevent.cpp
        taskevent.h
        tasklistfiltermodel.cpp
        tasklistfiltermodel.h
        tasklistmodel.cpp
        tasklistmodel.h
        taskschedulemode.cpp
        taskschedulemode.h
        tasktrackmode.cpp
        tasktrackmode.h
        togglproxy.cpp
        togglproxy.h
)

target_link_libraries(${LIB_NAME} PUBLIC
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    QtYamlCppAdapter
)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
