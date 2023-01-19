import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

Rectangle {
    id: root

    property alias model: repeater.model
    property alias spacing: rowLayout.spacing

    property int dayCircleDiameter: 30
    property real dayWidth: Math.max(dayCircleDiameter, (width - 6 * spacing) / 7)

    function isToday(date) {
        let today = new Date()
        return date.getDate() === today.getDate()
    }

    RowLayout {
        id: rowLayout

        width: parent.width

        spacing: 10

        Repeater {
            id: repeater

            delegate: Item {
//            delegate: Rectangle {
//                color: "#40ff0000"
//                color: "transparent"

                implicitWidth: root.dayWidth
                implicitHeight: delegateLayout.implicitHeight

                ColumnLayout {
                    id: delegateLayout

                    width: parent.width

                    ThemedLabel {
                        text: name
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Rectangle {
                        property bool isToday: root.isToday(date)
                        color: isCurrentDate ? palette.highlight : "transparent"
                        border.color: isToday ? palette.dark : "transparent"
                        border.width: 2
                        Layout.alignment: Qt.AlignHCenter
                        width: root.dayCircleDiameter
                        height: width
                        radius: width / 2

                        ThemedSmallLabel {
                            anchors.centerIn: parent
                            text: date.getDate()
                        }
                    }
                }
            }
        }
    }
}
