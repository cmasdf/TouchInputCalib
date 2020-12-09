import QtQuick 2.13

Rectangle {
    id: mainArea

    property string deviceInfo
    property bool touchAreaVisible

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

        property bool checked: false

        width: 200
        height: 200
        radius: 100
        color: touchArea.checked ? "#82CA9C" : "#F26C4F"
        anchors.centerIn: parent
        opacity: touchAreaVisible ? 1 : 0

        Text {
            anchors.centerIn: parent
            font.pixelSize: 18
            text: touchArea.checked ? Backend.lastInput.x + "x" + Backend.lastInput.y : "Push the Button!"
        }

        MouseArea {
            id: mouseArea

            width: parent.width
            height: parent.height
            anchors.centerIn: parent
            onClicked: {
                Backend.lastInput = mapToGlobal(mouseArea.x + mouseArea.width/2, mouseArea.y + mouseArea.height/2)
                touchArea.checked = touchArea.checked === false ? true : false
                Backend.touchAreaClicked()
            }
        }
    }
}