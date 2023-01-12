import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Item {
    id: root

    property string text: ""

    Layout.fillWidth: true

    implicitHeight: Theme.ConfigGroupTitleHeight

    ThemedLabel {
        text: parent.text
        anchors.left: parent.left
        anchors.leftMargin: Theme.ContentLeftMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.ConfigGroupTitleBottomMargin

        font.weight: Theme.ConfigGroupTitleFontWeight
        font.capitalization: Font.SmallCaps
    }

    BottomSeparator {}
}
