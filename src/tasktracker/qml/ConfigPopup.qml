import QtQuick
import QtQuick.Controls

import TaskTrackerLib

import "Theme.js" as Theme

ThemedPopup {
    id: root

    modal: true

    parent: Overlay.overlay

    x: Theme.PopupX
    y: Theme.PopupTop
    width: parent.width - 2 * x
    height: parent.height - Theme.PopupTop - Theme.PopupBottom

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    contentHeight: stackView.implicitHeight
    contentWidth: stackView.implicitWidth

    onClosed: {
        stackView.replace(null, configMainPageComponent, StackView.Immediate)
    }

    contentItem: StackView {
        id: stackView
        clip: true
        initialItem: configMainPageComponent
    }

    Component {
        id: configMainPageComponent
        ConfigMainPage {
            onDone: root.close()
            onSelectDataFolderLocation: stackView.push(configDataFolderLocationSelectionPageComponent)
        }
    }

    Component {
        id: configDataFolderLocationSelectionPageComponent
        ConfigDataFolderLocationSelectionPage {
            originalDataFolderLocation: Config.dataFolderLocation
            onRejected: stackView.pop()
            onAccepted: {
                Config.dataFolderLocation = dataFolderLocation
                stackView.pop()
            }
        }
    }
}
