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

    property string narrowLayoutAppTitle: ""
    property string wideLayoutAppTitle: title

    readonly property int wideLayoutTasksMinimumWidth: 360
    readonly property int wideLayoutCalendarMinimumWidth: 360
    readonly property int wideLayoutMinimumWidth: wideLayoutTasksMinimumWidth + wideLayoutCalendarMinimumWidth

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

    TasksPage {
        id: tasksPage
        title: qsTr("Tasks")
        header: appHeader
        anchors.fill: parent
        taskListModel: root.taskListModel
    }

    CalendarPage {
        id: calendarPage
        title: qsTr("Calendar")
        header: appHeader
        anchors.fill: parent
        taskListModel: root.taskListModel
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        AppHeader {
            id: appHeader
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

                ThemedSplitView {
                    id: wideLayoutSplitView

                    visible: true
                    anchors.fill: parent

                    Item {
                        id: wideLayoutTasksPagePlaceholder
                        SplitView.minimumWidth: wideLayoutTasksMinimumWidth
                    }

                    Item {
                        id: wideLayoutCalendarPagePlaceholder
                        clip: true
                        SplitView.minimumWidth: wideLayoutCalendarMinimumWidth
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
                            StackLayout.onIsCurrentItemChanged: narrowLayoutAppTitle = tasksPage.title
                        }

                        Item {
                            id: narrowLayoutCalendarPagePlaceholder
                            StackLayout.onIsCurrentItemChanged: narrowLayoutAppTitle = calendarPage.title
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
        states: [
            State {
                name: "wideLayout"
                when: width >= wideLayoutMinimumWidth

                ParentChange {
                    target: tasksPage
                    parent: wideLayoutTasksPagePlaceholder
                }

                ParentChange {
                    target: calendarPage
                    parent: wideLayoutCalendarPagePlaceholder
                }

                PropertyChanges {
                    appHeader.title: wideLayoutAppTitle
                    wideLayoutSplitView.visible: true
                    narrowLayoutColumnLayout.visible: false
                }
            },
            State {
                name: "narrowLayout"
                when: width < wideLayoutMinimumWidth

                ParentChange {
                    target: tasksPage
                    parent: narrowLayoutTasksPagePlaceholder
                }

                ParentChange {
                    target: calendarPage
                    parent: narrowLayoutCalendarPagePlaceholder
                }

                PropertyChanges {
                    appHeader.title: narrowLayoutAppTitle
                    wideLayoutSplitView.visible: false
                    narrowLayoutColumnLayout.visible: true
                }
            }
        ]
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
