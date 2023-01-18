import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "Theme.js" as Theme

Page {
    id: root

    signal showConfig()

    background: null

    header: PageHeader {
        onShowConfig: root.showConfig()

        PageHeader.Layout {
            PageHeader.Title { text: root.title }
        }

        BottomSeparator {}
    }
}
