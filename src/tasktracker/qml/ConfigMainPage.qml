import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

import TaskTrackerLib

Page {
    id: root

    signal done()
    signal selectDataFolderLocation()

    title: qsTr("Settings")

    header: ConfigPageHeader {
        title: root.title
        leftButtonVisible: false
        rightButtonEnabled: true
        rightButtonText: qsTr("Done")
        onRightButtonClicked: root.done()
    }

    Flickable {
        anchors.fill: parent

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
                onClicked: root.selectDataFolderLocation()
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
}
