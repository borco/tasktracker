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

    RowLayout {
        id: rowLayout

        width: parent.width

        spacing: 10

        Repeater {
            id: repeater

            delegate: Rectangle {
                color: "#40ff0000"

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
                        color: isCurrentDate ? palette.highlight : "transparent"
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
