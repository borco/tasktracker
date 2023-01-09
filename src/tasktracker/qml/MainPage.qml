import QtQuick
import QtQuick.Controls

Page {
    id: root

    signal showConfig()

    header: PageHeader {
        onShowConfig: root.showConfig()
    }
}
