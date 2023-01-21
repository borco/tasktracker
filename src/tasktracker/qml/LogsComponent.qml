import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QtPlogAdapter

import "theme"

ColumnLayout {
    id: control

    anchors.fill: parent
    spacing: 0

    DockToolBar {
        title: qsTr("Logs")

        Layout.fillWidth: true

        innerContentItem: RowLayout {
            anchors.fill: parent

            ThemedToolButton {
                icon.source: "../icons/clear.svg"
                onClicked: PlogMessageModel.clear()
            }

            ThemedToolButton {
                id: wrapTextToolButton
                icon.source: "../icons/wrap_text.svg"
                checkable: true
            }
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
