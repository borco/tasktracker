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
        currentDate: {
            let date = new Date()
            date.setDate(date.getDate() - 1)
            return date
        }
    }

    Page {
        anchors.fill: parent

        background: Rectangle {
            color: palette.base
        }

        WeekView {
            model: root.weekModel
            width: parent.width
        }
    }
}
