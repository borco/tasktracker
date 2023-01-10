import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Dialog {
    id: root

    property alias leftButton: leftButton
    property alias rightButton: rightButton

    background: Rectangle {
        radius: Theme.DialogRadius
        color: palette.window
        border.width: 1
        border.color: palette.dark
    }

    padding: Theme.DialogPadding

    Overlay.modal: Rectangle {
        color: Theme.colorWithAlpha(palette.text, 0.5)
    }

    header: Item {}

    footer: Item {
        implicitHeight: Theme.DialogButtonsHeight

        Rectangle {
            color: palette.dark
            width: parent.width
            height: 1
        }

        RowLayout {
            id: buttonsRowLayout

            anchors.fill: parent
            spacing: 0

            FlatButton {
                id: leftButton
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumWidth: buttonsRowLayout.width / 2 - 1
            }

            Rectangle {
                color: palette.dark
                Layout.fillHeight: true
                width: 1
            }

            FlatButton {
                id: rightButton
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
