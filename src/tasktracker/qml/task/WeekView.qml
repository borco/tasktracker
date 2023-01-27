import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import TaskTrackerLib

import "../theme"
import "../theme/Theme.js" as Theme

Control {
    id: root

    property date today: new Date()
    property alias date: weekModel.date

    property int daysSpacing: 10
    property real dayWidth: Math.max(Theme.RoundLabelDiameter, (width - 6 * daysSpacing - leftPadding - rightPadding) / 7)

    signal todayClicked()

    function isToday(date) {
        return date.getDate() === today.getDate()
                && date.getMonth() === today.getMonth()
                && date.getYear() === today.getYear()
    }

    implicitHeight: rootLayout.implicitHeight + topPadding + bottomPadding
    implicitWidth: rootLayout.implicitWidth + leftPadding + rightPadding

    leftPadding: Theme.ContentLeftMargin
    rightPadding: Theme.ContentRightMargin

    background: Rectangle {
        color: palette.base
    }

    WeekModel {
        id: weekModel
        weekStart: Config.weekStart
        date: today
    }

    ColumnLayout {
        id: rootLayout

        anchors.fill: parent
        anchors.topMargin: topPadding
        anchors.leftMargin: leftPadding
        anchors.rightMargin: rightPadding
        anchors.bottomMargin: bottomPadding

        RowLayout {
            ThemedLabel {
                text: weekModel.date.toLocaleString(Qt.locale(), qsTr("dddd, MMM d, yyyy"))
                font.pointSize: Theme.SmallLabelSize
                font.bold: true
                Layout.fillWidth: true
            }

            ThemedButton {
                text: qsTr("Today")
                highlighted: false
                onClicked: todayClicked()
            }
        }

        RowLayout {
            id: daysLayout

            spacing: root.daysSpacing

            Layout.fillWidth: true

            Repeater {
                id: repeater

                model: weekModel

                delegate: Item {
                    implicitWidth: root.dayWidth
                    implicitHeight: delegateLayout.implicitHeight

                    ColumnLayout {
                        id: delegateLayout

                        width: parent.width

                        ThemedLabel {
                            text: name
                            Layout.fillWidth: true
                            font.weight: Theme.XSmallLabelWeight
                            font.pointSize: Theme.XSmallLabelSize
                            elide: Text.ElideRight
                            horizontalAlignment: Text.AlignHCenter
                        }

                        ThemedRoundLabel {
                            text: date.getDate()
                            checked: isSelectedDate
                            borderVisible: isToday(date)
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }
            }
        }
    }
}
