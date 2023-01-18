import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

Page {
    id: root

    signal showConfig()

    background: null

    header: PageHeader {
        onShowConfig: root.showConfig()

        PageHeader.Layout {

            PageHeader.Title { text: root.title }

            ToolSeparator {}

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

            ToolSeparator {}

            ThemedToolButton {
                id: toggleStatusButton
                icon.source: "../icons/toggl.svg"
                icon.color: TogglProxy.loggedStatus === TogglProxy.LoggedIn ? "#E57CD8" : palette.dark
                icon.width: parent.height - 2 * padding
                icon.height: parent.height - 2 * padding
                padding: 1
            }
        }

        BottomSeparator {}
    }

    TaskListModel {
        id: taskListModel
    }

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
                showDone: doneToggle.checked
                showArchived: archivedToggle.checked
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

    Settings {
        category: "Main"
        property alias showArchived: archivedToggle.checked
        property alias showDone: doneToggle.checked
    }

    Component.onCompleted: {
        taskListModel.load(Config.dataFolderLocation)
    }

    Component.onDestruction: {
        taskListModel.save(Config.dataFolderLocation)
    }
}
