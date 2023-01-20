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

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        WeekView {
            id: weekView

            currentDate: dayView.dateForIndex(dayView.currentIndex)

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
                    visibleTasksModel: TaskListFilterModel {
                        sourceModel: taskListModel
                        showDone: doneToggle.checked
                        showArchived: archivedToggle.checked
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
