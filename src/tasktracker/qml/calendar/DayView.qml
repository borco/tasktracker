import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Item {
    id: root

    required property Component sourceComponent
    property int daysInPast: 356 * 10

    signal daysAdded(days: int)

    implicitWidth: swipeView.implicitWidth
    implicitHeight: swipeView.implicitHeight

    SwipeView {
        id: swipeView

        property int currentDelta: 0

        anchors.fill: parent

        currentIndex: daysInPast

        Repeater {
            id: repeater

            model: 2 * daysInPast

            Loader {
                active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                property int delta: index - daysInPast
                sourceComponent: root.sourceComponent
            }
        }

        onCurrentIndexChanged: {
            if (!currentItem)
                return

            let days = currentItem.delta - swipeView.currentDelta
            daysAdded(days)
            swipeView.currentDelta = currentItem.delta
        }
    }
}
