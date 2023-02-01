import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 640
    height: 800
    visible: true

    ColumnLayout {
        anchors.fill: parent
        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex
            Demo1 {}
            Demo2 {}
        }

        TabBar {
            id: tabBar

            Layout.fillWidth: true

            TabButton {
                text: qsTr("Demo1")
            }

            TabButton {
                text: qsTr("Demo2")
            }
        }
    }

    Settings {
        property alias tabBarCurrentIndex: tabBar.currentIndex
    }
}
