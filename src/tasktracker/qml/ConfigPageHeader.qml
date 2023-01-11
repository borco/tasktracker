import QtQuick
import QtQuick.Controls

import "Theme.js" as Theme

Item {
    id: root

    property string title: ""

    property alias leftButton: leftButton
    property alias rightButton: rightButton

    implicitHeight: Theme.PageHeaderHeight

    ThemedButton {
        id: leftButton

        text: qsTr("Cancel")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.ContentLeftMargin - leftPadding
    }

    Label {
        text: root.title
        anchors.centerIn: parent
        font.bold: true
    }

    ThemedButton {
        id: rightButton
        text: qsTr("Save")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: Theme.ContentRightMargin - rightPadding
    }

    ConfigHorizontalSeparator {}
}
