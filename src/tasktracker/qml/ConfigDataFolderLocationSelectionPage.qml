import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

import TaskTrackerLib

Page {
    id: root

    property string originalDataFolderLocation: ""
    property string dataFolderLocation: originalDataFolderLocation
    property bool isModified: dataFolderLocation !== originalDataFolderLocation

    signal rejected()
    signal accepted()

    component FolderItemComponent: ItemDelegate {
        width: ListView.view.width
        implicitHeight: Theme.ConfigItemHeight
        leftPadding: Theme.ConfigLeftContentMargin

        onClicked: folderListModel.cd(text)

        ConfigHorizontalSeparator {}
    }

    title: qsTr("Data Folder Location")

    header: ConfigPageHeader {
        title: root.title
        rightButtonEnabled: root.isModified
        onLeftButtonClicked: root.rejected()
        onRightButtonClicked: root.accepted()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.preferredHeight: Theme.ConfigGroupTitleHeight
            Layout.fillWidth: true

            Label {
                text: root.dataFolderLocation
                font.weight: Theme.ConfigGroupTitleFontWeight
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.ConfigGroupTitleBottomMargin
                anchors.left: parent.left
                anchors.leftMargin: Theme.ConfigLeftContentMargin
            }

            ConfigHorizontalSeparator {}
        }

        ListView {
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: folderListModel

            header: FolderItemComponent {
                text: ".."
            }

            delegate: FolderItemComponent {
                text: fileName
            }
        }
    }

    FolderListModel {
        id: folderListModel
        folder: root.dataFolderLocation
        onFolderChanged: root.dataFolderLocation = folder
    }
}
