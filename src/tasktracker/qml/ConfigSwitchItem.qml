import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Item {
    id: root

    property string text: ""
    property alias checked: switchControl.checked

    implicitHeight: Theme.ConfigItemHeight
    Layout.fillWidth: true

    ConfigItemBackground {}

    RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.ConfigLeftContentMargin
        anchors.right: parent.right
        anchors.rightMargin: Theme.ConfigRightContentMargin

        Label {
            text: root.text
            Layout.fillWidth: true
            elide: Text.ElideRight
        }

        Switch {
            id: switchControl
            rightPadding: 0
        }
    }
}
