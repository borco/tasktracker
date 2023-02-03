set(URI_NAME ListViewOrdering)
set(APP_NAME ${URI_NAME}Demo)

qt_add_executable(${APP_NAME}
    main.cpp
)

qt_add_qml_module(${APP_NAME}
    URI ${URI_NAME}
    VERSION 1.0
    RESOURCE_PREFIX "/"
    QML_FILES
        PetDelegate.qml
        PetsModel.qml
        main.qml
)

qt_add_resources(${APP_NAME} "dut_icons"
    PREFIX /
    BASE ../../src/tasktracker/
    FILES
    ../../src/tasktracker/icons/task/drag.svg
)

set_target_properties(${APP_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER borco.tasktracker.playground.${URI_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${APP_NAME} PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)
