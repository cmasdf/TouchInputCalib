import QtQuick 2.13
import QtGraphicalEffects 1.14

Rectangle {
    id: mainArea

    property string deviceInfo
    property bool touchAreaVisible
    property bool touchAreaActive
    property bool showResult
    property bool wrongResult
    property string userInfo

    anchors.fill: parent
    color: "#2B2B2B"

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
            text: mainArea.deviceInfo
        }
    }

    Rectangle {
        id: closeButton

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 40
        anchors.topMargin: 40
        width: 50
        height: 50
        radius: 25
        color: "#F26C4F"

        Image {
            id: closeIcon

            width: 22
            height: 22
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: "qrc:/res/img/close.png"
            sourceSize.height: 22

            ColorOverlay {
                anchors.fill: parent
                source: parent
                color: "white"
            }
        }

         MouseArea {
            id: closeArea

            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            onClicked: {
               Qt.quit()
            }
        }
    }

    RectangularGlow {
        id: effect
        anchors.fill: touchArea
        glowRadius: 6
        spread: 0.2
        color: mainArea.showResult && mainArea.wrongResult ? "#F26C4F" : "#82CA9C"
        cornerRadius: touchArea.radius + glowRadius
        opacity: touchAreaVisible ? 1 : 0

        Behavior on opacity {
            NumberAnimation {
                duration: 2000;
                easing.type: Easing.InOutQuad
            }
        }
    }

    Rectangle {
        id: touchArea

        width: 200
        height: 200
        radius: 100
        color: mainArea.showResult && mainArea.wrongResult ? "#F26C4F" : "#82CA9C"
        anchors.centerIn: parent
        opacity: touchAreaVisible ? 1 : 0

        Behavior on opacity {
            NumberAnimation {
                duration: 2000;
                easing.type: Easing.InOutQuad
            }
        }

        Text {
            anchors.centerIn: parent
            font.pixelSize: 18
            text: mainArea.showResult ? MainAreaBackend.lastInput.x + "x" + MainAreaBackend.lastInput.y : mainArea.userInfo
        }

        MouseArea {
            id: mouseArea

            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            enabled: mainArea.touchAreaActive && (touchArea.opacity == 1 || touchArea.opacity == 0)
            onClicked: {
                MainAreaBackend.lastInput = mapToGlobal(mouseArea.x + mouseArea.width/2, mouseArea.y + mouseArea.height/2)
                MainAreaBackend.touchAreaClicked(MainAreaBackend.lastInput)
            }
        }
    }
}