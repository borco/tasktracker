import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import ".."
import "../Theme.js" as Theme

Item {
    id: root

    property alias visibleTasksModel: view.model

    implicitHeight: view.implicitHeight
    implicitWidth: view.implicitWidth

    ListView {
        id: view

        anchors.fill: parent
        clip: true

        delegate: ColumnLayout {
            x: Theme.ContentLeftMargin
            width: ListView.view.width - x

            visible: currentDayHistoryView.count > 0
            height: visible ? implicitHeight : 0

            spacing: 0

            ConfigGroupTitle {
//                Rectangle { color: "#40ff0000"; anchors.fill: parent }

                text: "<b>%1</b> (%2, %3)".arg(name).arg(TaskRepeatMode.toString(repeatMode)).arg(TaskTrack.toString(trackMode))
            }

            Pane {
                Layout.fillWidth: true

                topPadding: 0
                leftPadding: Theme.ContentLeftMargin
                rightPadding: Theme.ContentRightMargin

                background: Rectangle { color: palette.base }

                contentHeight: currentDayHistoryView.implicitHeight

                TaskCurrentDayHistory {
                    id: currentDayHistory
                    sourceModel: history
                    currentDate: date
                }

                ListView {
                    id: currentDayHistoryView

                    model: currentDayHistory

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
                            text: TaskTrack.toString(trackMode)
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
