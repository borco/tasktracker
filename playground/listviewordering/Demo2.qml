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
        delegate: PetDelegate {}

        spacing: 4
        cacheBuffer: 50
    }
}
