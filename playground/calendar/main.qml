import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "calendar"

Window {
    id: root

    property WeekModel weekModel: WeekModel {
        currentDate: {
            let date = new Date()
            date.setDate(date.getDate() - 1)
            return date
        }
    }

    width: 640
    height: 480
    visible: true
    title: qsTr("Calendar")

    Page {
        anchors.fill: parent

        background: Rectangle {
            color: palette.base
        }

        ColumnLayout {
            anchors.fill: parent

            WeekView {
                model: root.weekModel
                Layout.fillWidth: true
            }

            DayView {
                id: dayView

                Layout.fillWidth: true
                Layout.fillHeight: true

                sourceComponent: Component {
                    Rectangle {
                        color: palette.window

                        Text {
                            anchors.centerIn: parent
                            text: "delta: %1".arg(delta)
                        }
                    }
                }

                onDaysAdded: (days) => root.weekModel.addDays(days)
            }
        }
    }
}
