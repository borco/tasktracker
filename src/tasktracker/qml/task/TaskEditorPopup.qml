import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

ThemedPopup {
    id: root

    property string name: ""
    property bool isArchived: false
    property int aggregateMode: TaskAggregate.DefaultMode
    property int trackMode: TaskTrack.DefaultMode

    property string title: qsTr("Task Editor")

    property int labelWidth: 60

    signal accepted()

    component ItemInput: Pane {
        property alias label: inputLabel.text
        property alias text: input.text

        Layout.fillWidth: true

        padding: 0

        implicitHeight: inputLayout.implicitHeight + inputLayout.anchors.topMargin + inputLayout.anchors.bottomMargin

        background: Rectangle {
            color: palette.base

            BottomSeparator {}
        }

        RowLayout {
            id: inputLayout

            anchors.fill: parent
            anchors.topMargin: Theme.PopupItemTopMargin
            anchors.bottomMargin: Theme.PopupItemBottomMargin
            anchors.leftMargin: Theme.ContentLeftMargin
            anchors.rightMargin: Theme.ContentRightMargin

            ThemedLabel {
                id: inputLabel
                Layout.preferredWidth: root.labelWidth
            }

            TextField {
                id: input
                Layout.fillWidth: true
            }
        }
    }

    modal: true

    parent: Overlay.overlay

    x: Theme.PopupX
    y: Theme.PopupTop
    width: parent.width - 2 * x
    height: parent.height - Theme.PopupTop - Theme.PopupBottom

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    contentHeight: contentLayout.implicitHeight
    contentWidth: contentLayout.implicitWidth

    ButtonGroup { id: trackModeGroup }
    ButtonGroup { id: repeadModeGroup }

    ColumnLayout {
        id: contentLayout

        anchors.fill: parent
        spacing: 0

        PopupPageHeader {
            title: root.title

            Layout.fillWidth: true

            leftButton.visible: true
            leftButton.text: qsTr("Cancel")
            leftButton.onClicked: root.close()
            rightButton.enabled: true
            rightButton.highlighted: true
            rightButton.text: qsTr("Save")
            rightButton.onClicked: {
                root.accepted()
                root.close()
            }
        }

        Flickable {
            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true
            contentHeight: flickableLayout.implicitHeight
            interactive: contentHeight > height

            ColumnLayout {
                id: flickableLayout

                width: parent.width
                            spacing: 0

                ItemInput {
                    label: qsTr("Name")
                    text: name
                    onTextChanged: name = text
                }

                ThemedSwitchDelegate {
                    focus: true
                    text: qsTr("Archived")
                    Layout.fillWidth: true
                    checked: isArchived
                    onCheckedChanged: isArchived = checked
                }

                ThemedGroupTitle { text: qsTr("Aggregate") }
                Repeater {
                    model: [
                        TaskAggregate.Daily,
                        TaskAggregate.Weekly,
                        TaskAggregate.Monthly,
                    ]
                    ThemedRadioDelegate {
                        text: TaskAggregate.toString(modelData)
                        ButtonGroup.group: repeadModeGroup
                        checked: aggregateMode === modelData
                        onClicked: aggregateMode = modelData
                    }
                }

                ThemedGroupTitle { text: qsTr("Track") }
                Repeater {
                    model: [
                        TaskTrack.Duration,
                        TaskTrack.Count,
                    ]
                    ThemedRadioDelegate {
                        text: TaskTrack.toString(modelData)
                        ButtonGroup.group: trackModeGroup
                        checked: trackMode === modelData
                        onClicked: trackMode = modelData
                    }
                }

                Item { Layout.preferredHeight: Theme.PopupContentBottomPadding }
            }
        }
    }
}
