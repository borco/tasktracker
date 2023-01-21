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
                text: TaskRepeat.toString(repeatMode)
            }

            ThemedSmallLabel {
                text: TaskTrack.toString(trackMode)
            }

            ThemedSmallLabel {
                visible: isArchived
                text: qsTr("Archived")
            }
        }

        ThemedToolButton {
            icon.source: "../icons/task/decrement.svg"
            visible: trackMode === TaskTrack.Count
            onClicked: decrement()
        }

        ThemedToolButton {
            icon.source: "../icons/task/increment.svg"
            visible: trackMode === TaskTrack.Count
            onClicked: increment()
        }

        ThemedToolButton {
            visible: trackMode === TaskTrack.Duration
            icon.source: isStarted ? "../icons/task/stop.svg" : "../icons/task/start.svg"
            onClicked: isStarted = !isStarted
        }
    }
}
