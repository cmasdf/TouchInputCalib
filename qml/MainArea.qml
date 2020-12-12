import QtQuick 2.13

Rectangle {
    id: mainArea

    property string deviceInfo
    property bool touchAreaVisible
    property bool touchAreaActive
    property bool showResult
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
        id: touchArea

        width: 200
        height: 200
        radius: 100
        color: mainArea.showResult ? "#F26C4F" : "#82CA9C"
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