import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "theme"
import "theme/Theme.js" as Theme
import "toggl"

Rectangle {
    id: root

    property alias title: title.text
    property alias isDoneVisible: isDoneToggle.checked
    property alias isArchivedVisible: isArchivedToggle.checked

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
            id: isArchivedToggle
            icon.source: "../icons/archived.svg"
            checkable: true
        }

        ThemedToolButton {
            id: isDoneToggle
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
