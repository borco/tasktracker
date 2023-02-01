import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// MultiEffect docs: https://doc-snapshots.qt.io/qt6-dev/qml-qtquick-effects-multieffect.html

MouseArea {
    id: root

    property string name
    property string type
    property string size
    property int age

    property bool held: false
    property Item parentWhenHeld: undefined

    signal dropEntered(drag: var, dragArea: var)

    onPressed: held = true
    onReleased: held = false

    drag.target: held ? content : undefined
    drag.axis: Drag.YAxis

    implicitHeight: content.implicitHeight + content.anchors.topMargin + content.anchors.bottomMargin
    implicitWidth: content.implicitWidth + content.anchors.leftMargin + content.anchors.rightMargin

    Rectangle {
        anchors.fill: parent
        color: "#400000ff"
        radius: 16
    }

    RowLayout {
        id: content

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        width: root.width
        height: root.height

        Drag.active: root.held
        Drag.source: root
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2

        Button {
            id: dragButton
            icon.source: "../icons/task/drag.svg"
            icon.color: "red"
            background: null
            enabled: false
        }

        Pane {
            id: innerControl

            topInset: 0
            bottomInset: 0
            Layout.fillWidth: true

            background: Rectangle {
                color: root.palette.base
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

        states: [
            State {
                when: held

                ParentChange {
                    target: content
                    parent: parentWhenHeld
                }

                PropertyChanges {
                    dragButton.icon.color: "blue"
                }

                AnchorChanges {
                    target: content
                    anchors.horizontalCenter: undefined
                    anchors.verticalCenter: undefined
                }
            }
        ]
    }

    DropArea {
        anchors.fill: parent
        anchors.margins: 10

        onEntered: (drag) => dropEntered(drag, root)
    }
}
