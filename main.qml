import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13

import "qml/"

Instantiator {
    id: windowInstantiator

    property var visibility: ApplicationWindow.Windowed

    model: ApplicationDataModel

    delegate: Window {
        id: applicationWindow

        // device info string
        property string deviceInfo:  model.deviceInfo
        // touch area visible flag
        property bool touchAreaVisible: false
        // touch area active (clickable) flag
        property bool touchAreaActive: true
        // show result flag
        property bool showResult: false
        // result is wrong (wrong click) flag
        property bool wrongResult: false
        // user info string
        property string userInfo: "Push this button!"

        visibility: windowInstantiator.visibility
        visible: true

        title: model.title
        objectName: model.objectName
        width: model.width
        height: model.height
        x: model.x
        y: model.y

        MainArea {
            id: mainArea

            deviceInfo: applicationWindow.deviceInfo
            touchAreaVisible: applicationWindow.touchAreaVisible
            touchAreaActive: applicationWindow.touchAreaActive
            showResult: applicationWindow.showResult
            wrongResult: applicationWindow.wrongResult
            userInfo: applicationWindow.userInfo
        }
    }
}
