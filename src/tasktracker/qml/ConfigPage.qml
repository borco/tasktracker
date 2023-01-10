import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "Theme.js" as Theme

import TaskTrackerLib

Page {
    id: root

    signal done()

    title: qsTr("Settings")
    padding: 0

    header: Item {
        implicitHeight: Theme.PageHeaderHeight

        Label {
            text: root.title
            anchors.centerIn: parent
            font.bold: true
        }

        FlatButton {
            text: qsTr("Done")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: Theme.ConfigRightContentMargin
            onClicked: root.done()
        }

        ConfigHorizontalSeparator {}
    }

    contentItem: StackView {
        initialItem: configMainPageComponent
    }

    Component {
        id: configMainPageComponent
        ConfigMainPage {}
    }
}
