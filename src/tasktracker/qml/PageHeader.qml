import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Item {
    id: root

    property alias rightLayout: rightLayout

    signal showConfig()

    implicitHeight: Theme.PageHeaderHeight

    RowLayout {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 6

        spacing: rightLayout.spacing

        RowLayout {
            id: rightLayout
        }

        ToolButton {
            id: configButton
            icon.source: "../icons/settings.svg"
            flat: true
            onClicked: root.showConfig()
        }
    }
}
