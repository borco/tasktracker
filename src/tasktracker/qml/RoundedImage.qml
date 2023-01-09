import QtQuick

import Qt5Compat.GraphicalEffects

Item {
    id: root

    property string source: ""
    property int borderSize: 0
    property color borderColor: palette.light

    Rectangle {
        visible: image.status === Image.Ready
        property int minSize: Math.min(root.width, root.height)
        color: root.borderColor
        anchors.centerIn: parent
        width: minSize
        height: minSize
        radius: minSize
    }

    Image {
        id: image

        property int minSize: Math.min(root.width, root.height) - 2 * root.borderSize

        source: root.source
        sourceSize: Qt.size(minSize, minSize)

        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Item {
                width: image.width
                height: image.height

                Rectangle {
                    anchors.fill: parent
                    radius: width
                }
            }
        }
    }
}
