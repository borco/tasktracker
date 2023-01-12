import QtQuick
import QtQuick.Controls

import "Theme.js" as Theme

Popup {
    id: root

    Overlay.modal: Rectangle {
        color: Theme.colorWithAlpha(palette.text, 0.5)
    }
}
