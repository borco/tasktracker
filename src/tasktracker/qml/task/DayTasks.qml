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
            date: model.date
            width: ListView.view.width
        }
    }
}
