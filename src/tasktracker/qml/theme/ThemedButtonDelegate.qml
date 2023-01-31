import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

ItemDelegate {
    id: root

    property alias separatorVisible: separator.visible

    Layout.fillWidth: true

    contentItem: ThemedLabel {
        rightPadding: root.spacing
        text: root.text
        font: root.font
        color: root.enabled
               ? (
                     root.down
                     ? Qt.darker(root.palette.button)
                     : root.palette.button
                  )
               : Qt.lighter(root.palette.button)
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    background: Rectangle {
        implicitHeight: 44
        color: root.palette.base
    }

    BottomSeparator { id: separator }
}
