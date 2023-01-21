import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

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

            visible: selectedDateDurationsView.count > 0
            height: visible ? implicitHeight : 0

            spacing: 0

            ThemedGroupTitle {
                text: "<b>%1</b> (%2, %3)".arg(name).arg(TaskRepeat.toString(repeatMode)).arg(TaskTrack.toString(trackMode))
            }

            Pane {
                Layout.fillWidth: true

                leftPadding: Theme.ContentLeftMargin
                rightPadding: Theme.ContentRightMargin

                background: Rectangle {
                    color: isArchived ? palette.alternateBase : palette.base
                }

                contentHeight: selectedDateDurationsView.implicitHeight

                TaskDurationFilterModel {
                    id: selectedDateDurations
                    sourceModel: durations
                    selectedDate: date
                }

                ListView {
                    id: selectedDateDurationsView

                    model: selectedDateDurations

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
