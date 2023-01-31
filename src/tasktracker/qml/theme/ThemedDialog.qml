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
    }

    padding: Theme.DialogPadding

    header: null

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

            ThemedButton {
                id: leftButton
                Layout.fillHeight: true
                Layout.preferredWidth: buttonsRowLayout.width / 2 - 1
            }

            Rectangle {
                color: palette.dark
                Layout.fillHeight: true
                width: 1
            }

            ThemedButton {
                id: rightButton
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
