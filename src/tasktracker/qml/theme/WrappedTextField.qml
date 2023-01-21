import QtQuick
import QtQuick.Controls

Item {
    id: root

    property alias text: textField.text
    property alias rightPadding: textField.rightPadding
    property alias echoMode: textField.echoMode

    implicitHeight: textField.implicitHeight

    TextField {
        id: textField
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
    }
}
