import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import ".."
import "../theme"
import "../theme/Theme.js" as Theme

Item {
    id: root

    required property TaskFilterModel taskFilterModel
    required property bool inEditMode

    property string title: ""

    signal editTask(dayViewTaskModelContext: var)
    signal deleteTask(dayViewTaskModelContext: var)
    signal editDuration(taskDurationModelContext: var)
    signal addDuration(taskDurationModel: var)
    signal addTask()

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.topMargin: Theme.ContentTopMargin
            Layout.leftMargin: Theme.ContentLeftMargin
            Layout.rightMargin: Theme.ContentRightMargin

            ThemedLabel {
                text: dayTasks.dayViewModel.date.toLocaleString(Qt.locale(), qsTr("dddd, MMM d, yyyy"))
                font.pointSize: Theme.SmallLabelSize
                font.bold: true

                Layout.fillWidth: true
            }

            ThemedButton {
                text: qsTr("Today")
                highlighted: false
                onClicked: dayTasks.dayViewModel.date = new Date()
            }
        }

        ThemedButtonDelegate {
            text: qsTr("＋ Add Task")
            separatorVisible: false
            visible: inEditMode
            Layout.topMargin: Theme.ContentTopMargin
            Layout.leftMargin: Theme.ContentLeftMargin
            Layout.rightMargin: Theme.ContentRightMargin
            onClicked: root.addTask()
        }

        DayTasks {
            id: dayTasks

            property var dayViewModel: QtObject {
                property date date: new Date()
            }

            Layout.fillWidth: true
            Layout.fillHeight: true

            editButtonVisible: inEditMode

            visibleTasksModel: taskFilterModel

            onEditTask: (dayViewTaskModelContext) => root.editTask(dayViewTaskModelContext)
            onDeleteTask: (dayViewTaskModelContext) => root.deleteTask(dayViewTaskModelContext)
            onEditDuration: (taskDurationModelContext) => root.editDuration(taskDurationModelContext)
            onAddDuration: (taskDurationModel) => root.addDuration(taskDurationModel)
        }
    }
}
