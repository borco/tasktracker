import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Item {
    id: root

    required property Component dayComponent

    property alias currentIndex: swipeView.currentIndex

    function dateForIndex(index) { return dayModel.dateForIndex(index) }
    function indexForDate(date) { return dayModel.indexForDate(date) }

    implicitWidth: swipeView.implicitWidth
    implicitHeight: swipeView.implicitHeight

    DayModel { id: dayModel }

    SwipeView {
        id: swipeView

        anchors.fill: parent

        currentIndex: dayModel.indexForDate(new Date())

        Repeater {
            id: repeater

            model: dayModel

            Loader {
                active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                required property var model
                sourceComponent: root.dayComponent
            }
        }

        Component.onCompleted:{
            contentItem.highlightMoveDuration = 0 //Set the moving time to 0
        }
    }
}
