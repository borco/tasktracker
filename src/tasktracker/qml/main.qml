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
        id: starPageComponent
        Page {
            BusyIndicator {
                anchors.centerIn: parent
                running: true
            }
        }
    }

    Component {
        id: configPageComponent
        ConfigPage {
            onDone: stackView.pop()
        }
    }

    Component {
        id: loginPageComponent
        LoginPage {
            isBusy: TogglProxy.loggedStatus === TogglProxy.LoggedUnknown
            onShowConfig: showConfigPage()
        }
    }

    Component {
        id: mainPageComponent
        MainPage {
            onShowConfig: showConfigPage()
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

    Connections {
        target: TogglProxy

        function onLoggedStatusChanged() {
            if (TogglProxy.loggedStatus === TogglProxy.LoggedIn) {
                stackView.replace(null, mainPageComponent, StackView.Immediate)
            } else if (TogglProxy.loggedStatus === TogglProxy.LoggedOut) {
                stackView.replace(null, loginPageComponent, StackView.Immediate)
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

        switch(TogglProxy.loggedStatus) {
        case TogglProxy.LoggedIn:
            stackView.replace(null, mainPageComponent, StackView.Immediate)
            break
        case TogglProxy.LoggedUnknown:
            stackView.replace(null, starPageComponent, StackView.Immediate)
            break
        default:
            stackView.replace(null, loginPageComponent, StackView.Immediate)
            break
        }

//        showConfigPage()
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
