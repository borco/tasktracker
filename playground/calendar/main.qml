import QtQuick

import TaskTrackerLib

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property TaskListModel taskListModel: TaskListModel {}

    CalendarPage {
        taskListModel: root.taskListModel
        anchors.fill: parent
    }
}
