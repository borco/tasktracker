import QtQuick
import QtQuick.Controls

import TaskTrackerLib

ThemedPopup {
    id: root

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    modal: true

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
