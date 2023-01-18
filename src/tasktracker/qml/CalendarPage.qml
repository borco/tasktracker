import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

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

    Flickable {
        anchors.fill: parent

        ColumnLayout {
            id: topLayout

            Repeater {
                model: TaskListFilterModel {
                    sourceModel: taskListModel
                    showDone: doneToggle.checked
                    showArchived: archivedToggle.checked
                }

                delegate: ColumnLayout {
                    Layout.fillWidth: true
                    ConfigGroupTitle {
                        text: name
                        Repeater {
                            model: history
                            delegate: ThemedLabel {
                                text: "started: %1, duration: %2".arg(dateTime).arg(seconds)
                            }
                        }
                    }
                }
            }
        }
    }
}
