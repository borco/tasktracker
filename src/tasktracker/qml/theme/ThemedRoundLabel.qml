import QtQuick
import QtQuick.Layouts

import "Theme.js" as Theme

Item {
    id: root

    property alias text: label.text

    property color checkedColor: palette.highlight
    property bool checked: false

    property bool borderVisible: true
    property color borderColor: palette.highlight
    property int borderWidth: Theme.RoundLabelBorderWidth

    property int diameter: Theme.RoundLabelDiameter

    implicitWidth: rectagle.implicitWidth
    implicitHeight: rectagle.implicitHeight

    Rectangle {
        id: rectagle

        anchors.centerIn: parent

        implicitWidth: diameter
        implicitHeight: diameter

        color: checked ? checkedColor : "transparent"
        border.color: borderColor
        border.width: borderVisible ? borderWidth : 0
        radius: diameter / 2
    }

    ThemedLabel {
        id: label
        anchors.centerIn: parent
        font.pointSize: Theme.SmallLabelSize
        font.bold: checked
    }
}
