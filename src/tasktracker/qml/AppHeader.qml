import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

Rectangle {
    id: root

    property alias title: title.text
    property alias isDoneVisible: doneToggle.checked
    property alias isArchivedVisible: archivedToggle.checked

    signal configClicked()

    color: palette.base

    implicitHeight: Theme.PageHeaderHeight

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.PageHeaderLeftMargin
        anchors.rightMargin: Theme.PageHeaderRightMargin

        spacing: Theme.PageHeaderSpacing

        ThemedLabel {
            id: title
            Layout.alignment: Qt.AlignVCenter
            font.pointSize: Theme.PageHeaderTitleSize
            font.weight: Theme.PageHeaderTitleWeight
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
