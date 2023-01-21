import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

ToolButton {
    id: root

    icon.color: checked ? palette.base : palette.button

    implicitWidth: Theme.ToolButtonSize
    implicitHeight: Theme.ToolButtonSize

    Layout.alignment: Qt.AlignVCenter

    Rectangle {
        anchors.fill: parent
        radius: Theme.ToolButtonCheckedRadius
        visible: checked
        color: root.palette.button
    }
}
