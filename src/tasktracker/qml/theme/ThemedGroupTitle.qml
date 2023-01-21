import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Rectangle {
    id: root

    property string text: ""

    color: palette.window

    Layout.fillWidth: true

    implicitHeight: Theme.GroupTitleHeight

    ThemedLabel {
        text: parent.text
        anchors.left: parent.left
        anchors.leftMargin: Theme.ContentLeftMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.GroupTitleBottomMargin

        font.weight: Theme.GroupTitleFontWeight
    }

    BottomSeparator {}
}
