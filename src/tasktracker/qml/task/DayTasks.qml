import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

Item {
    id: root

    property alias taskModel: visualModel.model

    property bool editButtonVisible: true

    signal editTask(dayViewTaskModelContext: var)
    signal deleteTask(dayViewTaskModelContext: var)
    signal editDuration(taskDurationModelContext: var)
    signal addDuration(taskDurationModel: var)
    signal moveTask(oldIndex: int, newIndex: int)

    implicitHeight: view.implicitHeight
    implicitWidth: view.implicitWidth

    DelegateModel {
        id: visualModel

        delegate: DayTask {
            taskMovingEnabled: root.editButtonVisible
            editButtonVisible: root.editButtonVisible
            dayViewTaskModelContext: model
            contentParentWhenHeld: root
            contentXWhenHeld: view.x + 4
            date: dayViewModel.date
            task: model.task
            width: ListView.view.width

            onEditTask: (dayViewTaskModelContext) => root.editTask(dayViewTaskModelContext)
            onDeleteTask: (dayViewTaskModelContext) => root.deleteTask(dayViewTaskModelContext)
            onEditDuration: (taskDurationModelContext) => root.editDuration(taskDurationModelContext)
            onAddDuration: (taskDurationModel) => root.addDuration(taskDurationModel)

            onMoveTask: (oldIndex, newIndex) => root.moveTask(oldIndex, newIndex)
        }
    }

    ListView {
        id: view

        anchors.fill: parent
        anchors.leftMargin: Theme.ContentLeftMargin
        anchors.rightMargin: Theme.ContentRightMargin

        clip: true
        spacing: 10

        header: Item { implicitHeight: 10 }
        footer: Item { implicitHeight: 10 }

        model: visualModel

        cacheBuffer: 50
    }
}
