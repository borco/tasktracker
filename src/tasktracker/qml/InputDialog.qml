import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

DialogWithButtons {
    id: root

    property alias textField: textField
    property alias errorLabel: errorLabel

    bottomPadding: Theme.DialogPadding / 2

    contentItem: ColumnLayout {
        Label {
            text: root.title
            font.bold: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            Layout.bottomMargin: root.padding / 2
        }

        Item {
            Layout.fillWidth: true
            implicitHeight: textField.implicitHeight

            TextField {
                id: textField
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Label {
            id: errorLabel
            font.pointSize: Theme.ErrorTextHeight
            color: Theme.ErrorTextColor
            Layout.fillWidth: true
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
}
