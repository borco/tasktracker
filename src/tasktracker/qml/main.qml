import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import TaskTrackerLib

import "config"
import "task"
import "theme"
import "theme/Theme.js" as Theme

ApplicationWindow {
    id: root

    property bool inDarkMode: palette.text > palette.base

    property bool inEditMode: appHeader.editChecked
    property alias isArchivedVisible: appHeader.isArchivedVisible
    property alias isDoneVisible: appHeader.isDoneVisible

    property TaskModel taskModel: TaskModel {}

    property TaskFilterModel taskFilterModel: TaskFilterModel {
        sourceModel: taskModel
        isArchivedVisible: root.isArchivedVisible
        isDoneVisible: root.isDoneVisible
    }

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

    ConfirmTaskDeletionMessageBox {
        id: confirmTaskDeletionMessageBox
        onDeletionAccepted: taskModel.deleteTask(task)
    }

    ConfigPopup {
        id: configPopup
    }

    TaskEditorPopup {
        id: taskEditorPopup

        property var context

        function editTask(context) {
            if (context) {
                this.context = context
                let task = context.task
                name = task.name
                isArchived = task.isArchived
                aggregateMode = task.aggregateMode
                trackMode = task.trackMode
            } else {
                name = ""
                isArchived = false
                aggregateMode = TaskAggregate.DefaultMode
                trackMode = TaskTrack.DefaultMode
            }

            open()
        }

        onAccepted: {
            let task = context ? context.task : taskModel.prependTask()
            task.name = name
            task.trackMode = trackMode
            task.aggregateMode = aggregateMode

            if (context) {
                // change the context.isArchived the last, so that
                // context.task isn't hidden and becomes invalid
                // before the other changes from the editor are stored in it
                context.isArchived = isArchived
            } else {
                task.isArchived = isArchived
                if (isArchived) {
                    taskFilterModel.invalidate()
                }
            }
        }
    }

    DurationEditorPopup {
        id: durationEditorPopup

        property var taskDurationModelContext: null
        property var taskDurationModel: null

        function editDuration(context) {
            taskDurationModelContext = context
            taskDurationModel = null
            start = context.start
            stop = context.stop
            open()
        }

        function addDuration(model) {
            taskDurationModelContext = null
            taskDurationModel = model
            start = taskDurationModel.nextFreeLocalTime()
            stop = taskDurationModel.nextFreeLocalTime()
            open()
        }

        onAccepted: {
            if (taskDurationModelContext) {
                taskDurationModelContext.duration = editedDuration
            } else if (taskDurationModel) {
                taskDurationModel.addDuration(editedDuration)
            }
        }
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
                            anchors.fill: parent
                            taskModel: inEditMode ? root.taskModel : root.taskFilterModel
                            inEditMode: root.inEditMode

                            onAddTask: taskEditorPopup.editTask(null)
                            onDeleteTask: (dayViewTaskModelContext) => confirmTaskDeletionMessageBox.deleteTask(dayViewTaskModelContext.task)
                            onEditTask: (dayViewTaskModelContext) => taskEditorPopup.editTask(dayViewTaskModelContext)
                            onEditDuration: (taskDurationModelContext) => durationEditorPopup.editDuration(taskDurationModelContext)
                            onAddDuration: (taskDurationModel) => durationEditorPopup.addDuration(taskDurationModel)

                            onMoveTask: (oldIndex, newIndex) => {
                                            taskModel.moveTask(oldIndex, newIndex)
                                        }
                        }
                    }

                    Item {
                        id: wideLayoutCalendarPagePlaceholder

                        clip: true
                        SplitView.minimumWidth: calendarPageMinimumWidth

                        CalendarPage {
                            id: calendarPage
                            title: qsTr("Calendar")
                            anchors.fill: parent
                            taskModel: root.taskFilterModel

                            onEditDuration: (taskDurationModelContext) => durationEditorPopup.editDuration(taskDurationModelContext)
                            onAddDuration: (taskDurationModel) => durationEditorPopup.addDuration(taskDurationModel)
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
        property alias editChecked: appHeader.editChecked
        property alias isArchivedVisible: appHeader.isArchivedVisible
        property alias isDoneVisible: appHeader.isDoneVisible
    }

    Component.onCompleted: {
        taskModel.load(Config.dataFolderLocation)
        splitView.restoreState(settings.splitView)
        wideLayoutSplitView.restoreState(settings.wideLayoutSplitView)
    }

    Component.onDestruction: {
        taskModel.save(Config.dataFolderLocation)
        settings.splitView = splitView.saveState()
        settings.wideLayoutSplitView = wideLayoutSplitView.saveState()
    }
}
