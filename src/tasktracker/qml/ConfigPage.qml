import QtQuick
import QtQuick.Controls

import TaskTrackerLib

Page {
    id: root

    signal done()

    padding: 0

    contentItem: StackView {
        id: stackView
        initialItem: configMainPageComponent
    }

    Component {
        id: configMainPageComponent
        ConfigMainPage {
            onDone: root.done()
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
