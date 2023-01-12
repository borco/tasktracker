import QtQuick

Rectangle {
    property bool inDarkMode: palette.text > palette.base

    color: inDarkMode ? palette.light : palette.dark
    height: 1
    width: parent.width
    anchors.bottom: parent.bottom
}
