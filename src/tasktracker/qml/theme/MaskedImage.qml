import QtQuick
import QtQuick.Effects

// MultiEffect docs: https://doc-snapshots.qt.io/qt6-dev/qml-qtquick-effects-multieffect.html

Item {
    id: root

    property string source: ""
    property string maskSource: ""

    property int topPadding: 4
    property int bottomPadding: 4
    property int leftPadding: 0
    property int rightPadding: 0

    property int borderSize: 0

    property color borderColor: palette.light

    Item {
        property int minSize: Math.min(
                                  root.width - root.leftPadding - root.rightPadding,
                                  root.height - root.topPadding - root.bottomPadding
                                  )

        visible: image.status === Image.Ready

        x: root.leftPadding
        y: root.topPadding

        width: minSize
        height: minSize

        MultiEffect {
            visible: borderSize > 0 && maskImage.status === Image.Ready
            anchors.fill: parent

            colorize: 1
            colorizeColor: root.borderColor

            source: Image {
                id: maskImage
                anchors.fill: parent
                source: root.maskSource
            }
        }

        MultiEffect {
            anchors.fill: parent
            anchors.margins: root.borderSize

            maskEnabled: true
            maskSource: Image {
                anchors.fill: parent
                source: root.maskSource
            }

            source: Image {
                id: image
                anchors.fill: parent
                source: root.source
            }
        }
    }
}
