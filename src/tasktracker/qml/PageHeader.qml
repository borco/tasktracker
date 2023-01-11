import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Item {
    id: root

    signal showConfig()

    implicitHeight: Theme.PageHeaderHeight

    ThemedToolButton {
        anchors.right: parent.right
        anchors.rightMargin: Theme.PageHeaderRightMargin
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "../icons/settings.svg"
        onClicked: root.showConfig()
    }
}
