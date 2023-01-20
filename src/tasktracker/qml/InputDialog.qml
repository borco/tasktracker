import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Theme

ThemedDialog {
    id: root

    property alias textField: textField
    property alias errorLabel: errorLabel

    bottomPadding: Theme.dialogPadding / 2

    contentItem: ColumnLayout {
        ThemedLabel {
            text: root.title
            font.bold: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            Layout.bottomMargin: root.padding / 2
        }

        WrappedTextField {
            id: textField
            Layout.fillWidth: true
        }

        ThemedSmallLabel {
            id: errorLabel
            color: Theme.errorColor
            Layout.fillWidth: true
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
}
