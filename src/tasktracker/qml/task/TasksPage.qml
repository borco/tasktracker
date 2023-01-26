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

    signal edit(dayViewTaskModel: var)

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.topMargin: Theme.ContentTopMargin
            Layout.leftMargin: Theme.ContentLeftMargin
            Layout.rightMargin: Theme.ContentRightMargin

            ThemedLabel {
                text: dayTasks.dayViewModel.date.toLocaleString(Qt.locale(), qsTr("dddd, MMM d, yyyy"))
                font.pointSize: Theme.SmallLabelSize
                font.bold: true

                Layout.fillWidth: true
            }

            ThemedButton {
                text: qsTr("Today")
                highlighted: false
                onClicked: dayTasks.dayViewModel.date = new Date()
            }
        }

        DayTasks {
            id: dayTasks

            property var dayViewModel: QtObject {
                property date date: new Date()
            }

            Layout.fillWidth: true
            Layout.fillHeight: true

            editButtonVisible: true

            visibleTasksModel: TaskFilterModel {
                sourceModel: taskModel
                isDoneVisible: header.isDoneVisible
                isArchivedVisible: header.isArchivedVisible
            }

            onEdit: (dayViewTaskModel) => root.edit(dayViewTaskModel)
        }
    }
}
