import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Item {
    id: root

    property alias settingsButtonVisible: settingsButton.visible
    property alias rightLayout: rightLayout

    signal showSettings()

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
            id: settingsButton
            icon.source: "../icons/settings.svg"
            flat: true
            onClicked: root.showSettings()
        }
    }
}
