import QtQuick

Item {
    id: root

    component DelegateItem: Item {
        id: delegateItem
        width: model.width
        height: model.height

        Rectangle {
            id: dragRect
            width: model.width
            height: model.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: model.color
            border.color: Qt.darker(color)
            property int dragItemIndex: index

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                drag.target: dragRect

                drag.onActiveChanged: {
                    if (mouseArea.drag.active) {
                        dragRect.dragItemIndex = index;
                    }
                }
            }

            states: [
                State {
                    when: dragRect.Drag.active
                    ParentChange {
                        target: dragRect
                        parent: listView
                    }

                    AnchorChanges {
                        target: dragRect
                        anchors.horizontalCenter: undefined
                        anchors.verticalCenter: undefined
                    }
                }
            ]

            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: dragRect.width / 2
            Drag.hotSpot.y: dragRect.height / 2
        }

        DropArea {
            anchors.fill: parent
            onEntered: {
                console.log("dragged", drag.source.dragItemIndex);
                console.log("moved", dragRect.dragItemIndex);
                listModel.move(drag.source.dragItemIndex, listView.dragItemIndex, 1)
            }
        }
    }

    ListModel {
                id: listModel
                ListElement {
                    width: 50
                    height: 50
                    color: 'red'
                }
                ListElement {
                    width: 100
                    height: 50
                    color: 'yellow'
                }
                ListElement {
                    width: 150
                    height: 50
                    color: 'green'
                }
                ListElement {
                    width: 100
                    height: 50
                    color: 'blue'
                }
                ListElement {
                    width: 50
                    height: 50
                    color: 'black'
                }
                ListElement {
                    width: 200
                    height: 50
                    color: 'gray'
                }
            }

    ListView {
        id: listView
        anchors.fill: parent

        model: listModel

        delegate: DelegateItem {}

        addDisplaced: Transition {
            NumberAnimation {
                properties: "x, y"
                duration: 100
            }
        }

        moveDisplaced: Transition {
            NumberAnimation {
                properties: "x, y"
                duration: 100
            }
        }

        remove: Transition {
            NumberAnimation {
                properties: "x, y"
                duration: 100
            }

            NumberAnimation {
                properties: "opacity"
                duration: 100
            }
        }

        removeDisplaced: Transition {
            NumberAnimation {
                properties: "x, y"
                duration: 100
            }
        }

        displaced: Transition {
            NumberAnimation {
                properties: "x, y"
                duration: 100
            }
        }
    }
}
