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
        clip: true

        delegate: DayHistoryDelegate {
            onIncrementCount: console.log("increment count")
            onDecrementCount: console.log("decrement count")
        }
    }
}
