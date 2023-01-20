import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import TaskTrackerLib

import "pages"
import "Theme.js" as Theme

ApplicationWindow {
    id: root

    property bool inDarkMode: palette.text > palette.base
    property TaskListModel taskListModel: TaskListModel {}

    readonly property int wideLayoutTasksMinimumWidth: 360
    readonly property int wideLayoutCalendarMinimumWidth: 360
    readonly property int wideLayoutMinimumWidth: wideLayoutTasksMinimumWidth + wideLayoutCalendarMinimumWidth
    property bool useWideLayout: width >= wideLayoutMinimumWidth

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


    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        AppHeader {
            id: appHeader

            property string wideLayoutTitle: qsTr("Task Tracker")
            property string narrowLayoutTitle: ""

            title: useWideLayout ? wideLayoutTitle : narrowLayoutTitle
            Layout.fillWidth: true
            onConfigClicked: showConfigPage()
        }

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
                        header: appHeader
                        taskListModel: root.taskListModel
                        SplitView.minimumWidth: wideLayoutTasksMinimumWidth
                    }

                    CalendarPage {
                        title: qsTr("Calendar")
                        header: appHeader
                        taskListModel: root.taskListModel
                        clip: true
                        SplitView.minimumWidth: wideLayoutCalendarMinimumWidth
                    }
                }

                ColumnLayout {
                    visible: !useWideLayout
                    anchors.fill: parent
                    spacing: 0

                    StackLayout {
                        id: narrowStackLayout

                        currentIndex: mainTabBar.currentIndex

                        TasksPage {
                            title: qsTr("Tasks")
                            header: appHeader
                            taskListModel: root.taskListModel
                            StackLayout.onIsCurrentItemChanged: appHeader.narrowLayoutTitle = title
                        }

                        CalendarPage {
                            title: qsTr("Calendar")
                            header: appHeader
                            taskListModel: root.taskListModel
                            StackLayout.onIsCurrentItemChanged: appHeader.narrowLayoutTitle = title
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
        taskListModel.load(Config.dataFolderLocation)
        splitView.restoreState(settings.splitView)
        wideLayoutSplitView.restoreState(settings.wideLayoutSplitView)
    }

    Component.onDestruction: {
        taskListModel.save(Config.dataFolderLocation)
        settings.splitView = splitView.saveState()
        settings.wideLayoutSplitView = wideLayoutSplitView.saveState()
    }
}
