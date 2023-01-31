import QtQuick

import "../theme"
import "../theme/Theme.js" as Theme

import TaskTrackerLib

ThemedMessageBox {
    id: root

    property Task task: null

    signal deletionAccepted()

    leftButton.text: qsTr("No")
    rightButton.text: qsTr("Delete")
    rightButton.color: Theme.DangerColor

    function deleteTask(task) {
        if (!task) {
            console.error("No task provided for deletion")
            return
        }

        title = qsTr("Delete task?")
        text = qsTr("This will completely delete task:<br><b>%1</b>").arg(task.name)
        this.task = task

        open()
    }

    onAccepted: root.deletionAccepted()
}
