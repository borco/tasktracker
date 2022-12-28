import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    readonly property string usernameKey: 'user'
    readonly property string passwordKey: 'password'

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

        TextField {
            id: passwordInput
            Layout.fillWidth: true
        }

        RowLayout {
            GridLayout.columnSpan: 2

            Button {
                Layout.preferredWidth: 80
                text: qsTr('Store')

                onClicked: {
                    KeyChain.writeKey(usernameKey, usernameInput.text.trim())
                    KeyChain.writeKey(passwordKey, passwordInput.text.trim())
                }
            }

            Button {
                Layout.preferredWidth: 80
                text: qsTr('Restore')

                onClicked: {
                    KeyChain.readKey(usernameKey)
                    KeyChain.readKey(passwordKey)
                }
            }

            Button {
                Layout.preferredWidth: 80
                text: qsTr('Delete')

                onClicked: {
                    KeyChain.deleteKey(usernameKey)
                    KeyChain.deleteKey(passwordKey)
                }
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
                    script: infoLabel.visible = false
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
            infoLabel.text = String("Key '%1' successfully stored").arg(key)
            infoLabel.color = 'green'
            infoLabel.visible = true
        }

        function onKeyDeleted(key) {
            infoLabel.text = String("Key '%1' successfully deleted").arg(key)
            infoLabel.color = 'green'
            infoLabel.visible = true
        }

        function onKeyRestored(key, value) {
            infoLabel.text = String("Key '%1' successfully restored with data '%2'").arg(key).arg(value)
            infoLabel.color = 'green'
            infoLabel.visible = true
            switch (key) {
            case usernameKey:
                usernameInput.text = value
                break
            case passwordKey:
                passwordInput.text = value
                break
            }
        }

        function onError(errorText) {
            infoLabel.text = errorText
            infoLabel.color = 'red'
            infoLabel.visible = true
        }
    }
}
