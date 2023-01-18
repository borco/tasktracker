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

    ListView {
        anchors.fill: parent

        model: TaskListFilterModel {
            sourceModel: taskListModel
            showDone: doneToggle.checked
            showArchived: archivedToggle.checked
        }

        delegate: ColumnLayout {
            width: ListView.view.width
            spacing: 0

            ConfigGroupTitle {
                text: "<b>%1</b> (%2, %3)".arg(name).arg(TaskScheduleMode.toString(scheduleMode)).arg(TaskTrackMode.toString(trackMode))
            }

            Pane {
                Layout.fillWidth: true

                topPadding: 0
                leftPadding: Theme.ContentLeftMargin
                rightPadding: Theme.ContentRightMargin

                background: Rectangle { color: palette.base }

                ListView {
                    model: history

                    implicitHeight: contentHeight
                    interactive: false
                    section.property: "date"
                    section.delegate: Rectangle {
                        width: ListView.view.width
                        height: 24

                        color: palette.base

                        ThemedSmallLabel {
                            text: section
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 4
                        }

                        BottomSeparator {}
                    }

                    delegate: RowLayout {
                        width: ListView.view.width

                        ThemedLabel {
                            Layout.preferredWidth: 100
                            text: TaskTrackMode.toString(trackMode)
                        }

                        ThemedLabel {
                            Layout.preferredWidth: 100
                            horizontalAlignment: Text.AlignRight
                            text: time
                        }

                        ThemedLabel {
                            Layout.preferredWidth: 100
                            horizontalAlignment: Text.AlignRight
                            text: qsTr("%1 sec").arg(seconds)
                        }

                        Item { Layout.fillWidth: true }
                    }
                }
            }

            BottomSeparator {
                anchors.bottom: undefined
                Layout.fillWidth: true
            }
        }
    }
}
