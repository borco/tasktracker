import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qt.labs.settings

import TaskTrackerLib

ColumnLayout {
    id: control

    function readCredentials() {
        KeyChain.readKey(usernameInput.text.trim())
    }

    function writeCredentials() {
        KeyChain.writeKey(usernameInput.text.trim(), passwordInput.text.trim())
    }

    function deleteCredentials() {
        KeyChain.deleteKey(usernameInput.text.trim())
    }

    GridLayout {
        Layout.fillWidth: true

        columns: 2
        columnSpacing: 20

        Label {
            text: qsTr('Username:')
        }

        TextField {
            id: usernameInput
            Layout.fillWidth: true
        }

        Label {
            text: qsTr('Password:')
        }

        Label {
            id: infoLabel

            Layout.fillWidth: true
            GridLayout.columnSpan: 2

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

        PasswordTextField {
            id: passwordInput
            Layout.fillWidth: true
        }
    }

    Switch {
        Layout.alignment: Qt.AlignRight
        text: qsTr('Keep password in key chain')
        checked: Config.storePasswordInKeyChain
    }

    Connections {
        target: KeyChain

        function onKeyStored(key) {
            infoLabel.text += String("Key '%1' successfully stored\n").arg(key)
            infoLabel.color = 'green'
            infoLabel.visible = true
        }

        function onKeyDeleted(key) {
            infoLabel.text += String("Key '%1' successfully deleted\n").arg(key)
            infoLabel.color = 'green'
            infoLabel.visible = true
        }

        function onKeyRestored(key, value) {
            infoLabel.text += String("Key '%1' successfully restored\n").arg(key)
            infoLabel.color = 'green'
            infoLabel.visible = true
            if (key === usernameInput.text.trim()) {
                passwordInput.text = value
            }
        }

        function onError(errorText) {
            infoLabel.text = errorText
            infoLabel.color = 'red'
            infoLabel.visible = true
        }
    }

    Settings {
        category: "Login.qml"
        property alias username: usernameInput.text
        property alias passwordEchoMode: passwordInput.echoMode
    }
}
