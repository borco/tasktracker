import QtQuick
import QtQuick.Controls

TextField {
    id: control

    echoMode: TextInput.PasswordEchoOnEdit

    rightPadding: echoToggleImage.width
                  + 2 * echoToggleImage.anchors.rightMargin

    Image {
        id: echoToggleImage

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.rightMargin: 4

        fillMode: Image.PreserveAspectFit

        source: control.echoMode === TextInput.PasswordEchoOnEdit
                ? "../icons/password_hidden.svg"
                : "../icons/password_visible.svg"

        MouseArea {
            anchors.fill: parent
            onClicked: control.echoMode === TextInput.PasswordEchoOnEdit
                       ? control.echoMode = TextInput.Normal
                       : control.echoMode = TextInput.PasswordEchoOnEdit
        }
    }
}
