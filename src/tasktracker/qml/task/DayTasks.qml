import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

Item {
    id: root

    property alias visibleTasksModel: view.model

    property bool editButtonVisible: true

    signal editTask(dayViewTaskModelContext: var)
    signal editDuration(taskDurationModelContext: var)
    signal addDuration(taskDurationModel: var)

    implicitHeight: view.implicitHeight
    implicitWidth: view.implicitWidth

    ListView {
        id: view

        anchors.fill: parent
        anchors.leftMargin: Theme.ContentLeftMargin
        anchors.rightMargin: Theme.ContentRightMargin

        clip: true
        spacing: 10

        header: Item { implicitHeight: 10 }
        footer: Item { implicitHeight: 10 }

        delegate: DayTask {
            editButtonVisible: root.editButtonVisible
            dayViewTaskModelContext: model
            date: dayViewModel.date
            task: model.task
            width: ListView.view.width
            onEditTask: (dayViewTaskModelContext) => root.editTask(dayViewTaskModelContext)
            onEditDuration: (taskDurationModelContext) => root.editDuration(taskDurationModelContext)
            onAddDuration: (taskDurationModel) => root.addDuration(taskDurationModel)
        }
    }
}
