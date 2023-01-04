import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    width: 640
    height: 480
    visible: true

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        GroupBox {
            title: qsTr("Config")
            Layout.fillWidth: true

            Login {}
        }

        Item { Layout.fillHeight: true }
    }

    Component.onCompleted: {
        //        readCredentials()
    }
}
