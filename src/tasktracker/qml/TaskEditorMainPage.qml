import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

import TaskTrackerLib

Page {
    id: root

    property var model

    property int labelWidth: 60

    signal done()

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

    title: qsTr("Task Editor")

    background: null

    header: ConfigPageHeader {
        title: root.title

        leftButton.visible: false
        rightButton.enabled: true
        rightButton.highlighted: true
        rightButton.text: qsTr("Done")
        rightButton.onClicked: root.done()
    }

    Flickable {
        anchors.fill: parent

        contentHeight: layout.implicitHeight
        clip: true
        interactive: contentHeight > height

        ColumnLayout {
            id: layout

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

            Item { Layout.preferredHeight: Theme.PopupContentBottomPadding }
        }
    }
}
