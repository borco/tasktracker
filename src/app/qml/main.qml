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

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        GroupBox {
            title: qsTr("Config")
            Layout.fillWidth: true

            Login {}
        }

        RowLayout {
            Button {
                text: "Debug"
                onClicked: console.debug("xxx")
            }

            Button {
                text: "Info"
                onClicked: console.info("xxx")
            }

            Button {
                text: "Warn"
                onClicked: console.warn("xxx")
            }

            Button {
                text: "Error"
                onClicked: console.error("xxx")
            }
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
                            font.weight: 400
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

    Component.onCompleted: {
        //        readCredentials()
        console.debug("debug message")
        console.info("info message")
        console.warn("warn message")
        console.error("error message")

        console.debug("debug message")
        console.info("info message")
        console.warn("warn message")
        console.error("error message")
    }
}
