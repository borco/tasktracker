import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    property bool isBusy: false

    signal showConfig()

    header: PageHeader {
        onShowConfig: root.showConfig()
    }

    ColumnLayout {
        anchors.fill: parent

        Item { Layout.fillHeight: true }

        LoginComponent {
            enabled: !root.isBusy
            Layout.fillWidth: true
        }

        Item { Layout.fillHeight: true }
    }

    BusyIndicator {
        anchors.centerIn: parent
        visible: root.isBusy
        running: visible
    }
}
