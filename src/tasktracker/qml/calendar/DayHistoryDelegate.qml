import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

ColumnLayout {
    id: root

    required property Task task

    signal incrementCount()
    signal decrementCount()

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

    component CountDelegate: RowLayout {
        required property int count

        ThemedLabel {
            id: valueLabel
            text: count
        }

        Item { Layout.fillWidth: true }

        ThemedToolButton {
            visible: count > 0
            icon.source: "../../icons/task/decrement.svg"
            onClicked: decrementCount()
        }

        ThemedToolButton {
            icon.source: "../../icons/task/increment.svg"
            onClicked: incrementCount()
        }
    }

    x: Theme.ContentLeftMargin
    width: ListView.view.width - x

    height: visible ? implicitHeight : 0

    spacing: 0

    TaskDurationFilterModel {
        id: filteredDurations
        sourceModel: task.durations
        selectedDate: date
    }

    TaskCountFilterModel {
        id: filteredCounts
        sourceModel: task.counts
        selectedDate: date
    }

    ThemedGroupTitle {
        text: "<b>%1</b> (%2, %3)".arg(task.name).arg(TaskRepeat.toString(task.repeatMode)).arg(TaskTrack.toString(task.trackMode))
    }

    FilterPane {
        visible: task.trackMode === TaskTrack.Count && countsView.count === 0
        CountDelegate {
            anchors.fill: parent
            count: 0
        }
    }

    FilterPane {
        visible: countsView.count > 0

        FilterListView {
            id: countsView

            model: filteredCounts

            delegate: CountDelegate {
                width: ListView.view.width
            }
        }
    }

    FilterPane {
        visible: durationsView.count > 0

        FilterListView {
            id: durationsView

            model: filteredDurations

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
