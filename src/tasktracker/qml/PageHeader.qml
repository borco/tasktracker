import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Rectangle {
    id: root

    signal showConfig()

    component Title: ThemedLabel {
        font.pointSize: Theme.PageHeaderTitleSize
        font.weight: Theme.PageHeaderTitleWeight
    }

    component Layout: RowLayout {
        anchors.left: parent.left
        anchors.leftMargin: Theme.PageHeaderLeftMargin
        height: parent.height
    }

    color: palette.base

    implicitHeight: Theme.PageHeaderHeight

    ThemedToolButton {
        anchors.right: parent.right
        anchors.rightMargin: Theme.PageHeaderRightMargin
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "../icons/settings.svg"
        onClicked: root.showConfig()
    }
}
