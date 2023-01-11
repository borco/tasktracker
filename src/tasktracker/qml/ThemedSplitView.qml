import QtQuick
import QtQuick.Controls

import "Theme.js" as Theme

SplitView {
    id: root

    property real hitAreaPadding: Theme.SplitViewHitAreaPadding + Theme.SplitViewSize / 2

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    handle: Rectangle {
        implicitWidth: root.orientation === Qt.Horizontal ? Theme.SplitViewSize : root.width
        implicitHeight: root.orientation === Qt.Horizontal ? root.height : Theme.SplitViewSize

        color: SplitHandle.pressed || SplitHandle.hovered
               ? root.palette.button
               : palette.dark

        // Increase the hit area
        containmentMask: Item {
            x: root.orientation === Qt.Horizontal ? -root.hitAreaPadding : 0
            y: root.orientation === Qt.Horizontal ? 0 : -root.hitAreaPadding
            width: root.orientation === Qt.Horizontal ? root.hitAreaPadding * 2 : root.width
            height: root.orientation === Qt.Horizontal ? root.height : root.hitAreaPadding * 2
        }
    }
}
