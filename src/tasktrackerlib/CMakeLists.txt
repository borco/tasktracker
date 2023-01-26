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
        datesortedlist.h
        daymodel.cpp
        daymodel.h
        foldercreator.cpp
        foldercreator.h
        foldermodel.cpp
        foldermodel.h
        mainwindow.cpp
        mainwindow.h
        task.cpp
        task.h
        taskaggregate.cpp
        taskaggregate.h
        taskcount.cpp
        taskcount.h
        taskduration.cpp
        taskduration.h
        taskdurationmodel.cpp
        taskdurationmodel.h
        taskdurationsortedlist.cpp
        taskdurationsortedlist.h
        taskfiltermodel.cpp
        taskfiltermodel.h
        taskmodel.cpp
        taskmodel.h
        tasktrack.cpp
        tasktrack.h
        togglproxy.cpp
        togglproxy.h
        weekmodel.cpp
        weekmodel.h
        yamlbackingstore.cpp
        yamlbackingstore.h
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
