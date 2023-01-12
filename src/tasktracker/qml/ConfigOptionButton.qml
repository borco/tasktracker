import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

ItemDelegate {
    id: root

    property string value: ""

    Layout.fillWidth: true

    contentItem: RowLayout {
        ThemedLabel {
            text: root.text
            Layout.fillWidth: true
            elide: Text.ElideRight
        }

        ThemedLabel { text: root.value + " ❯" }
    }

    BottomSeparator {}
}
