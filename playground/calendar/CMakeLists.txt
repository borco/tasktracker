set(URI_NAME Calendar)
set(APP_NAME ${URI_NAME}Demo)

qt_add_executable(${APP_NAME}
    main.cpp
)

qt_add_qml_module(${APP_NAME}
    URI ${URI_NAME}
    VERSION 1.0
    RESOURCE_PREFIX "/"
    QML_FILES
    main.qml
)

qt_add_resources(${APP_NAME} "dut_qml"
    PREFIX ${URI_NAME}
    BASE ../../src/tasktracker/qml
    FILES
    ../../src/tasktracker/qml/BottomSeparator.qml
    ../../src/tasktracker/qml/CalendarPage.qml
    ../../src/tasktracker/qml/ConfigGroupTitle.qml
    ../../src/tasktracker/qml/PageHeader.qml
    ../../src/tasktracker/qml/Theme.js
    ../../src/tasktracker/qml/ThemedLabel.qml
    ../../src/tasktracker/qml/ThemedSmallLabel.qml
    ../../src/tasktracker/qml/ThemedToolButton.qml
    ../../src/tasktracker/qml/TogglLoggedStatus.qml
    ../../src/tasktracker/qml/WeekView.qml
)

qt_add_resources(${APP_NAME} "dut_icons"
    PREFIX /
    BASE ../../src/tasktracker/
    FILES
    ../../src/tasktracker/icons/archived.svg
    ../../src/tasktracker/icons/task/done.svg
    ../../src/tasktracker/icons/toggl.svg
    ../../src/tasktracker/icons/settings.svg
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
    QtPlogAdapter
    TaskTrackerLib
    TaskTrackerLibPlugin
)
