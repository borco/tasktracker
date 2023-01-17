import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import TaskTrackerLib

import "Theme.js" as Theme

ApplicationWindow {
    id: root

    function showConfigPage() {
        configPopup.open()
    }

    width: 640
    height: 480
    visible: true

    title: qsTr("Task Tracker")

    background: Rectangle {
        color: palette.window
    }

    ConfigPopup {
        id: configPopup
    }

    Item {
        visible: false

        BusyIndicator {
            anchors.centerIn: parent
            running: true
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ThemedSplitView {
            id: splitView

            Layout.fillHeight: true
            Layout.fillWidth: true

            orientation: Qt.Vertical

            MainPage {
                SplitView.minimumHeight: 200
                onShowConfig: showConfigPage()
            }

            Pane {
                visible: Config.logsVisible
                padding: 0

                LogsComponent {
                    anchors.fill: parent
                }
            }
        }
    }

    Settings {
        id: settings
        category: "Main"
        property var splitView
    }

    Component.onCompleted: {
        splitView.restoreState(settings.splitView)
        showConfigPage()
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
