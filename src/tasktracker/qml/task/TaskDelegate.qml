import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"

Pane {
    id: root

    required property int index
    required property var model
    required property Task task
    required property bool isDone
    required property bool isArchived

    property bool isStarted: false

    signal edit()
    signal increment()
    signal decrement()
    signal start()
    signal stop()

    contentHeight: layout.implicitHeight
    contentWidth: layout.implicitWidth

    background: Rectangle {
        radius: 10
        color: task.isArchived ? palette.alternateBase : palette.base
    }

    RowLayout {
        id: layout

        anchors.fill: parent

        ThemedToolButton {
            icon.source: "../../icons/task/edit.svg"
            onClicked: edit()
        }

        ColumnLayout {
            Layout.fillWidth: true

            ThemedLabel {
                text: task.name
                Layout.fillWidth: true
            }

            ThemedSmallLabel {
                text: TaskRepeat.toString(task.repeatMode)
            }

            ThemedSmallLabel {
                text: TaskTrack.toString(task.trackMode)
            }

            ThemedSmallLabel {
                visible: isArchived
                text: qsTr("Archived")
            }
        }

        ThemedToolButton {
            icon.source: "../../icons/task/decrement.svg"
            visible: task.trackMode === TaskTrack.Count
            onClicked: decrement()
        }

        ThemedToolButton {
            icon.source: "../../icons/task/increment.svg"
            visible: task.trackMode === TaskTrack.Count
            onClicked: increment()
        }

        ThemedToolButton {
            visible: task.trackMode === TaskTrack.Duration
            icon.source: isStarted ? "../../icons/task/stop.svg" : "../../icons/task/start.svg"
            onClicked: isStarted = !isStarted
        }
    }
}
