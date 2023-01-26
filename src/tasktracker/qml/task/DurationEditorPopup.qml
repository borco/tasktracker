import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

ThemedPopup {
    id: root

    property date start
    property date stop
    property bool validDuration: true

    property string title: qsTr("Task Editor")

    signal accepted()

    function updateDuration() {
        let seconds = TaskAggregate.secondsBetween(startEditor.editedDate, stopEditor.editedDate)
        validDuration = seconds >= 0
        durationLabel.color = validDuration ? root.palette.text : Theme.ErrorColor
        durationLabel.text = qsTr("Duration: %1").arg(TaskAggregate.formattedSeconds(seconds, true))
    }

    parent: Overlay.overlay
    anchors.centerIn: parent

    contentHeight: contentLayout.implicitHeight
    contentWidth: contentLayout.implicitWidth

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    modal: true

    ColumnLayout {
        id: contentLayout

        anchors.fill: parent
//        spacing: 0

        PopupPageHeader {
            title: root.title

            Layout.fillWidth: true

            leftButton.text: qsTr("Cancel")
            leftButton.onClicked: root.close()
            rightButton.text: qsTr("Save")
            rightButton.enabled: validDuration
            rightButton.onClicked: {
                accepted()
                root.close()
            }
        }

        ColumnLayout {
            Layout.fillWidth: true

            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.leftMargin: Theme.ContentLeftMargin
            Layout.rightMargin: Theme.ContentRightMargin

            ThemedSmallLabel {
                text: qsTr("Duration:")
            }

            ThemedLabel {
                id: durationLabel
            }

            GridLayout {
                Layout.fillWidth: true
                Layout.topMargin: 10

                columns: 2

                ThemedSmallLabel { text: qsTr("Start:") }

                ThemedSmallLabel { text: qsTr("Stop:") }

                TimeEditor {
                    id: startEditor
                    date: root.start
                    Layout.fillWidth: true
                    onEditedDateChanged: updateDuration()
                }

                TimeEditor {
                    id: stopEditor
                    date: root.stop
                    minimumDate: startEditor.editedDate
                    Layout.fillWidth: true
                    onEditedDateChanged: updateDuration()
                }
            }
        }

        Item { Layout.fillHeight: true }
    }
}
