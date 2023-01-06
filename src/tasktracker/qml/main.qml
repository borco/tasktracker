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
                visible: settingsPopup.logsVisible
                padding: 0

                LogsComponent {
                    anchors.fill: parent
                }
            }
        }
    }

    ToolButton {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 6
        icon.source: "../icons/settings.svg"
        flat: true
        onClicked: settingsPopup.open()
    }

    SettingsPopup {
        id: settingsPopup
        anchors.centerIn: Overlay.overlay
        width: Math.min(600, parent.width)
        height: Math.min(parent.height - 100, 600)
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
    }

    Component.onCompleted: {
        splitView.restoreState(settings.splitView)
//        settingsPopup.open()
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
