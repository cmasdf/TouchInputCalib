import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13

import io.qt.examples.backend 1.0

QtObject {
    id: root

    property var backend: BackEnd {
        id: backend
    }

    property var window1: Window {
        id: "applicationWindow1"

        visible: true
        width: 1920
        height: 1080
        x: 0
        y: 0

        visibility: ApplicationWindow.Windowed

        objectName: "applicationWindow1"

        Item {
            id: leftScreen

            anchors.fill: parent

            Rectangle {
                id: button1

                property bool checked: false
                property point globalPos

                width: 120
                height: 120
                radius: 40
                color: button1.checked ? "green" : "orange"
                anchors.centerIn: parent

                Text {
                    anchors.centerIn: parent
                    text: button1.checked ? (Math.round(button1.globalPos.x)) + "x" + (Math.round(button1.globalPos.y))
                                          : "Click Button!"
                }

                MouseArea {
                    id: mouseArea1

                    width: parent.width
                    height: parent.height
                    anchors.centerIn: parent
                    onClicked: {
                        button1.globalPos = mapToGlobal(mouseX, mouseY)
                        console.log(button1.globalPos)
                        button1.checked = button1.checked === false ? true : false
                        backend.buttonClicked()
                    }
                }
            }
        }
    }

    property var window2: Window {
        id: applicationWindow2

        visible: true
        width: 1920
        height: 1080
        x: Screen.desktopAvailableWidth/2
        y: 0

        visibility: ApplicationWindow.Windowed

        objectName: "applicationWindow2"

        Item {
            id: rightScreen

            anchors.fill: parent

            Rectangle {
                id: button2

                property bool checked: false
                property point globalPos

                width: 120
                height: 120
                radius: 40
                color: button2.checked ? "blue" : "red"
                anchors.centerIn: parent

                Text {
                    anchors.centerIn: parent
                    text: button2.checked ? (Math.round(button2.globalPos.x)) + "x" + (Math.round(button2.globalPos.y))
                                          : "Click Button!"
                }

                MouseArea {
                    id: mouseArea2

                    width: parent.width
                    height: parent.height
                    anchors.centerIn: parent
                    onClicked: {
                        button2.globalPos = mapToGlobal(mouseX, mouseY)
                        console.log(button2.globalPos)
                        button2.checked = button2.checked === false ? true : false
                        backend.buttonClicked()
                    }
                }
            }
        }
    }
}
