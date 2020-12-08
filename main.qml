import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import "qml/"

QtObject {
    id: root

    property var window0: Window {
        id: applicationWindow0

        property string device

        visible: true

        visibility: ApplicationWindow.Windowed

        objectName: "applicationWindow0"

        MainArea {
            id: leftScreen
            device: applicationWindow0.device
        }
    }

    property var window1: Window {
        id: applicationWindow1

        property string device

        visible: true

        visibility: ApplicationWindow.Windowed

        objectName: "applicationWindow1"

        MainArea {
            id: rightScreen
            device: applicationWindow1.device
        }
    }
}
