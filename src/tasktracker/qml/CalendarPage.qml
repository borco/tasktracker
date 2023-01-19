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

    property int dayWidth: Math.floor((root.width - weekLayout.spacing) / 7 - 7)

    WeekModel {
        id: weekModel
        currentDate: new Date()
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            id: weekLayout

            Layout.topMargin: 10
            Layout.alignment: Qt.AlignHCenter

            Repeater {
                model: weekModel

                delegate: Item {
                    implicitWidth: root.dayWidth
                    implicitHeight: weekDelegateLayout.implicitHeight

                    ColumnLayout {
                        id: weekDelegateLayout
                        width: parent.width

                        ThemedLabel {
                            text: name
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                            horizontalAlignment: Text.AlignHCenter
                        }

                        Rectangle {
                            color: isCurrentDate ? palette.highlight : "transparent"
                            Layout.alignment: Qt.AlignHCenter
                            width: 30
                            height: width
                            radius: width / 2
                            ThemedSmallLabel {
                                anchors.centerIn: parent
                                text: date.getDate()
                            }
                        }
                    }
                }
            }
        }

        BottomSeparator {
            anchors.bottom: undefined
            Layout.fillWidth: true
        }

        ListView {
            clip: true

            Layout.fillHeight: true
            Layout.fillWidth: true

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
}
