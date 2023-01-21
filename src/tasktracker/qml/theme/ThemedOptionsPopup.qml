import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

ThemedPopup {
    id: root

    property ListModel options: ListModel {}

    property string title: ""

    signal clicked(value: var)

    modal: true

    parent: Overlay.overlay
    anchors.centerIn: parent

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    contentHeight: contentLayout.implicitHeight
    contentWidth: contentLayout.implicitWidth

    contentItem: ColumnLayout {
        id: contentLayout

        spacing: 0

        ConfigPageHeader {
            id: header
            title: root.title
            leftButton.onClicked: close()
            rightButton.visible: false
            Layout.fillWidth: true
        }

        Repeater {
            model: options

            delegate: ItemDelegate {
                Layout.fillWidth: true
                text: name
                onClicked: {
                    root.clicked(value)
                    close()
                }

                BottomSeparator {}
            }
        }

        Item {
            implicitHeight: 16
        }
    }
}
