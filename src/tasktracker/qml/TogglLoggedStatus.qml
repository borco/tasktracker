import QtQuick
import QtQuick.Layouts

import TaskTrackerLib

ThemedToolButton {
    id: root
    icon.source: "../icons/toggl.svg"
    icon.color: TogglProxy.loggedStatus === TogglProxy.LoggedIn ? "#E57CD8" : palette.dark
    icon.width: parent.height - 2 * padding
    icon.height: parent.height - 2 * padding
    padding: 1
}
