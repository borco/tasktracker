import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Control {
    id: root

    property string name
    property string type
    property string size
    property int age

    implicitHeight: layout.implicitHeight + topPadding + bottomPadding
    implicitWidth: layout.implicitWidth + leftPadding + rightPadding

    rightPadding: 10

    background: Rectangle {
        color: "#400000ff"
        radius: 16
    }

    RowLayout {
        id: layout

        anchors.fill: parent
        anchors.topMargin: topPadding
        anchors.bottomMargin: bottomPadding
        anchors.leftMargin: leftPadding
        anchors.rightMargin: rightPadding

        Image {
            source: "../icons/task/drag.svg"
        }

        Pane {
            id: innerControl

            topInset: 0
            bottomInset: 0
            Layout.fillWidth: true

            background: Rectangle {
                color: "#40ff0000"
                radius: 16
            }

            ColumnLayout {
                anchors.fill: parent
                Text { text: 'Name: ' + name }
                Text { text: 'Type: ' + type }
                Text { text: 'Age: ' + age }
                Text { text: 'Size: ' + size }
                Text { text: 'Height:' + root.height }
            }
        }
    }
}
