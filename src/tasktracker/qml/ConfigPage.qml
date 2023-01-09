import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

import TaskTrackerLib

Page {
    id: root

    property alias logsVisible: logsVisibleSwitch.checked

    property int leftContentMargin: 20
    property int groupTitleHeight: 40
    property int groupTitleBottomMargin: 4

    signal done()

    component Separator: Rectangle {
        height: 1
        color: "#404040A0"
        width: parent.width
        anchors.bottom: parent.bottom
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

    component ButtonItem: Item {
        id: buttonItem

        property string text: ""
        signal clicked()

        implicitHeight: buttonItemButton.implicitHeight
        Layout.fillWidth: true

        ItemBackground {}

        FlatButton {
            id: buttonItemButton
            anchors.centerIn: parent
            text: buttonItem.text
            onClicked: buttonItem.clicked()
        }
    }

    title: qsTr("Settings")

    padding: 0

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 200
        color: palette.alternateBase
        radius: 6
    }

    header: Item {
        implicitHeight: Theme.PageHeaderHeight

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
            onClicked: root.done()
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
                id: storeSecretsInKeychain
                text: qsTr('Store sensitive data in key-chain')
                checked: Config.storeSecretsInKeychain
                onCheckedChanged: Config.storeSecretsInKeychain = checked
            }

            GroupTitle {
                text: qsTr("Misc")
            }

            SwitchItem {
                id: logsVisibleSwitch
                text: qsTr('Show logs')
                checked: Config.logsVisible
                onCheckedChanged: Config.logsVisible = checked
            }

            GroupTitle {
                visible: TogglProxy.loggedStatus === TogglProxy.LoggedIn
            }

            ButtonItem {
                visible: TogglProxy.loggedStatus === TogglProxy.LoggedIn
                text: qsTr("Log Out")
                onClicked: TogglProxy.logOut()
            }
        }
    }
}
