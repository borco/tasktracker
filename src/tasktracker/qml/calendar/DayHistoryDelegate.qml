import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

Pane {
    id: root

    required property Task task

    background: Rectangle {
        color: task.isArchived ? palette.alternateBase : palette.base
    }

    TaskSelectedDate {
        id: taskSelectedDate
        task: root.task
        selectedDate: date
    }

    ColumnLayout {
        id: layout
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            Button {
                id: durationDetailsToggle
                visible: task.trackMode === TaskTrack.Duration
                text: taskSelectedDate.durations.size
                checkable: true

                background: Rectangle {
                    implicitWidth: 30
                    implicitHeight: 30
                    radius: width
                    color : durationDetailsToggle.checked ? root.palette.button : "transparent"
                    border.color: root.palette.button
                    border.width: 1
                }

                contentItem: Text {
                    text: durationDetailsToggle.text
                    color : durationDetailsToggle.checked ? root.palette.buttonText : root.palette.button
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.leftMargin: task.trackMode === TaskTrack.Duration ? 10 : 0

                ThemedLabel {
                    text: task.name
                    Layout.fillWidth: true
                }

                ThemedSmallLabel {
                    visible: task.trackMode === TaskTrack.Count
                    text: task.aggregateMode === TaskAggregate.Daily
                          ? qsTr("%1").arg(taskSelectedDate.count)
                          : qsTr("%1 / %2: %3").arg(taskSelectedDate.count).arg(TaskAggregate.toString(task.aggregateMode)).arg(taskSelectedDate.aggregateCount)
                }

                ThemedSmallLabel {
                    property string formattedSeconds: taskSelectedDate.formattedSeconds(taskSelectedDate.seconds)
                    property string formattedAggregatedSeconds: taskSelectedDate.formattedSeconds(taskSelectedDate.aggregatedSeconds)
                    visible: task.trackMode === TaskTrack.Duration
                    text: task.aggregateMode === TaskAggregate.Daily
                          ? qsTr("%1").arg(formattedSeconds)
                          : qsTr("%1 / %2: %3").arg(formattedSeconds).arg(TaskAggregate.toString(task.aggregateMode)).arg(formattedAggregatedSeconds)
                }
            }

            ThemedToolButton {
                icon.source: "../../icons/task/decrement.svg"
                visible: task.trackMode === TaskTrack.Count && taskSelectedDate.count > 0
                onClicked: --taskSelectedDate.count
            }

            ThemedToolButton {
                icon.source: "../../icons/task/increment.svg"
                visible: task.trackMode === TaskTrack.Count
                onClicked: ++taskSelectedDate.count
            }
        }

        ListView {
            Layout.fillWidth: true

            visible: task.trackMode === TaskTrack.Duration && durationDetailsToggle.checked
            model: taskSelectedDate.durations

            implicitHeight: contentHeight
            interactive: false

            delegate: Pane {
                width: ListView.view.width

                background: Rectangle { color: palette.alternateBase }

                RowLayout {
                    anchors.fill: parent
                    ThemedLabel {
                        text: time
                        font.family: fixedFont.family
                    }

                    ThemedLabel {
                        Layout.preferredWidth: 80
                        horizontalAlignment: Text.AlignRight
                        text: qsTr("+%1 sec").arg(seconds)
                        font.family: fixedFont.family
                    }

                    Item { Layout.fillWidth: true }
                }
            }
        }
    }
}
