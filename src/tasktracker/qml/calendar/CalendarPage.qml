import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import ".."
import "../theme"
import "../theme/Theme.js" as Theme

Item {
    id: root

    required property TaskModel taskModel
    required property AppHeader header

    property string title: ""

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        WeekView {
            id: weekView

            selectedDate: dayView.dateForIndex(dayView.currentIndex)
            onTodayClicked: dayView.currentIndex = dayView.indexForDate(today)

            Layout.fillWidth: true
            topPadding: Theme.PopupItemTopMargin
            bottomPadding: Theme.PopupItemTopMargin

            BottomSeparator {}
        }

        DayView {
            id: dayView

            Layout.fillWidth: true
            Layout.fillHeight: true

            sourceComponent: Component {
                DayHistory {
                    visibleTasksModel: TaskFilterModel {
                        sourceModel: taskModel
                        isDoneVisible: header.isDoneVisible
                        isArchivedVisible: header.isArchivedVisible
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
