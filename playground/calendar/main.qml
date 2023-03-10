import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "task"
import "theme"

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Calendar")

    Page {
        anchors.fill: parent

        background: Rectangle {
            color: palette.base
        }

        ColumnLayout {
            anchors.fill: parent

            WeekView {
                date: dayView.dateForIndex(dayView.currentIndex)
                Layout.fillWidth: true
                topPadding: 10
                onTodayClicked: dayView.currentIndex = dayView.indexForDate(today)
            }

            ThemedLabel {
                text: "current index: %1\ncurrent date: %2".arg(dayView.currentIndex).arg(dayView.dateForIndex(dayView.currentIndex).toLocaleString(Qt.locale(), "MMM dd, yyyy"))
            }

            DayView {
                id: dayView

                Layout.fillWidth: true
                Layout.fillHeight: true

                dayComponent: Component {
                    Rectangle {
                        color: palette.window

                        Text {
                            anchors.centerIn: parent
                            text: "index: %1\ndate: %2".arg(dayViewModel.index).arg(dayViewModel.date.toLocaleString(Qt.locale(), "MMM dd, yyyy"))
                        }
                    }
                }
            }
        }
    }

    Settings {
        category: "Main"
        property alias dayCurrentIndex: dayView.currentIndex
    }
}
