import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import "qml/"

QtObject {
    id: root

    property var window1: Window {
        id: "applicationWindow1"

        visible: true
        width: 1920
        height: 1080
        x: 0
        y: 0

        visibility: ApplicationWindow.Windowed

        objectName: "applicationWindow1"

        TouchCircle {
            id: leftScreen
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

        TouchCircle {
            id: rightScreen
        }
    }
}
