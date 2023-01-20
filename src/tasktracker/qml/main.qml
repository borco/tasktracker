import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import TaskTrackerLib

import "pages"

ApplicationWindow {
    id: root

    property bool inDarkMode: palette.text > palette.base
    property TaskListModel taskListModel: TaskListModel {}

    property string narrowLayoutTitle: ""

    readonly property int tasksPageMinimumWidth: 360
    readonly property int calendarPageMinimumWidth: 360

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
            title: root.title
            Layout.fillWidth: true
            onConfigClicked: configPopup.open()
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

                ThemedSplitView {
                    id: wideLayoutSplitView

                    visible: true
                    anchors.fill: parent

                    Item {
                        SplitView.minimumWidth: tasksPageMinimumWidth

                        TasksPage {
                            id: tasksPage
                            title: qsTr("Tasks")
                            header: appHeader
                            anchors.fill: parent
                            taskListModel: root.taskListModel
                        }
                    }

                    Item {
                        id: wideLayoutCalendarPagePlaceholder

                        clip: true
                        SplitView.minimumWidth: calendarPageMinimumWidth

                        CalendarPage {
                            id: calendarPage
                            title: qsTr("Calendar")
                            header: appHeader
                            anchors.fill: parent
                            taskListModel: root.taskListModel
                        }
                    }
                }

                ColumnLayout {
                    id: narrowLayoutColumnLayout

                    visible: false
                    anchors.fill: parent

                    spacing: 0

                    StackLayout {
                        id: narrowStackLayout

                        currentIndex: mainTabBar.currentIndex

                        Item {
                            id: narrowLayoutTasksPagePlaceholder
                            StackLayout.onIsCurrentItemChanged: narrowLayoutTitle = tasksPage.title
                        }

                        Item {
                            id: narrowLayoutCalendarPagePlaceholder
                            StackLayout.onIsCurrentItemChanged: narrowLayoutTitle = calendarPage.title
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

    StateGroup {
        states: State {
            when: width < tasksPageMinimumWidth + calendarPageMinimumWidth

            ParentChange {
                target: tasksPage
                parent: narrowLayoutTasksPagePlaceholder
            }

            ParentChange {
                target: calendarPage
                parent: narrowLayoutCalendarPagePlaceholder
            }

            PropertyChanges {
                appHeader.title: narrowLayoutTitle
                wideLayoutSplitView.visible: false
                narrowLayoutColumnLayout.visible: true
            }
        }
    }

    Settings {
        id: settings
        category: "Main"
        property var splitView
        property var wideLayoutSplitView
        property alias currentPageIndex: mainTabBar.currentIndex
        property alias archivedVisible: appHeader.archivedVisible
        property alias doneVisible: appHeader.doneVisible
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
