import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

ThemedPopup {
    id: root

    property var model

    property string title: qsTr("Task Editor")

    property int labelWidth: 60

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

    onOpened: model.isEdited = true

    onClosed: {
        model.isEdited = false
        model = null
    }

    ThemedOptionsPopup {
        id: trackModePopup

        title: qsTr("Track Mode")

        Component.onCompleted: {
            [
            TaskTrackMode.Count,
            TaskTrackMode.Duration,
            ]
            .forEach(option =>
                     options.append({
                                        name: TaskTrackMode.toString(option),
                                        value: option
                                    }))
        }

        onClicked: (trackMode) => model.trackMode = trackMode
    }

    ColumnLayout {
        id: contentLayout

        anchors.fill: parent
        spacing: 0

        ConfigPageHeader {
            title: root.title

            Layout.fillWidth: true

            leftButton.visible: false
            rightButton.enabled: true
            rightButton.highlighted: true
            rightButton.text: qsTr("Done")
            rightButton.onClicked: root.done()
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
                    text: model ? model.name : ""
                    onTextChanged: if (model) model.name = text
                }

                ConfigSwitchItem {
                    property var model: root.model
                    focus: true
                    text: qsTr("Archived")
                    Layout.fillWidth: true
                    checked: model ? model.isArchived: false
                    onCheckedChanged: if (model) model.isArchived = checked
                }

                ConfigOptionButton {
                    text: qsTr("Schedule Mode")
                    value: model ? TaskRepeatMode.toString(model.repeatMode) : ""
                }

                ConfigOptionButton {
                    text: qsTr("Track Mode")
                    value: model ? TaskTrackMode.toString(model.trackMode) : ""
                    onClicked: trackModePopup.open()
                }

                Item { Layout.preferredHeight: Theme.PopupContentBottomPadding }
            }
        }
    }
}
