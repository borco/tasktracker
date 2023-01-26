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

    signal edit(dayViewTaskModel: var)
    signal editDuration(taskDurationModel: var)

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
            dayViewTaskModel: model
            date: dayViewModel.date
            task: model.task
            width: ListView.view.width
            onEdit: (dayViewTaskModel) => root.edit(dayViewTaskModel)
            onEditDuration: (taskDurationModel) => root.editDuration(taskDurationModel)
        }
    }
}
