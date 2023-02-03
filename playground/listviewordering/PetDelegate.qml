import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// MultiEffect docs: https://doc-snapshots.qt.io/qt6-dev/qml-qtquick-effects-multieffect.html

Control {
    id: root

    property string name
    property string type
    property string size
    property int age
    property int extraPadding

    property bool held: false
    property Item parentWhenHeld: undefined

    signal dropEntered(drag: var, dragArea: var)

    topPadding: 8
    bottomPadding: 8

    implicitHeight: content.implicitHeight + bottomPadding + topPadding
    implicitWidth: content.implicitWidth + leftPadding + rightPadding

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onPressed: held = true
        onReleased: held = false

        drag.axis: Drag.YAxis
    }

    Rectangle {
        anchors.fill: parent
        anchors.leftMargin: root.leftInset
        anchors.rightMargin: root.rightInset
        anchors.topMargin: root.topInset
        anchors.bottomMargin: root.bottomInset
        color: root.palette.mid
    }

    Rectangle {
        id: content

        color: palette.base
        border.width: 0
        border.color: root.palette.highlight

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: root.leftPadding
        anchors.rightMargin: root.rightPadding
        anchors.topMargin: root.topPadding
        anchors.bottomMargin: root.bottomPadding

        width: root.width
        height: root.height

        implicitWidth: contentLayout.implicitWidth
        implicitHeight: contentLayout.implicitHeight

        Drag.active: root.held
        Drag.source: root
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2

        RowLayout {
            id: contentLayout

            anchors.fill: parent

            Button {
                icon.source: "../icons/task/drag.svg"
                icon.color: root.palette.button
                background: null
                enabled: false
            }

            Item {
                id: innerControl

                Layout.fillWidth: true

                implicitHeight: innerLayout.implicitHeight

                ColumnLayout {
                    id: innerLayout
                    anchors.fill: parent
                    Text { text: 'Name: ' + name }
                    Text { text: 'Type: ' + type }
                    Text { text: 'Age: ' + age }
                    Text { text: 'Size: ' + size }
                    Text {
                        text: "..."
                        Layout.fillWidth: true
                        Layout.minimumHeight: root.extraPadding
                        verticalAlignment: Text.AlignBottom
                    }
                }
            }
        }
    }

    DropArea {
        anchors.fill: parent
        anchors.margins: 10

        onEntered: (drag) => dropEntered(drag, root)
    }

    states: [
        State {
            when: held

            ParentChange {
                target: content
                parent: parentWhenHeld
            }

            AnchorChanges {
                target: content
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }

            PropertyChanges {
                target: content
                border.width: 1
                x: 8
            }


            PropertyChanges {
                target: mouseArea
                drag.target: content
            }
        }
    ]
}
