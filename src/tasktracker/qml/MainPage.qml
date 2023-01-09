import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

Page {
    id: root

    signal showConfig()

    header: PageHeader {
        onShowConfig: root.showConfig()

        Rectangle {
            height: 1
            color: palette.dark
            width: parent.width
            anchors.bottom: parent.bottom
        }

        RowLayout {
            anchors.left: parent.left
            height: parent.height

            Item {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height

                RoundedImage {
                    anchors.fill: parent
                    anchors.margins: 4
                    borderSize: 1
                    source: TogglProxy.imageUrl
                }
            }

            Label { text: TogglProxy.fullname }
        }
    }
}
