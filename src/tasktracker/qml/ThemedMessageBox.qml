import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Theme

ThemedDialog {
    id: root

    property string text: ""

    modal: true
    anchors.centerIn: Overlay.overlay
    bottomPadding: Theme.dialogPadding / 2

    leftButton.onClicked: reject()
    rightButton.onClicked: accept()

    contentItem: ColumnLayout {
        ThemedLabel {
            text: root.title
            font.bold: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            Layout.bottomMargin: root.padding / 2
        }

        ThemedLabel {
            text: root.text
            Layout.fillWidth: true
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
