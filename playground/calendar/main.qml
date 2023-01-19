import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Calendar")

    property WeekModel weekModel: WeekModel {
        currentDate: new Date()
    }

    Page {
        anchors.fill: parent

        WeekView {
            model: root.weekModel
            width: parent.width
        }
    }
}
