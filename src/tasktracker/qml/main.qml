import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import TaskTrackerLib

import "Theme.js" as Theme

ApplicationWindow {
    id: root

    property bool inDarkMode: palette.text > palette.base
    property TaskListModel taskListModel: TaskListModel {}

    function showConfigPage() {
        configPopup.open()
    }

    width: 640
    height: 480
    visible: true

    readonly property int wideLayoutTasksMinimumWidth: 360
    readonly property int wideLayoutCalendarMinimumWidth: 360
    readonly property int wideLayoutMinimumWidth: wideLayoutTasksMinimumWidth + wideLayoutCalendarMinimumWidth
    property bool useWideLayout: width >= wideLayoutMinimumWidth

    title: qsTr("Task Tracker")

    background: Rectangle {
        color: palette.window
    }

    ConfigPopup {
        id: configPopup
    }


    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ThemedSplitView {
            id: splitView

            Layout.fillHeight: true
            Layout.fillWidth: true

            orientation: Qt.Vertical

            Item {
                SplitView.minimumHeight: 200

                Layout.fillHeight: true
                Layout.fillWidth: true

                SplitView {
                    id: wideLayoutSplitView
                    visible: useWideLayout
                    anchors.fill: parent

                    TasksPage {
                        title: qsTr("Tasks")
                        taskListModel: root.taskListModel
                        SplitView.minimumWidth: wideLayoutTasksMinimumWidth
                        onShowConfig: showConfigPage()
                    }

                    CalendarPage {
                        title: qsTr("Calendar")
                        clip: true
                        taskListModel: root.taskListModel
                        SplitView.minimumWidth: wideLayoutCalendarMinimumWidth
                        onShowConfig: showConfigPage()
                    }
                }

                ColumnLayout {
                    visible: !useWideLayout
                    anchors.fill: parent
                    spacing: 0

                    StackLayout {
                        currentIndex: mainTabBar.currentIndex

                        TasksPage {
                            title: qsTr("Tasks")
                            taskListModel: root.taskListModel
                            onShowConfig: showConfigPage()
                        }

                        CalendarPage {
                            title: qsTr("Calendar")
                            taskListModel: root.taskListModel
                            onShowConfig: showConfigPage()
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        implicitHeight: 1
                        color: inDarkMode ? palette.light : palette.dark
                    }

                    TabBar {
                        id: mainTabBar
                        Layout.fillWidth: true
                        TabButton { icon.source: "../icons/tasks.svg" }
                        TabButton { icon.source: "../icons/calendar.svg" }
                    }
                }
            }

            Pane {
                visible: Config.logsVisible
                padding: 0

                LogsComponent {
                    anchors.fill: parent
                }
            }
        }
    }

    Settings {
        id: settings
        category: "Main"
        property var splitView
        property var wideLayoutSplitView
        property alias currentPageIndex: mainTabBar.currentIndex
    }

    Component.onCompleted: {
        splitView.restoreState(settings.splitView)
        wideLayoutSplitView.restoreState(settings.wideLayoutSplitView)
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
        settings.wideLayoutSplitView = wideLayoutSplitView.saveState()
    }
}
