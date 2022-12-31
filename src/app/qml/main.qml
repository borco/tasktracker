import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings

Window {
    id: root

    function readCredentials(username) {
        KeyChain.readKey(username)
    }

    function writeCredentials(username, password) {
        KeyChain.writeKey(username, password)
    }

    function deleteCredentials(username) {
        KeyChain.deleteKey(username)
    }

    width: 640
    height: 480
    visible: true

    GridLayout {
        anchors.fill: parent
        anchors.margins: 20

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

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: passwordInput
                echoMode: TextInput.PasswordEchoOnEdit
                Layout.fillWidth: true
            }

            ToolButton {
                icon.source: passwordInput.echoMode === TextInput.PasswordEchoOnEdit
                             ? "../icons/password_hidden.svg"
                             : "../icons/password_visible.svg"
                onClicked: passwordInput.echoMode === TextInput.PasswordEchoOnEdit
                           ? passwordInput.echoMode = TextInput.Normal
                           : passwordInput.echoMode = TextInput.PasswordEchoOnEdit
            }
        }

        RowLayout {
            GridLayout.columnSpan: 2

            Button {
                Layout.preferredWidth: 80
                text: qsTr('Write')
                onClicked: writeCredentials(usernameInput.text.trim())
            }

            Button {
                Layout.preferredWidth: 80
                text: qsTr('Read')
                onClicked: readCredentials(usernameInput.text.trim())
            }

            Button {
                Layout.preferredWidth: 80
                text: qsTr('Delete')
                onClicked: deleteCredentials(usernameInput.text.trim())
            }
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

        Item {
            Layout.fillHeight: true
            GridLayout.columnSpan: 2
        }
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
        property alias username: usernameInput.text
        property alias passwordEchoMode: passwordInput.echoMode
    }

    Component.onCompleted: {
//        readCredentials()
    }
}
