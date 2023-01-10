import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

import TaskTrackerLib

Page {
    id: root

    property alias logsVisible: logsVisibleSwitch.checked

    property int leftContentMargin: 20
    property int rightContentMargin: 8
    property int itemHeight: 28
    property int groupTitleHeight: 40
    property int groupTitleBottomMargin: 4

    signal done()

    component Separator: Rectangle {
        height: 1
        color: palette.dark
        width: parent.width
        anchors.bottom: parent.bottom
    }

    component FlatButton: Button {
        id: flatButton

        property bool boldFont: true
        property color normalColor: palette.link
        property color downColor: Qt.darker(palette.link)

        leftPadding: 4
        rightPadding: 4

        contentItem: Label {
            text: flatButton.text
            font.bold: flatButton.boldFont
            opacity: enabled ? 1.0 : 0.3
            color: flatButton.down ? flatButton.downColor : flatButton.normalColor
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

        implicitHeight: root.itemHeight
        Layout.fillWidth: true

        ItemBackground {}

        RowLayout {
            id: switchItemLayout

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: root.leftContentMargin
            anchors.right: parent.right
            anchors.rightMargin: root.rightContentMargin

            Label {
                text: switchItem.text
                Layout.fillWidth: true
                elide: Text.ElideRight
            }

            Switch {
                id: switchItemSwitch
                rightPadding: 0
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
            width: parent.width
            text: buttonItem.text
            onClicked: buttonItem.clicked()
        }
    }

    component OptionButton: Button {
        id: optionButton

        property string value: ""

        implicitHeight: root.itemHeight

        Layout.fillWidth: true

        background: ItemBackground {}

        leftPadding: 0
        rightPadding: 0

        contentItem: Item {

            RowLayout {
                id: optionItemLayout

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: root.leftContentMargin
                anchors.right: parent.right
                anchors.rightMargin: root.rightContentMargin

                Label {
                    text: optionButton.text
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                }

                Label {
                    text: optionButton.value + " ❯"
                }
            }
        }
    }

    title: qsTr("Settings")

    padding: 0

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
            anchors.rightMargin: root.rightContentMargin
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

            GroupTitle { text: qsTr("Security and Privacy") }

            SwitchItem {
                id: storeSecretsInKeychain
                text: qsTr('Store sensitive data in key-chain')
                checked: Config.storeSecretsInKeychain
                onCheckedChanged: Config.storeSecretsInKeychain = checked
            }

            OptionButton {
                text: qsTr("Data folder location")
                value: Config.dataFolderLocation
                onClicked: console.log("select data location")
            }

            GroupTitle { text: qsTr("Misc") }

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
