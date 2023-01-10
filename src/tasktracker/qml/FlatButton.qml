import QtQuick
import QtQuick.Controls

Button {
    id: root

    property bool boldFont: true
    property color normalColor: palette.link
    property color downColor: Qt.darker(palette.link)

    leftPadding: 4
    rightPadding: 4

    contentItem: Label {
        text: root.text
        font.bold: root.boldFont
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? root.downColor : root.normalColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Item {}
}
