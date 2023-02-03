import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

Item {
    id: root

    property bool held: false
    property Item contentParentWhenHeld: null
    property int contentXWhenHeld: 4

    property date date
    property Task task
    property var dayViewTaskModelContext

    property bool taskMovingEnabled: false
    property bool editButtonVisible: true

    property int topPadding: 8
    property int bottomPadding: 8
    property int leftPadding: 8
    property int rightPadding: 8

    property int toolButtonSize: 24
    property int toolButtonIconSize: 20
    property int toolButtonPadding: (toolButtonSize - toolButtonIconSize) / 2

    signal editTask(dayViewTaskModelContext: var)
    signal deleteTask(dayViewTaskModelContext: var)
    signal editDuration(taskDurationModelContext: var)
    signal addDuration(taskDurationModel: var)
    signal moveTask(oldIndex: int, newIndex: int)

    implicitHeight: content.implicitHeight + topPadding + bottomPadding
    implicitWidth: content.implicitWidth + leftPadding + rightPadding

    component DelegateToolButton: ThemedToolButton {
        icon.width: toolButtonIconSize
        icon.height: toolButtonIconSize
        implicitWidth: toolButtonSize
        implicitHeight: toolButtonSize
        icon.color: palette.button
        padding: toolButtonPadding
    }

    component Delegate: ItemDelegate {
        width: ListView.view.width
        background: Rectangle { color: palette.alternateBase }
        implicitHeight: 40
        font.family: fixedFont.family

        Rectangle {
            anchors.bottom: parent.bottom
            color: root.palette.base
            width: parent.width
            height: 1
        }
    }

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

    Rectangle {
        id: background
        anchors.fill: parent
        color: root.palette.mid
    }

    MouseArea {
        id: mouseArea

        enabled: taskMovingEnabled

        anchors.fill: parent

        onPressed: held = true
        onReleased: held = false

        drag.axis: Drag.YAxis
    }

    Rectangle {
        id: content

        color: task && task.isArchived ? palette.alternateBase : palette.base

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        width: root.width
        height: root.height

        implicitWidth: contentLayout.implicitWidth
        implicitHeight: contentLayout.implicitHeight

        Drag.active: root.held
        Drag.source: root
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2

        ColumnLayout {
            id: contentLayout

            anchors.fill: parent
            anchors.topMargin: root.topPadding
            anchors.bottomMargin: root.bottomPadding
            anchors.leftMargin: root.leftPadding
            anchors.rightMargin: root.rightPadding

            spacing: 0

            RowLayout {
                Layout.fillWidth: true

                DelegateToolButton {
                    visible: root.taskMovingEnabled
                    icon.source: "../../icons/task/drag.svg"
                    icon.color: palette.active.button
                    enabled: false
                }

                DelegateToolButton {
                    visible: root.editButtonVisible
                    icon.source: "../../icons/task/edit.svg"
                    onClicked: root.editTask(root.dayViewTaskModelContext)
                }

                DelegateToolButton {
                    visible: root.editButtonVisible
                    icon.source: "../../icons/task/delete.svg"
                    icon.color: Theme.DangerColor
                    onClicked: root.deleteTask(root.dayViewTaskModelContext)
                }

                ThemedRoundButton {
                    id: durationDetailsToggle
                    visible: task && task.trackMode === TaskTrack.Duration
                    text: taskDurationModel.size
                    checkable: true
//                    checked: true
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: task && task.trackMode === TaskTrack.Duration ? 10 : 0

                    ThemedLabel {
                        text: task ? task.name : ""
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                    }

                    ThemedSmallLabel {
                        visible: task && task.trackMode === TaskTrack.Count
                        text: task
                              ? (task.aggregateMode === TaskAggregate.Daily
                                 ? qsTr("%1").arg(taskCount.count)
                                 : qsTr("%1 / %2: %3").arg(taskCount.count).arg(TaskAggregate.toString(task.aggregateMode)).arg(taskCount.aggregateCount)
                                 )
                              : ""
                    }

                    ThemedSmallLabel {
                        property string formattedSeconds: TaskAggregate.formattedSeconds(taskDurationModel.seconds)
                        property string formattedAggregatedSeconds: TaskAggregate.formattedSeconds(taskDurationModel.aggregateSeconds)
                        visible: task && task.trackMode === TaskTrack.Duration
                        text: task
                              ? (task.aggregateMode === TaskAggregate.Daily
                                 ? qsTr("%1").arg(formattedSeconds)
                                 : qsTr("%1 / %2: %3").arg(formattedSeconds).arg(TaskAggregate.toString(task.aggregateMode)).arg(formattedAggregatedSeconds)
                                 )
                              : ""
                    }
                }

                DelegateToolButton {
                    icon.source: "../../icons/task/decrement.svg"
                    visible: task && task.trackMode === TaskTrack.Count && taskCount.count > 0
                    onClicked: --taskCount.count
                }

                DelegateToolButton {
                    icon.source: "../../icons/task/increment.svg"
                    visible: task && task.trackMode === TaskTrack.Count
                    onClicked: ++taskCount.count
                }
            }

            Item {
                visible: task && task.trackMode === TaskTrack.Duration && durationDetailsToggle.checked

                Layout.fillWidth: true
                Layout.leftMargin: -root.leftPadding
                Layout.rightMargin: -root.rightPadding
                Layout.topMargin: root.bottomPadding
                Layout.bottomMargin: -root.bottomPadding

                implicitHeight: durationsView.implicitHeight
                implicitWidth: durationsView.implicitWidth

                ListView {
                    id: durationsView

                    anchors.fill: parent

                    model: taskDurationModel

                    implicitHeight: contentHeight
                    interactive: false

                    footer: Delegate {
                        text: qsTr("＋")
                        onClicked: root.addDuration(taskDurationModel)
                    }

                    delegate: Delegate {
                        property var taskDurationModelContext: model
                        text: qsTr("%1 → %2   %3").arg(startTime).arg(stopTime).arg(TaskAggregate.formattedSeconds(seconds, true))
                        onClicked: editDuration(taskDurationModelContext)
                    }
                }

                Rectangle {
                    height: 1
                    width: parent.width
                }
            }
        }

        Rectangle {
            id: contentBorder
            anchors.fill: parent
            visible: false
            color: "transparent"
            border.width: 1
            border.color: root.palette.highlight
        }
    }

    DropArea {
        anchors.fill: parent
        anchors.margins: 10

        onEntered: (drag)=> {
                       let oldIndex = drag.source.DelegateModel.itemsIndex
                       let newIndex = root.DelegateModel.itemsIndex
                       if (oldIndex === newIndex) {
                           return
                       }
                       moveTask(oldIndex, newIndex)
                   }
    }

    states: [
        State {
            when: held

            ParentChange {
                target: content
                parent: contentParentWhenHeld
            }

            AnchorChanges {
                target: content
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }

            PropertyChanges {
                target: content
                x: contentXWhenHeld
            }

            PropertyChanges {
                target: content
                x: contentXWhenHeld
            }

            PropertyChanges {
                target: mouseArea
                drag.target: content
            }

            PropertyChanges {
                target: contentBorder
                visible: true
            }
        }
    ]
}
