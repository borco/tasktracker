import QtQuick
import QtQuick.Controls

Item {
    ListView {
        id: view

        anchors {
            fill: parent
            margins: 2
        }

        model: PetsModel {}
        delegate: PetDelegate {
            name: model.name
            type: model.type
            size: model.size
            age: model.age

            implicitHeight: model.height + topPadding + bottomPadding
            width: ListView.view.width
        }

        spacing: 4
        cacheBuffer: 50
    }
}
