import QtQuick 2.13
import QtQuick.Controls 2.13

import io.qt.examples.backend 1.0

Item {
    visible: true

    ApplicationWindow {
        visible: true
        width: 1920
        height: 1080

        visibility: ApplicationWindow.Windowed
        screen: Qt.application.screens[1]

        objectName: "applicationWindow1"

        /*BackEnd {
            id: backend1
        }*/

        Item {
            id: leftScreen

            width: parent.width/2
            height: parent.height
            anchors.left: parent.left

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
}


    /*ApplicationWindow {
        objectName: "applicationWindow2"
        visible: true
        width: 1920
        height: 1080

        BackEnd {
            id: backend2
        }

        Item {
            id: rightScreen

            width: parent.width/2
            height: parent.height
            anchors.right: parent.right

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
}*/
