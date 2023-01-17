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

    background: null

    header: ConfigPageHeader {
        title: root.title
        leftButton.visible: false
        rightButton.enabled: true
        rightButton.highlighted: true
        rightButton.text: qsTr("Done")
        rightButton.onClicked: root.done()
    }

    LoginTogglPopup {
        id: signInTogglPopup
    }

    ThemedMessageBox {
        id: signOutMessageBox
        title: qsTr("Signing Out?")
        text: qsTr("Are you sure you want to sign out of\nyour account?")

        leftButton.text: qsTr("Cancel")
        rightButton.text: qsTr("Sign Out")
        rightButton.color: Theme.DangerColor

        onAccepted: {
            TogglProxy.logOut()
        }
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
                text: qsTr("Toggl")
            }

            ConfigButtonItem {
                text: TogglProxy.loggedStatus === TogglProxy.LoggedIn ? qsTr("Sign Out") : qsTr("Sign In")
                enabled: TogglProxy.loggedStatus !== TogglProxy.LoggedUnknown
                onClicked: {
                    if (TogglProxy.loggedStatus === TogglProxy.LoggedIn) {
                        signOutMessageBox.open()
                    } else {
                        signInTogglPopup.open()
                    }
                }
            }

            Item { Layout.preferredHeight: Theme.ConfigGroupTitleHeight }
        }
    }
}
