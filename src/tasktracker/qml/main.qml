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
        color: palette.base
    }

    ConfigPopup {
        id: configPopup

        x: Theme.PopupX
        y: Theme.PopupTop
        width: root.width - 2 * x
        height: root.height - Theme.PopupTop - Theme.PopupBottom
    }

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

        ThemedSplitView {
            id: splitView

            Layout.fillHeight: true
            Layout.fillWidth: true

            orientation: Qt.Vertical

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
//                showConfigPage()
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
    }

    Component.onDestruction: {
        settings.splitView = splitView.saveState()
    }
}
