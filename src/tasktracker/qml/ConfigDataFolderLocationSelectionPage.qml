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
        leftPadding: Theme.ContentLeftMargin

        onClicked: folderListModel.cd(text)

        ConfigHorizontalSeparator {}
    }

    title: qsTr("Data Folder Location")

    header: ConfigPageHeader {
        title: root.title
        leftButton.onClicked: root.rejected()
        rightButton.enabled: root.isModified
        rightButton.highlighted: true
        rightButton.onClicked: root.accepted()
    }

    FolderCreator {
        id: folderCreator
        path: folderListModel.folder
    }

    InputDialog {
        id: newFolderNameDialog

        modal: true
        width: Math.min(300, root.width - 100)
        anchors.centerIn: Overlay.overlay

        title: qsTr("New folder")

        errorLabel.text: folderCreator.error

        leftButton.text: qsTr("Cancel")
        leftButton.highlighted: true
        leftButton.onClicked: {
            reject()
            textField.text = ""
        }

        rightButton.text: qsTr("Ok")
        rightButton.enabled: folderCreator.isValidDir(textField.text)
        rightButton.onClicked: {
            let path = textField.text
            if (folderCreator.makeDir(path)) {
                accept()
                textField.text = ""
                folderListModel.cd(path)
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.preferredHeight: Theme.ConfigGroupTitleHeight
            Layout.fillWidth: true

            RowLayout {
                anchors.verticalCenter: parent.verticalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.ConfigGroupTitleBottomMargin
                anchors.left: parent.left
                anchors.leftMargin: Theme.ContentLeftMargin
                anchors.right: parent.right
                anchors.rightMargin: Theme.ContentRightMargin

                Label {
                    text: root.dataFolderLocation
                    font.weight: Theme.ConfigGroupTitleFontWeight
                    Layout.fillWidth: true
                }

                ThemedToolButton {
                    icon.source: "../icons/create_new_folder.svg"
                    onClicked: newFolderNameDialog.open()
                }

                ThemedToolButton {
                    icon.source: "../icons/refresh.svg"
                    onClicked: folderListModel.refresh()
                }
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

    Component.onCompleted: {
        newFolderNameDialog.open()
    }
}
