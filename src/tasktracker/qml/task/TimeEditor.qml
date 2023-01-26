import QtQuick
import QtQuick.Window
import QtQuick.Controls

Item {
    id: root

    property date date
    property date minimumDate
    property date editedDate: new Date()

    width: frame.implicitWidth + 10
    height: frame.implicitHeight + 10

    FontMetrics {
        id: fontMetrics
    }

    function updateEditedDate() {
        if (date) {
            let d = new Date(date.getTime())
            d.setHours(hoursTumbler.currentIndex, minutesTumbler.currentIndex, secondsTumbler.currentIndex)
            editedDate = d
        }
    }

    component TumblerDelegate: Label {
        text: modelData
        opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: fontMetrics.font.pixelSize * 1.25
    }

    Frame {
        id: frame
        padding: 0
        anchors.centerIn: parent

        background: null

        Row {
            id: row

            Tumbler {
                id: hoursTumbler

                model: 24
                wrap: false

                delegate: TumblerDelegate {
                    color: minimumDate && (minimumDate.getHours() > modelData) ? "red" : root.palette.text
                }

                onCurrentIndexChanged: updateEditedDate()
            }

            Tumbler {
                id: minutesTumbler

                model: 60
                wrap: false

                delegate: TumblerDelegate {
                    color: minimumDate
                           && ((minimumDate.getHours() === hoursTumbler.currentIndex && minimumDate.getMinutes() > modelData)
                               || (minimumDate.getHours() > hoursTumbler.currentIndex)) ? "red" : root.palette.text
                }

                onCurrentIndexChanged: updateEditedDate()
            }

            Tumbler {
                id: secondsTumbler

                model: 60
                wrap: false

                delegate: TumblerDelegate {
                    color: minimumDate
                           && ((minimumDate.getHours() === hoursTumbler.currentIndex
                                && minimumDate.getMinutes() === minutesTumbler.currentIndex
                                && minimumDate.getSeconds() > modelData)
                               || (minimumDate.getHours() === hoursTumbler.currentIndex
                                   && minimumDate.getHours() > hoursTumbler.currentIndex)
                               || (minimumDate.getHours() > hoursTumbler.currentIndex)) ? "red" : root.palette.text
                }

                onCurrentIndexChanged: updateEditedDate()
            }

        }
    }

    function setTumblers() {
        let hours = date.getHours()
        hoursTumbler.positionViewAtIndex(hours, Tumbler.Center)
        hoursTumbler.currentIndex = hours

        let minutes = date.getMinutes()
        minutesTumbler.positionViewAtIndex(minutes, Tumbler.Center)
        minutesTumbler.currentIndex = minutes

        let seconds = date.getSeconds()
        secondsTumbler.positionViewAtIndex(seconds, Tumbler.Center)
        secondsTumbler.currentIndex = seconds
    }

    onDateChanged: setTumblers()
    onVisibleChanged: {
        if (visible) setTumblers()
    }
}
