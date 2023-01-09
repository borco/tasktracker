import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings

import TaskTrackerLib

Window {
    id: root

    function showConfigPage() {
        stackView.push(configPageComponent)
    }

    width: 640
    height: 480
    visible: true

    title: qsTr("Task Tracker")

    Component {
        id: configPageComponent
        ConfigPage {
            onDone: stackView.pop()
        }
    }

    Component {
        id: loginComponent
        LoginPage {
            onShowSettings: showConfigPage()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        SplitView {
            id: splitView

            Layout.fillHeight: true
            Layout.fillWidth: true

            orientation: Qt.Vertical

            handle: Rectangle {
                implicitWidth: 6
                implicitHeight: 6
                color: SplitHandle.pressed ? palette.dark
                                           : (SplitHandle.hovered
                                              ? palette.highlight
                                              : palette.window)
            }

            StackView {
                id: stackView

                SplitView.minimumHeight: 200
                initialItem: loginComponent
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
//        showConfigPage()
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
