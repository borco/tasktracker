import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Rectangle {
    id: root

    property string text: ""

    color: palette.window

    Layout.fillWidth: true

    implicitHeight: Theme.ConfigGroupTitleHeight

    ThemedLabel {
        text: parent.text
        anchors.left: parent.left
        anchors.leftMargin: Theme.ContentLeftMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.ConfigGroupTitleBottomMargin

        font.weight: Theme.ConfigGroupTitleFontWeight
    }

    BottomSeparator {}
}
