import QtQuick
import QtQuick.Controls

import "Theme.js" as Theme

Item {
    id: root

    property string title: ""

    property alias leftButton: leftButton
    property alias rightButton: rightButton

    implicitHeight: Theme.PageHeaderHeight

    FlatButton {
        id: leftButton

        text: qsTr("Cancel")
        normalColor: palette.text
        downColor: palette.text
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.ConfigLeftContentMargin - leftPadding
    }

    Label {
        text: root.title
        anchors.centerIn: parent
        font.bold: true
    }

    FlatButton {
        id: rightButton
        text: qsTr("Save")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: Theme.ConfigRightContentMargin - rightPadding
    }

    ConfigHorizontalSeparator {}
}
