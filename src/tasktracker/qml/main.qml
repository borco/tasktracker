import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import TaskTrackerLib

import "Theme.js" as Theme

ApplicationWindow {
    id: root

    function showConfigPage() {
        configPopup.open()
    }

    width: 640
    height: 480
    visible: true

    title: qsTr("Task Tracker")

    background: Rectangle {
        color: palette.window
    }

    ConfigPopup {
        id: configPopup
    }

    Item {
        visible: false

        BusyIndicator {
            anchors.centerIn: parent
            running: true
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ThemedSplitView {
            id: splitView

            Layout.fillHeight: true
            Layout.fillWidth: true

            orientation: Qt.Vertical

            ColumnLayout {
                SplitView.minimumHeight: 200

                StackLayout {
                    currentIndex: mainTabBar.currentIndex

                    TasksPage {
                        title: qsTr("Tasks")
                        onShowConfig: showConfigPage()
                    }

                    CalendarPage {
                        title: qsTr("Calendar")
                        onShowConfig: showConfigPage()
                    }
                }

                TabBar {
                    id: mainTabBar
                    Layout.fillWidth: true
                    TabButton { icon.source: "../icons/tasks.svg" }
                    TabButton { icon.source: "../icons/calendar.svg" }
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
        property alias currentPageIndex: mainTabBar.currentIndex
    }

    Component.onCompleted: {
        splitView.restoreState(settings.splitView)
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
