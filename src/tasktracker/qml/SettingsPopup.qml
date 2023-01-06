import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qt.labs.settings

import TaskTrackerLib

Dialog {
    id: root

    property alias logsVisible: logsVisibleSwitch.checked

    property int leftContentMargin: 20
    property int groupTitleHeight: 40
    property int groupTitleBottomMargin: 4

    component Separator: Rectangle {
        height: 1
        color: "#404040A0"
        width: parent.width
        anchors.bottom: parent.bottom
    }

    component ItemBackground: Rectangle {
        anchors.fill: parent
        color: palette.light

        Separator {}
    }

    component GroupTitle: Item {
        property string text: ""

        Layout.fillWidth: true

        implicitHeight: root.groupTitleHeight

        Label {
            text: parent.text
            anchors.left: parent.left
            anchors.leftMargin: root.leftContentMargin
            anchors.bottom: parent.bottom
            anchors.bottomMargin: root.groupTitleBottomMargin

            font.weight: 400
            font.capitalization: Font.SmallCaps
        }

        Separator {}
    }

    component SwitchItem: Item {
        id: switchItem

        property string text: ""
        property alias checked: switchItemSwitch.checked

        implicitHeight: switchItemLayout.implicitHeight
        Layout.fillWidth: true

        ItemBackground {}

        RowLayout {
            id: switchItemLayout

            anchors.left: parent.left
            anchors.leftMargin: root.leftContentMargin
            anchors.right: parent.right

            Label {
                text: switchItem.text
                Layout.fillWidth: true
                elide: Text.ElideRight
            }

            Switch {
                id: switchItemSwitch
            }
        }
    }

    component FlatButton: Button {
        id: flatButton

        leftPadding: 4
        rightPadding: 4

        contentItem: Label {
            text: flatButton.text
            font.bold: true
            opacity: enabled ? 1.0 : 0.3
            color: flatButton.down ? Qt.darker(palette.link) : palette.link
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Item {}
    }

    title: qsTr("Settings")

    modal: true
    padding: 0

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 200
        color: palette.alternateBase
        radius: 6
    }

    header: Item {
        implicitHeight: 30

        Label {
            text: root.title
            anchors.centerIn: parent
            font.bold: true
        }

        FlatButton {
            text: qsTr("Done")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 6
            onClicked: accept()
        }

        Separator {}
    }

    contentItem: Flickable {

        contentHeight: layout.implicitHeight
        clip: true

        ColumnLayout {
            id: layout

            width: parent.width
            spacing: 0

            GroupTitle {
                text: qsTr("Security and Privacy")
            }

            SwitchItem {
                id: storePasswordInKeyChain
                text: qsTr('Store sensitive data in key-chain')
                checked: Config.storePasswordInKeyChain
                onCheckedChanged: Config.storePasswordInKeyChain = checked
            }

            GroupTitle {
                text: qsTr("Misc")
            }

            SwitchItem {
                id: logsVisibleSwitch
                text: qsTr('Show logs')
            }
        }
    }

    Settings {
        id: settings
        category: "SettingsPopup"
        property alias storePasswordInKeyChain: storePasswordInKeyChain.checked
        property alias logsVisible: logsVisibleSwitch.checked
    }
}
