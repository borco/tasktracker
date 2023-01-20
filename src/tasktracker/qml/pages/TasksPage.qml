import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import ".."
//import "../Theme.js" as Theme

Item {
    id: root

    required property TaskListModel taskListModel
    required property AppHeader header

    property string title: ""

    TaskEditorPopup {
        id: taskEditorPopup
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: TaskListFilterModel {
                sourceModel: taskListModel
                doneVisible: header.doneVisible
                archivedVisible: header.archivedVisible
            }

            clip: true
            spacing: 10

            header: Item { implicitHeight: 10 }
            footer: Item { implicitHeight: 10 }

            delegate: TaskDelegate {
                width: ListView.view.width
                onEdit: {
                    taskEditorPopup.model = model
                    taskEditorPopup.open()
                }
            }
        }
    }
}
