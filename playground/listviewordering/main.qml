import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 640
    height: 800
    visible: true

    DelegateModel {
        id: visualModel

        model: PetsModel {}

        delegate: PetDelegate {
            name: model.name
            type: model.type
            size: model.size
            age: model.age
            extraPadding: model.height

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

        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        model: visualModel

        cacheBuffer: 50
    }
}
