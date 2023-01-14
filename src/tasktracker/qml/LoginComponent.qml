import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

ColumnLayout {
    id: control

    property int maximumWidth: 400

    function readCredentials() {
        KeyChain.readKey(usernameInput.text.trim())
    }

    function showErrorMessage(message) {
        infoLabel.text = message
        infoLabel.color = 'red'
        infoLabel.visible = true
    }

    Item { Layout.fillHeight: true }

    RowLayout {

        Item { Layout.fillWidth: true }

        ColumnLayout {
            Layout.maximumWidth: control.maximumWidth

            GroupBox {
                title: qsTr("Toggl Login Info")

                Layout.fillWidth: true
                contentHeight: togglLoginInfoLayout.implicitHeight
                               + togglLoginInfoLayout.anchors.topMargin
                               + togglLoginInfoLayout.anchors.bottomMargin

                ColumnLayout {
                    id: togglLoginInfoLayout

                    anchors.fill: parent
                    anchors.margins: 6

                    ThemedSmallLabel {
                        text: qsTr('Username:')
                    }

                    WrappedTextField {
                        id: usernameInput
                        Layout.fillWidth: true
                    }

                    ThemedSmallLabel {
                        text: qsTr('Password:')
                    }

                    PasswordTextField {
                        id: passwordInput
                        Layout.fillWidth: true
                    }
                }
            }

            ThemedSmallLabel {
                id: infoLabel

                Layout.fillWidth: true

                wrapMode: Text.Wrap
                visible: false

                onVisibleChanged: if (visible) hideAnimation.start();

                SequentialAnimation {
                    id: hideAnimation

                    PauseAnimation {
                        duration: 10000
                    }

                    ScriptAction {
                        script: {
                            infoLabel.visible = false
                            infoLabel.text = ''
                        }
                    }
                }
            }

            ThemedButton {
                id: loginButton
                text: qsTr("Login")

                flat: false
                highlighted: true
                Layout.fillWidth: true
                Layout.topMargin: 10

                onClicked: {
                    TogglProxy.username = usernameInput.text.trim()
                    TogglProxy.password = passwordInput.text
                    TogglProxy.logIn()
                }
            }
        }

        Item { Layout.fillWidth: true }
    }

    Item { Layout.fillHeight: true }

    Connections {
        target: TogglProxy

        function onLoggedWithUserAndPassword() {
            if (Config.storeSecretsInKeychain) {
                KeyChain.writeKey(TogglProxy.username, TogglProxy.password)
            }
        }
    }

    Connections {
        target: Config

        function onStoreSecretsInKeychainChanged() {
            if (Config.storeSecretsInKeychain) {
                readCredentials()
            }
        }
    }

    Connections {
        target: KeyChain

//        function onKeyStored(key) {
//            infoLabel.text += String("Key '%1' successfully stored\n").arg(key)
//            infoLabel.color = 'green'
//            infoLabel.visible = true
//        }

        function onKeyDeleted(key) {
            infoLabel.text += String("Key '%1' successfully deleted\n").arg(key)
            infoLabel.color = 'green'
            infoLabel.visible = true
        }

        function onKeyRestored(key, value) {
//            infoLabel.text += String("Key '%1' successfully restored\n").arg(key)
//            infoLabel.color = 'green'
//            infoLabel.visible = true
            if (key === usernameInput.text.trim()) {
                passwordInput.text = value
            }
        }

        function onError(errorText) {
            showErrorMessage(errorText)
        }
    }

    Settings {
        id: settings
        category: "Login"
        property alias username: usernameInput.text
        property alias passwordEchoMode: passwordInput.echoMode
    }

    Component.onCompleted: {
        if (settings.storeSecretsInKeychain) {
            readCredentials()
        }
    }
}
