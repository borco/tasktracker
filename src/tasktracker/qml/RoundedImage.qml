import QtQuick
import QtQuick.Effects

Item {
    id: root

    property string source: ""
    property int borderSize: 0
    property color borderColor: palette.light

    Rectangle {
        property int minSize: Math.min(root.width, root.height)

        visible: image.status === Image.Ready
        anchors.centerIn: parent
        color: borderSize > 0 ? root.borderColor : "transparent"
        width: minSize
        height: minSize
        radius: minSize

        MultiEffect {
            anchors.fill: parent
            anchors.margins: root.borderSize
            maskEnabled: true

            maskSource: Image {
                anchors.fill: parent
                source: "../icons/round_image.svg"
            }

            source: Image {
                id: image
                anchors.fill: parent
                source: root.source
            }
        }
    }
}
