import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    signal showSettings()

    header: PageHeader {
        onShowSettings: root.showSettings()
    }

    ColumnLayout {
        anchors.fill: parent

        Item { Layout.fillHeight: true }

        LoginComponent {
            Layout.fillWidth: true
        }

        Item { Layout.fillHeight: true }
    }
}
