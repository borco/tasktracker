import QtQuick
import QtQuick.Controls

Item {
    id: root

    DelegateModel {
        id: visualModel

        model: PetsModel {}

        delegate: PetDelegate {
            name: model.name
            type: model.type
            size: model.size
            age: model.age

            implicitHeight: model.height
            width: ListView.view.width
            parentWhenHeld: view

            onDropEntered: (drag, dragArea) => {
                               console.log("dropped")
                               visualModel.items.move(
                                   drag.source.DelegateModel.itemsIndex,
                                   dragArea.DelegateModel.itemsIndex)
                           }
        }
    }

    ListView {
        id: view

        anchors {
            fill: parent
            margins: 2
        }

        model: visualModel

        spacing: 4
        cacheBuffer: 50
    }
}
