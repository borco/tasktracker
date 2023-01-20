import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Theme

Rectangle {
    id: root

    property alias title: title.text
    property alias doneVisible: doneToggle.checked
    property alias archivedVisible: archivedToggle.checked

    signal configClicked()

    color: palette.base

    implicitHeight: Theme.pageHeaderHeight

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.pageHeaderLeftMargin
        anchors.rightMargin: Theme.pageHeaderRightMargin

        spacing: Theme.pageHeaderSpacing

        ThemedLabel {
            id: title
            Layout.alignment: Qt.AlignVCenter
            font.pointSize: Theme.pageHeaderTitleSize
            font.weight: Theme.pageHeaderTitleWeight
        }

        TogglLoggedStatus {}

        Item { Layout.fillWidth: true }

        ThemedToolButton {
            id: archivedToggle
            icon.source: "../icons/archived.svg"
            checkable: true
        }

        ThemedToolButton {
            id: doneToggle
            icon.source: "../icons/task/done.svg"
            checkable: true
        }

        ThemedToolButton {
            id: configButton
            icon.source: "../icons/settings.svg"
            onClicked: root.configClicked()
        }
    }

    BottomSeparator {}
}
