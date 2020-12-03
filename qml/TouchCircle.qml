import QtQuick 2.13

import io.qt.examples.backend 1.0

Item {
    anchors.fill: parent

    BackEnd {
        id: backend
    }

    Rectangle {
        id: button

        property bool checked: false
        property point globalPos

        width: 120
        height: 120
        radius: 60
        color: button.checked ? "green" : "orange"
        anchors.centerIn: parent

        Text {
            anchors.centerIn: parent
            text: button.checked ? (Math.round(button.globalPos.x)) + "x" + (Math.round(button.globalPos.y))
                                  : "Click Button!"
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