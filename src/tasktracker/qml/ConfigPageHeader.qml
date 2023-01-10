import QtQuick
import QtQuick.Controls

import "Theme.js" as Theme

Item {
    id: root

    property string title: ""

    property string leftButtonText: qsTr("Cancel")
    property bool leftButtonVisible: true

    property string rightButtonText: qsTr("Save")
    property bool rightButtonEnabled: true

    signal leftButtonClicked()
    signal rightButtonClicked()

    implicitHeight: Theme.PageHeaderHeight

    FlatButton {
        text: root.leftButtonText
        visible: root.leftButtonVisible
        normalColor: palette.text
        downColor: palette.text
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.ConfigLeftContentMargin - leftPadding
        onClicked: root.leftButtonClicked()
    }

    Label {
        text: root.title
        anchors.centerIn: parent
        font.bold: true
    }

    FlatButton {
        text: root.rightButtonText
        enabled: root.rightButtonEnabled
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: Theme.ConfigRightContentMargin - rightPadding
        onClicked: root.rightButtonClicked()
    }

    ConfigHorizontalSeparator {}
}
