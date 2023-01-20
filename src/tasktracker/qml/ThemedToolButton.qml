import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Theme

ToolButton {
    id: root

    icon.color: checked ? palette.base : palette.button

    implicitWidth: Theme.toolButtonSize
    implicitHeight: Theme.toolButtonSize

    Layout.alignment: Qt.AlignVCenter

    Rectangle {
        anchors.fill: parent
        radius: Theme.toolButtonCheckedRadius
        visible: checked
        color: root.palette.button
    }
}
