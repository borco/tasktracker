import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Item {
    id: root

    property string text: ""

    Layout.fillWidth: true

    implicitHeight: Theme.ConfigGroupTitleHeight

    Label {
        text: parent.text
        anchors.left: parent.left
        anchors.leftMargin: Theme.ConfigLeftContentMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.ConfigGroupTitleBottomMargin

        font.weight: Theme.ConfigGroupTitleFontWeight
        font.capitalization: Font.SmallCaps
    }

    ConfigHorizontalSeparator {}
}