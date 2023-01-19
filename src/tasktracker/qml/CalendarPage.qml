import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "calendar"
import "Theme.js" as Theme

Page {
    id: root

    required property TaskListModel taskListModel

    signal showConfig()

    background: null

    header: PageHeader {
        title.text: root.title

        onShowConfig: root.showConfig()

        PageHeader.Layout {
            TogglLoggedStatus {}

            Item { Layout.fillWidth: true }

            ThemedToolButton {
                id: archivedToggle
                icon.source: "../icons/archived.svg"
                checkable: true
            }

            ThemedToolButton {
                id: doneToggle
                icon.source: "../icons/task/done.svg"
                checkable: true
            }
        }
    }

    WeekModel {
        id: weekModel
        currentDate: new Date()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        WeekView {
            id: weekView
            Layout.fillWidth: true
            model: weekModel
            topPadding: Theme.PopupItemTopMargin
            bottomPadding: Theme.PopupItemTopMargin

            BottomSeparator {}
        }

        DayView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            sourceComponent: Component {
                DayHistory {
                    currentDate: {
                        let date = new Date()
                        date.setDate(weekView.today.getDate() + delta)
                        return date
                    }
                    visibleTasksModel: TaskListFilterModel {
                        sourceModel: taskListModel
                        showDone: doneToggle.checked
                        showArchived: archivedToggle.checked
                    }
                }
            }

            onDaysAdded: (days) => weekModel.addDays(days)
        }
    }
}
