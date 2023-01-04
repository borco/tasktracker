import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings

Window {
    id: root

    width: 640
    height: 480
    visible: true

    title: qsTr("Task Tracker")

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        MainToolBar {
            id: mainToolBar
            Layout.fillWidth: true
        }

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
                visible: mainToolBar.logs.checked
                padding: 0

                LogsComponent {
                    anchors.fill: parent
                }
            }
        }

    }

    Component {
        id: loginComponent

        Pane {
            ColumnLayout {
                anchors.fill: parent

                Item { Layout.fillHeight: true }

                LoginComponent {
                    Layout.fillWidth: true
                }

                Item { Layout.fillHeight: true }
            }
        }
    }

    Settings {
        id: settings
        category: "Main"
        property var splitView
        property alias logsVisible: mainToolBar.logsVisible
    }

    Component.onCompleted: {
        splitView.restoreState(settings.splitView)
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
