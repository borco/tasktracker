import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

Control {
    id: root

    property date date
    property Task task
    property var dayViewTaskModelContext

    property bool editButtonVisible: true

    signal editTask(dayViewTaskModelContext: var)
    signal editDuration(taskDurationModelContext: var)
    signal addDuration(taskDurationModel: var)

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

                    ThemedToolButton {
                        visible: root.editButtonVisible
                        icon.source: "../../icons/task/edit.svg"
                        onClicked: root.editTask(root.dayViewTaskModelContext)
                    }

                    ThemedRoundButton {
                        id: durationDetailsToggle
                        visible: task.trackMode === TaskTrack.Duration
                        text: taskDurationModel.size
                        checkable: true
                        checked: true
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

            footer: ItemDelegate {
                width: ListView.view.width
                background: Rectangle { color: palette.alternateBase }
                icon.source: "../../icons/task/increment.svg"
                icon.width: 24
                icon.height: 24
                onClicked: root.addDuration(taskDurationModel)
            }

            delegate: Pane {
                property var taskDurationModelContext: model

                width: ListView.view.width

                background: Rectangle { color: palette.alternateBase }

                RowLayout {
                    anchors.fill: parent
                    ThemedLabel {
                        text: qsTr("%1 → %2   %3").arg(startTime).arg(stopTime).arg(TaskAggregate.formattedSeconds(seconds))
                        font.family: fixedFont.family

                        MouseArea {
                            anchors.fill: parent
                            onClicked: editDuration(taskDurationModelContext)
                        }
                    }

                    Item { Layout.fillWidth: true }
                }
            }
        }
    }
}
