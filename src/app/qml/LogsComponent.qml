import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qt.labs.settings

import QtPlogAdapter

ColumnLayout {
    id: control

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
                icon.source: "../icons/clear.svg"
                onClicked: PlogMessageModel.clear()
            }

            ToolButton {
                id: wrapTextToolButton
                icon.source: "../icons/wrap_text.svg"
                checkable: true
            }

            Item { Layout.fillWidth: true }
        }
    }

    PlogMessageView {
        wrapMessages: wrapTextToolButton.checked
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    Settings {
        id: settings
        category: "Logs"
        property alias wrapMessages: wrapTextToolButton.checked
    }
}
