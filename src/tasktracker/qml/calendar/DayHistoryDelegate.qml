import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

ColumnLayout {
    id: root

    required property Task task

    component FilterPane: Pane {
        Layout.fillWidth: true

        leftPadding: Theme.ContentLeftMargin
        rightPadding: Theme.ContentRightMargin

        background: Rectangle {
            color: task.isArchived ? palette.alternateBase : palette.base
        }
    }

    component FilterListView: ListView {
        anchors.fill: parent
        implicitHeight: contentHeight
        interactive: false
    }

    x: Theme.ContentLeftMargin
    width: ListView.view.width - x

    height: visible ? implicitHeight : 0

    spacing: 0

    TaskSelectedDate {
        id: taskSelectedDate
        task: root.task
        selectedDate: date
    }

    ThemedGroupTitle {
        text: "<b>%1</b> (%2, %3)".arg(task.name).arg(TaskAggregate.toString(task.aggregateMode)).arg(TaskTrack.toString(task.trackMode))
    }

    FilterPane {
        visible: task.trackMode === TaskTrack.Count
        RowLayout {
            anchors.fill: parent

            ThemedLabel {
                id: valueLabel
                text: taskSelectedDate.count
            }

            Item { Layout.fillWidth: true }

            ThemedToolButton {
                visible: taskSelectedDate.count > 0
                icon.source: "../../icons/task/decrement.svg"
                onClicked: --taskSelectedDate.count
            }

            ThemedToolButton {
                icon.source: "../../icons/task/increment.svg"
                onClicked: ++taskSelectedDate.count
            }
        }
    }

    FilterPane {
        visible: durationsView.count > 0

        FilterListView {
            id: durationsView

            model: taskSelectedDate.durations

            delegate: RowLayout {
                width: ListView.view.width

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

    FilterPane {
        visible: task.trackMode === TaskTrack.Duration
        ThemedToolButton {
            icon.source: "../../icons/task/increment.svg"
        }
    }

    BottomSeparator {
        anchors.bottom: undefined
        Layout.fillWidth: true
    }
}
