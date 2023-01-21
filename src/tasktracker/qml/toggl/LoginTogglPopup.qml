import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

ThemedPopup {
    id: root

    property int maximumWidth: 400
    property string title: qsTr("Toggl Login")

    function readCredentials() {
        KeyChain.readKey(usernameInput.text.trim())
    }

    function showErrorMessage(message) {
        infoLabel.text = message
        infoLabel.color = Theme.ErrorColor
    }

    modal: true

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    parent: Overlay.overlay
    anchors.centerIn: parent

    contentWidth: contentLayout.implicitWidth
    contentHeight: contentLayout.implicitHeight

    ColumnLayout {
        id: contentLayout

        anchors.fill: parent
        spacing: 0

        ConfigPageHeader {
            title: root.title

            Layout.fillWidth: true

            leftButton.visible: true
            leftButton.onClicked: close()
            rightButton.visible: false
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.leftMargin: Theme.ContentLeftMargin
            Layout.rightMargin: Theme.ContentRightMargin
            Layout.topMargin: Theme.PopupItemTopMargin
            Layout.bottomMargin: Theme.PopupContentBottomPadding

            ThemedSmallLabel {
                text: qsTr('Username:')
                Layout.fillWidth: true
            }

            WrappedTextField {
                id: usernameInput
                text: TogglProxy.username
                Layout.fillWidth: true
            }

            ThemedSmallLabel {
                text: qsTr('Password:')
                Layout.fillWidth: true
            }

            PasswordTextField {
                id: passwordInput
                Layout.fillWidth: true
            }

            ThemedSmallLabel {
                id: infoLabel

                Layout.preferredWidth: passwordInput.width

                elide: Text.ElideRight

                onTextChanged: if (infoLabel.text !== '') clearTextAnimation.start();

                SequentialAnimation {
                    id: clearTextAnimation

                    PauseAnimation {
                        duration: 10000
                    }

                    ScriptAction {
                        script: {
                            infoLabel.text = ""
                            TogglProxy.loginError = ""
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
    }

    BusyIndicator {
        id: busyIndicator
        visible: false
        running: visible
        anchors.centerIn: parent
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
        target: TogglProxy

        function onLoggedStatusChanged() {
            if (TogglProxy.loggedStatus === TogglProxy.LoggedUnknown) {
                busyIndicator.visible = true
                contentLayout.enabled = false
            } else {
                contentLayout.enabled = true
                busyIndicator.visible = false
            }
        }

        function onLoggedWithUserAndPassword() {
            if (Config.storeSecretsInKeychain) {
                KeyChain.writeKey(TogglProxy.username, TogglProxy.password)
            }
            close()
        }

        function onLoginErrorChanged() {
            if (TogglProxy.loginError !== "") {
                showErrorMessage(TogglProxy.loginError)
            }
        }
    }

    Connections {
        target: KeyChain

        function onKeyDeleted(key) {
            infoLabel.text += String("Key '%1' successfully deleted\n").arg(key)
            infoLabel.color = 'green'
        }

        function onKeyRestored(key, value) {
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
        property alias passwordEchoMode: passwordInput.echoMode
    }

    Component.onCompleted: {
        if (settings.storeSecretsInKeychain) {
            readCredentials()
        }
    }
}
