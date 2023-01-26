import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

Control {
    id: root

    required property date date
    required property Task task

    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth

    TaskCount {
        id: taskCount
        task: root.task
        date: root.date
    }

    TaskDurationModel {
        id: taskDurationModel
        task: root.task
        date: root.date
    }

    ColumnLayout {
        id: layout

        anchors.fill: parent
        spacing: 0

        Pane {
            Layout.fillWidth: true

            background: Rectangle {
                color: task.isArchived ? palette.alternateBase : palette.base
            }

            ColumnLayout {
                anchors.fill: parent

                RowLayout {
                    Layout.fillWidth: true

                    Button {
                        id: durationDetailsToggle
                        visible: task.trackMode === TaskTrack.Duration
                        text: taskDurationModel.size
                        checkable: true
//                        checked: true

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
                                  ? qsTr("%1").arg(taskCount.count)
                                  : qsTr("%1 / %2: %3").arg(taskCount.count).arg(TaskAggregate.toString(task.aggregateMode)).arg(taskCount.aggregateCount)
                        }

                        ThemedSmallLabel {
                            property string formattedSeconds: TaskAggregate.formattedSeconds(taskDurationModel.seconds)
                            property string formattedAggregatedSeconds: TaskAggregate.formattedSeconds(taskDurationModel.aggregateSeconds)
                            visible: task.trackMode === TaskTrack.Duration
                            text: task.aggregateMode === TaskAggregate.Daily
                                  ? qsTr("%1").arg(formattedSeconds)
                                  : qsTr("%1 / %2: %3").arg(formattedSeconds).arg(TaskAggregate.toString(task.aggregateMode)).arg(formattedAggregatedSeconds)
                        }
                    }

                    ThemedToolButton {
                        icon.source: "../../icons/task/decrement.svg"
                        visible: task.trackMode === TaskTrack.Count && taskCount.count > 0
                        onClicked: --taskCount.count
                    }

                    ThemedToolButton {
                        icon.source: "../../icons/task/increment.svg"
                        visible: task.trackMode === TaskTrack.Count
                        onClicked: ++taskCount.count
                    }
                }
            }
        }

        DurationEditorPopup {
            id: durationEditoPopup
        }

        ListView {
            Layout.fillWidth: true

            visible: task.trackMode === TaskTrack.Duration && durationDetailsToggle.checked
            model: taskDurationModel

            implicitHeight: contentHeight
            interactive: false

            delegate: Pane {
                width: ListView.view.width

                background: Rectangle { color: palette.alternateBase }

                RowLayout {
                    anchors.fill: parent
                    ThemedLabel {
                        text: qsTr("%1 → %2   +%3 sec").arg(startTime).arg(stopTime).arg(seconds)
                        font.family: fixedFont.family

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                durationEditoPopup.start = start
                                durationEditoPopup.stop = stop
                                durationEditoPopup.open()
                            }
                        }
                    }

                    Item { Layout.fillWidth: true }
                }
            }
        }
    }
}
