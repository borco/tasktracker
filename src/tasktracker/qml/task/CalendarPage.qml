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

    signal editDuration(taskDurationModelContext: var)

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        WeekView {
            id: weekView

            date: dayView.dateForIndex(dayView.currentIndex)
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

            dayComponent: Component {
                DayTasks {
                    editButtonVisible: false

                    visibleTasksModel: TaskFilterModel {
                        sourceModel: taskModel
                        isDoneVisible: header.isDoneVisible
                        isArchivedVisible: header.isArchivedVisible
                    }

                    onEditDuration: (taskDurationModelContext) => root.editDuration(taskDurationModelContext)
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
