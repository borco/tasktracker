import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Button {
    id: root

    property string value: ""

    implicitHeight: Theme.ConfigItemHeight
    Layout.fillWidth: true
    leftPadding: 0
    rightPadding: 0

    background: ConfigItemBackground {}

    contentItem: Item {
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

            Label {
                text: root.value + " ❯"
            }
        }
    }
}
