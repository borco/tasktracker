import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import ".."
import "../Theme.js" as Theme

Rectangle {
    id: root

    property alias model: repeater.model
    property int daysSpacing: 10
    property int dayCircleDiameter: 30
    property real dayWidth: Math.max(dayCircleDiameter, (width - 6 * daysSpacing) / 7)

    function isToday(date) {
        let today = new Date()
        return date.getDate() === today.getDate()
                && date.getMonth() === today.getMonth()
                && date.getYear() === today.getYear()
    }

    implicitHeight: rootLayout.implicitHeight

    ColumnLayout {
        id: rootLayout

        width: parent.width

        ThemedLabel {
            text: root.model.currentDate.toLocaleString(Qt.locale(), qsTr("dddd, MMM d"))
            font.pointSize: Theme.SmallLabelSize
            font.bold: true
        }

        RowLayout {
            id: daysLayout

            spacing: root.daysSpacing

            Layout.fillWidth: true

            Repeater {
                id: repeater

                delegate: Item {
                    implicitWidth: root.dayWidth
                    implicitHeight: delegateLayout.implicitHeight

                    ColumnLayout {
                        id: delegateLayout

                        width: parent.width

                        ThemedLabel {
                            text: name
                            Layout.fillWidth: true
                            font.weight: Theme.XSmallLabelWeight
                            font.pointSize: Theme.XSmallLabelSize
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

                            ThemedLabel {
                                anchors.centerIn: parent
                                text: date.getDate()
                                font.pointSize: Theme.SmallLabelSize
                                font.bold: isCurrentDate
                            }
                        }
                    }
                }
            }
        }
    }
}
