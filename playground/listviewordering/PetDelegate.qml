import QtQuick

Rectangle {
    id: content

    required property string name
    required property string type
    required property string size
    required property int age

    width: view.width
    height: column.implicitHeight + 4

    border.width: 1
    border.color: "lightsteelblue"

    radius: 2

    Column {
        id: column
        anchors { fill: parent; margins: 2 }

        Text { text: 'Name: ' + name }
        Text { text: 'Type: ' + type }
        Text { text: 'Age: ' + age }
        Text { text: 'Size: ' + size }
    }
}
