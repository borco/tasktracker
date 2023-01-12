import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

Page {
    id: root

    signal showConfig()

    background: null

    header: PageHeader {
        onShowConfig: root.showConfig()

        RowLayout {
            anchors.left: parent.left
            height: parent.height

            MaskedImage {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height
                Layout.leftMargin: Theme.PageHeaderLeftMargin
                borderSize: 2
                source: TogglProxy.imageUrl
                maskSource: "../icons/avatar_mask.svg"
            }

            ThemedLabel { text: TogglProxy.fullname }
        }

        BottomSeparator {}
    }
}
