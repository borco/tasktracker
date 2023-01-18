import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Rectangle {
    id: root

    property alias title: title
    property alias configButton: configButton

    signal showConfig()

    component Layout: RowLayout {
        spacing: Theme.PageHeaderSpacing
        height: parent.height
        anchors.left: parent.title.right
        anchors.leftMargin: spacing
        anchors.right: parent.configButton.left
        anchors.rightMargin: spacing
    }

    color: palette.base

    implicitHeight: Theme.PageHeaderHeight

    ThemedLabel {
        id: title
        anchors.left: parent.left
        anchors.leftMargin: Theme.PageHeaderLeftMargin
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: Theme.PageHeaderTitleSize
        font.weight: Theme.PageHeaderTitleWeight
    }

    ThemedToolButton {
        id: configButton
        anchors.right: parent.right
        anchors.rightMargin: Theme.PageHeaderRightMargin
        anchors.verticalCenter: parent.verticalCenter
        icon.source: "../icons/settings.svg"
        onClicked: root.showConfig()
    }

    BottomSeparator {}
}
