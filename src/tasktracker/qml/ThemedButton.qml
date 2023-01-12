import QtQuick
import QtQuick.Controls

Button {
    id: root

    property string color: ""

    flat: true

    contentItem: Label {
        property color flatTextColor: root.color ? root.color : root.palette.button
        property color flatTextDownColor: Qt.lighter(flatTextColor, 1.2)

        text: root.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: root.flat ? (root.down ? flatTextDownColor : flatTextColor) : root.palette.buttonText
    }

    background: Rectangle {
        property color flatBackgroundColor: "transparent"
        property color backgroundColor: root.color ? root.color : root.palette.button
        property color backgroundDownColor: Qt.lighter(backgroundColor, 1.2)

        color: root.flat ? flatBackgroundColor
                         : (root.down ?  backgroundDownColor: backgroundColor)
        radius: root.height
    }
}
