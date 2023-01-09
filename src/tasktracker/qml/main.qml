import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings

Window {
    id: root

    function showSettingsPage() {
        settingsPage.visible = true
        stackView.push(settingsPage)
    }

    width: 640
    height: 480
    visible: true

    title: qsTr("Task Tracker")

    SettingsPage {
        id: settingsPage
        onDone: stackView.pop()
    }

    Component {
        id: loginComponent
        LoginPage {
            onShowSettings: showSettingsPage()
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
                visible: settingsPage.logsVisible
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
//        showSettingsPage()
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
