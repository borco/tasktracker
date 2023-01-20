import QtQuick
import QtQuick.Controls

import Theme

Item {
    id: root

    property string title: ""

    property alias leftButton: leftButton
    property alias rightButton: rightButton

    implicitHeight: Theme.pageHeaderHeight

    ThemedButton {
        id: leftButton

        text: qsTr("Cancel")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.contentLeftMargin - leftPadding
    }

    ThemedLabel {
        text: root.title
        anchors.centerIn: parent
        font.bold: true
    }

    ThemedButton {
        id: rightButton
        text: qsTr("Save")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: Theme.contentRightMargin - rightPadding
    }

    BottomSeparator {}
}
