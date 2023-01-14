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
            model: taskListModel
            clip: true
            spacing: 10

            header: Item { implicitHeight: 10 }
            footer: Item { implicitHeight: 10 }

            delegate: Pane {
                width: ListView.view.width
                background: Rectangle {
                    radius: 10
                    color: isArchived ? palette.alternateBase : palette.base
                }

                ColumnLayout {
                    ThemedLabel {
                        text: name
                    }

                    ThemedSmallLabel {
                        text: scheduleModeText
                    }

                    ThemedSmallLabel {
                        visible: trackMode !== Task.NoTracking
                        text: trackModeText
                    }

                    ThemedSmallLabel {
                        visible: isArchived
                        text: qsTr("Archived")
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        taskListModel.load(Config.dataFolderLocation)
    }

    Component.onDestruction: {
        taskListModel.save(Config.dataFolderLocation)
    }
}
