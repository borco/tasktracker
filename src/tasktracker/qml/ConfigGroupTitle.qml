import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Theme

Rectangle {
    id: root

    property string text: ""

    color: palette.window

    Layout.fillWidth: true

    implicitHeight: Theme.configGroupTitleHeight

    ThemedLabel {
        text: parent.text
        anchors.left: parent.left
        anchors.leftMargin: Theme.contentLeftMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: Theme.configGroupTitleBottomMargin

        font.weight: Theme.configGroupTitleFontWeight
    }

    BottomSeparator {}
}
