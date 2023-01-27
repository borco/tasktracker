import QtQuick
import QtQuick.Controls

Button {
    id: root

    background: null

    contentItem: ThemedRoundLabel {
        text: root.text
        borderVisible: true
        borderColor: checkedColor
        checked: root.checked
    }
}
