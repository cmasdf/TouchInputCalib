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

        property string deviceInfo: model.deviceInfo
        property bool touchAreaVisible: false
        property bool touchAreaActive: true
        property bool showResult: false
        property bool wrongResult: false
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
