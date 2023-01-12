import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

ToolBar {
    id: root

    property string title: ""
    property alias innerContentItem: content.contentItem

    RowLayout {
        anchors.fill: parent

        ThemedLabel {
            text: root.title
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignVCenter
            Layout.leftMargin: Theme.ContentLeftMargin
        }

        ToolSeparator {}

        Control {
            id: content
            Layout.fillHeight: true
        }

        Item { Layout.fillWidth: true }
    }
}
