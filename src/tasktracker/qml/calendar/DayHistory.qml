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

                text: "<b>%1</b> (%2, %3)".arg(name).arg(TaskRepeat.toString(repeatMode)).arg(TaskTrack.toString(trackMode))
            }

            Pane {
                Layout.fillWidth: true

                leftPadding: Theme.ContentLeftMargin
                rightPadding: Theme.ContentRightMargin

                background: Rectangle {
                    color: isArchived ? palette.alternateBase : palette.base
                }

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

            BottomSeparator {
                anchors.bottom: undefined
                Layout.fillWidth: true
            }
        }
    }
}
