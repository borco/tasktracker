import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Item {
    id: root

    required property Component sourceComponent

    // daysInPast controls how far in the past or in the future we can go
    // example: 365 * 10 will let us go for roughly 10 years in the past or in the future
    property int daysInPast: 356 * 10

    property alias currentIndex: swipeView.currentIndex

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

        Component.onCompleted:{
            contentItem.highlightMoveDuration = 0 //Set the moving time to 0
        }
    }
}
