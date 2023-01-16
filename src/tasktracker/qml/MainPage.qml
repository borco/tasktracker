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

        RowLayout {
            anchors.left: parent.left
            height: parent.height

            MaskedImage {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height
                Layout.leftMargin: Theme.PageHeaderLeftMargin
                borderSize: 2
                source: TogglProxy.imageUrl
                maskSource: "../icons/avatar_mask.svg"
            }

            ThemedLabel { text: TogglProxy.fullname }

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

        BottomSeparator {}
    }

    TaskListModel {
        id: taskListModel
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

            delegate: TaskDelegate {}
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
