import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

ColumnLayout {
    id: root

    component FilterPane: Pane {
        Layout.fillWidth: true

        leftPadding: Theme.ContentLeftMargin
        rightPadding: Theme.ContentRightMargin

        background: Rectangle {
            color: isArchived ? palette.alternateBase : palette.base
        }
    }

    component FilterListView: ListView {
        implicitHeight: contentHeight
        interactive: false
    }

    x: Theme.ContentLeftMargin
    width: ListView.view.width - x

    height: visible ? implicitHeight : 0

    spacing: 0

    TaskDurationFilterModel {
        id: filteredDurations
        sourceModel: durations
        selectedDate: date
    }

    TaskCountFilterModel {
        id: filteredCounts
        sourceModel: counts
        selectedDate: date
    }

    ThemedGroupTitle {
        text: "<b>%1</b> (%2, %3)".arg(name).arg(TaskRepeat.toString(repeatMode)).arg(TaskTrack.toString(trackMode))
    }

    FilterPane {
        visible: trackMode === TaskTrack.Count && countsView.count === 0
        ThemedLabel {
            text: "0"
        }
    }

    FilterPane {
        visible: countsView.count > 0

        FilterListView {
            id: countsView

            model: filteredCounts

            delegate: ThemedLabel {
                width: ListView.view.width
                text: count
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
        visible: trackMode === TaskTrack.Duration && durationsView.count === 0
        ThemedLabel {
            text: "+"
        }
    }

    BottomSeparator {
        anchors.bottom: undefined
        Layout.fillWidth: true
    }
}
