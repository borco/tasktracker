import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Flickable {
    id: root

    contentHeight: layout.implicitHeight
    clip: true

    ColumnLayout {
        id: layout

        width: parent.width
        spacing: 0

        ConfigGroupTitle { text: qsTr("Security and Privacy") }

        ConfigSwitchItem {
            id: storeSecretsInKeychain
            text: qsTr('Store sensitive data in key-chain')
            checked: Config.storeSecretsInKeychain
            onCheckedChanged: Config.storeSecretsInKeychain = checked
        }

        ConfigOptionButton {
            text: qsTr("Data folder location")
            value: Config.dataFolderLocation
            onClicked: console.log("select data location")
        }

        ConfigGroupTitle { text: qsTr("Misc") }

        ConfigSwitchItem {
            id: logsVisibleSwitch
            text: qsTr('Show logs')
            checked: Config.logsVisible
            onCheckedChanged: Config.logsVisible = checked
        }

        ConfigGroupTitle {
            visible: TogglProxy.loggedStatus === TogglProxy.LoggedIn
        }

        ConfigButtonItem {
            visible: TogglProxy.loggedStatus === TogglProxy.LoggedIn
            text: qsTr("Log Out")
            onClicked: TogglProxy.logOut()
        }
    }
}
