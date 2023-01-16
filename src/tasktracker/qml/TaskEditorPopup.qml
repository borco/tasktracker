import QtQuick
import QtQuick.Controls

import TaskTrackerLib

import "Theme.js" as Theme

ThemedPopup {
    id: root

    property var model

    parent: Overlay.overlay

    x: Theme.PopupX
    y: Theme.PopupTop
    width: parent.width - 2 * x
    height: parent.height - Theme.PopupTop - Theme.PopupBottom

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    modal: true

    contentHeight: stackView.implicitHeight
    contentWidth: stackView.implicitWidth

    onOpened: model.isEdited = true
    onClosed: {
        model.isEdited = false
        model = null
    }

    contentItem: StackView {
        id: stackView
        clip: true
        initialItem: taskEditorMainPageComponent
    }

    Component {
        id: taskEditorMainPageComponent
        TaskEditorMainPage {
            model: root.model
            onDone: root.close()
        }
    }
}
