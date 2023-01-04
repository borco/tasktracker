import QtQuick
import QtQuick.Controls

ToolBar {
    id: control

    property alias logs: logsToolButton
    property alias logsVisible: logsToolButton.checked

    ToolButton {
        id: logsToolButton
        icon.source: "../icons/logs.svg"
        text: qsTr("Logs")
        checkable: true
    }
}
