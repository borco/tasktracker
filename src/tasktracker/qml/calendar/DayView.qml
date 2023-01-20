import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Item {
    id: root

    required property Component sourceComponent

    property alias currentIndex: swipeView.currentIndex

    function dateForIndex(index) { return dayModel.dateForIndex(index) }

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
                property date date: model.date
                property int index: model.index
                sourceComponent: root.sourceComponent
            }
        }

        Component.onCompleted:{
            contentItem.highlightMoveDuration = 0 //Set the moving time to 0
        }
    }
}
