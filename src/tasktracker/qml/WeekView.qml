import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

RowLayout {
    id: root

    required property WeekModel weekModel

    property int dayWidth: 100

    Layout.topMargin: 10
    Layout.alignment: Qt.AlignHCenter

    Repeater {
        model: weekModel

        delegate: Item {
            implicitWidth: root.dayWidth
            implicitHeight: weekDelegateLayout.implicitHeight

            ColumnLayout {
                id: weekDelegateLayout
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
                    width: 30
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
