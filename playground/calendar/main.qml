import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property WeekModel weekModel: WeekModel {}

    Page {
        anchors.fill: parent

        ColumnLayout {
            width: parent.width

            WeekView {
                weekModel: root.weekModel
                Layout.fillWidth: true
            }
        }
    }
}
