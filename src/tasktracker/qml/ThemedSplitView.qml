import QtQuick
import QtQuick.Controls

import Theme

SplitView {
    id: root

    property bool inDarkMode: palette.text > palette.base
    property real hitAreaPadding: Theme.splitViewHitAreaPadding + Theme.splitViewSize / 2

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    handle: Rectangle {
        implicitWidth: root.orientation === Qt.Horizontal ? Theme.splitViewSize : root.width
        implicitHeight: root.orientation === Qt.Horizontal ? root.height : Theme.splitViewSize

        color: SplitHandle.pressed || SplitHandle.hovered
               ? palette.highlight
               : (inDarkMode ? palette.light : palette.dark)

        // Increase the hit area
        containmentMask: Item {
            x: root.orientation === Qt.Horizontal ? -root.hitAreaPadding : 0
            y: root.orientation === Qt.Horizontal ? 0 : -root.hitAreaPadding
            width: root.orientation === Qt.Horizontal ? root.hitAreaPadding * 2 : root.width
            height: root.orientation === Qt.Horizontal ? root.height : root.hitAreaPadding * 2
        }
    }
}
