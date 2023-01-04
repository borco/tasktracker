import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import QtPlogAdapter

Window {
    id: root

    width: 640
    height: 480
    visible: true

    title: qsTr("Task Tracker")

    SplitView {
        anchors.fill: parent
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
            Layout.fillWidth: true
            initialItem: loginComponent
        }

        Pane {
            Layout.fillWidth: true
            Layout.fillHeight: true

            padding: 0

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                ToolBar {
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent
                        Label {
                            text: qsTr("Logs")
                            font.weight: 600
                        }

                        ToolSeparator {}

                        ToolButton {
                            text: qsTr("Clear")
                            onClicked: PlogMessageModel.clear()
                        }

                        Item { Layout.fillWidth: true }
                    }
                }

                PlogMessageView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
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

                Login {
                    Layout.fillWidth: true
                }

                Item { Layout.fillHeight: true }
            }
        }
    }

    Component.onCompleted: {
//        readCredentials()

//        console.debug("debug message")
//        console.info("info message")
//        console.warn("warn message")
//        console.error("error message")

//        console.debug("debug message")
//        console.info("info message")
//        console.warn("warn message")
//        console.error("error message")
    }
}
