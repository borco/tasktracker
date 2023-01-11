import QtQuick
import QtQuick.Controls

Button {
    id: root

    flat: true

    contentItem: Label {
        text: root.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: root.flat ? (root.down ? Qt.lighter(root.palette.button, 1.2) : root.palette.button)
                         : root.palette.buttonText
    }

    background: Rectangle {
        color: root.flat ? "transparent"
                         : (root.down ? Qt.lighter(root.palette.button, 1.2) : root.palette.button)
        radius: root.height
    }
}
