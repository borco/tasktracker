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

        ListView {
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: TaskFilterModel {
                sourceModel: taskModel
                isDoneVisible: header.isDoneVisible
                isArchivedVisible: header.isArchivedVisible
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
