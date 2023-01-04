import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
