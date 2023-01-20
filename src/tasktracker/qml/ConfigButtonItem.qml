import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: root

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

    BottomSeparator {}
}
