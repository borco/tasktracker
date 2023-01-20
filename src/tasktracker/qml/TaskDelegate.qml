import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

Pane {
    id: root

    required property int index
    required property var model
    required property string name
    required property bool isDone
    required property bool isArchived
    required property int repeatMode
    required property int trackMode

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
        color: isArchived ? palette.alternateBase : palette.base
    }

    RowLayout {
        id: layout

        anchors.fill: parent

        ThemedToolButton {
            icon.source: "../icons/task/edit.svg"
            onClicked: edit()
        }

        ColumnLayout {
            Layout.fillWidth: true

            ThemedLabel {
                text: name
                Layout.fillWidth: true
            }

            ThemedSmallLabel {
                text: TaskRepeatMode.toString(repeatMode)
            }

            ThemedSmallLabel {
                visible: trackMode !== Task.NoTracking
                text: TaskTrackMode.toString(trackMode)
            }

            ThemedSmallLabel {
                visible: isArchived
                text: qsTr("Archived")
            }
        }

        ThemedToolButton {
            icon.source: isDone ? "../icons/task/done.svg" : "../icons/task/todo.svg"
            visible: trackMode === Task.NoTracking
            onClicked: model.isDone = !isDone
        }

        ThemedToolButton {
            icon.source: "../icons/task/decrement.svg"
            visible: [Task.Repeats, Task.MinimumRepeats, Task.MaximumRepeats].includes(trackMode)
            onClicked: decrement()
        }

        ThemedToolButton {
            icon.source: "../icons/task/increment.svg"
            visible: [Task.Repeats, Task.MinimumRepeats, Task.MaximumRepeats].includes(trackMode)
            onClicked: increment()
        }

        ThemedToolButton {
            visible: [Task.Duration, Task.MinimumDuration, Task.MaximumDuration].includes(trackMode)
            icon.source: isStarted ? "../icons/task/stop.svg" : "../icons/task/start.svg"
            onClicked: isStarted = !isStarted
        }
    }
}
