import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

Page {
    id: root

    required property TaskListModel taskListModel

    signal showConfig()

    background: null

    header: PageHeader {
        title.text: root.title

        onShowConfig: root.showConfig()

        PageHeader.Layout {
            TogglLoggedStatus {}

            Item { Layout.fillWidth: true }

            ThemedToolButton {
                id: archivedToggle
                icon.source: "../icons/archived.svg"
                checkable: true
            }

            ThemedToolButton {
                id: doneToggle
                icon.source: "../icons/task/done.svg"
                checkable: true
            }
        }
    }

    Flickable {
        anchors.fill: parent

        ColumnLayout {
            id: topLayout

            width: parent.width

            Repeater {
                model: TaskListFilterModel {
                    sourceModel: taskListModel
                    showDone: doneToggle.checked
                    showArchived: archivedToggle.checked
                }

                delegate: ColumnLayout {
                    Layout.fillWidth: true

                    ConfigGroupTitle {
                        text: "%1 (%2, %3)".arg(name).arg(TaskScheduleMode.toString(scheduleMode)).arg(TaskTrackMode.toString(trackMode))
                    }

                    Repeater {
                        model: history
                        delegate: ThemedLabel {
                            text: "tracking: %1, started: %2, duration: %3".arg(trackMode).arg(dateTime).arg(seconds)
                        }
                    }

                    BottomSeparator {
                        anchors.bottom: undefined
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
