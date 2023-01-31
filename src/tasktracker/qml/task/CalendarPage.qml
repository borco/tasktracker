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

    required property TaskFilterModel taskFilterModel

    property string title: ""

    signal editDuration(taskDurationModelContext: var)
    signal addDuration(taskDurationModel: var)

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

                    visibleTasksModel: taskFilterModel
                    onEditDuration: (taskDurationModelContext) => root.editDuration(taskDurationModelContext)
                    onAddDuration: (taskDurationModel) => root.addDuration(taskDurationModel)
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
