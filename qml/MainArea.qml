import QtQuick 2.13

import io.qt.examples.backend 1.0

Rectangle {
    id: mainArea

    property string device

    anchors.fill: parent
    color: "#2B2B2B"

    Backend {
        id: backend
    }

    Rectangle {
        id: monitorInfo

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 40
        anchors.topMargin: 40
        width: 500
        height: 50
        radius: 12
        color: "#F26C4F"

        Text {
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 18
            text: mainArea.device
        }
    }

    Rectangle {
        id: button

        property bool checked: false
        property point globalPos

        width: 200
        height: 200
        radius: 100
        color: button.checked ? "#82CA9C" : "#F26C4F"
        anchors.centerIn: parent

        Text {
            anchors.centerIn: parent
            font.pixelSize: 18
            text: button.checked ? (Math.round(button.globalPos.x)) + "x" + (Math.round(button.globalPos.y))
                                  : "Push the Button!"
        }

        MouseArea {
            id: mouseArea

            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            onClicked: {
                button.globalPos = mapToGlobal(mouseArea.x + mouseArea.width/2, mouseArea.y + mouseArea.height/2)
                button.checked = button.checked === false ? true : false
                backend.buttonClicked(button.globalPos)
            }
        }
    }
}