import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib
import Theme

import ".."
import "../calendar"

Item {
    id: root

    required property TaskListModel taskListModel
    required property AppHeader header

    property string title: ""

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        WeekView {
            id: weekView

            currentDate: dayView.dateForIndex(dayView.currentIndex)
            onTodayClicked: dayView.currentIndex = dayView.indexForDate(today)

            Layout.fillWidth: true
            topPadding: Theme.popupItemTopMargin
            bottomPadding: Theme.popupItemTopMargin

            BottomSeparator {}
        }

        DayView {
            id: dayView

            Layout.fillWidth: true
            Layout.fillHeight: true

            sourceComponent: Component {
                DayHistory {
                    visibleTasksModel: TaskListFilterModel {
                        sourceModel: taskListModel
                        doneVisible: header.doneVisible
                        archivedVisible: header.archivedVisible
                    }
                }
            }
        }
    }

    Settings {
        id: settings
        category: "Calendar"
        property alias dayViewCurrentIndex: dayView.currentIndex
    }
}
