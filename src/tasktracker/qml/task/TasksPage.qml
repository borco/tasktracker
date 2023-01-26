import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import ".."

Item {
    id: root

    required property TaskModel taskModel
    required property AppHeader header

    property string title: ""

    TaskEditorPopup {
        id: taskEditorPopup
    }

    ColumnLayout {
        anchors.fill: parent

        DayTasks {
            QtObject {
                id: dayViewModel
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

            onEdit: (dayViewTaskModel) => {
                        taskEditorPopup.model = dayViewTaskModel
                        taskEditorPopup.open()
                    }
        }
    }
}
