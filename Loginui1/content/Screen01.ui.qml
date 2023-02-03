

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.4
import QtQuick.Controls 6.4
import Loginui1
import QtQuick.Timeline 1.0

Rectangle {
    id: rectangle
    width: Constants.width
    height: 1280

    color: Constants.backgroundColor
    state: "login"

    Image {
        id: adventurePage
        anchors.right: parent.right
        anchors.fill: parent
        source: "image/adventurePage.jpg"
        anchors.rightMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: qt_logo_green_128x128px
        anchors.top: parent.top
        source: "image/qt_logo_green_128x128px.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 40
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: tagLine
        color: "#ffffff"
        text: qsTr("Are you ready to explore?")
        anchors.top: qt_logo_green_128x128px.bottom
        font.pixelSize: 50
        font.family: "Times New Roman"
        anchors.horizontalCenterOffset: 0
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter

        SequentialAnimation {
            id: animation

            ColorAnimation {
                id: colorAnimation1
                target: rectangle
                property: "color"
                to: "#2294c6"
                from: Constants.backgroundColor
            }

            ColorAnimation {
                id: colorAnimation2
                target: rectangle
                property: "color"
                to: Constants.backgroundColor
                from: "#2294c6"
            }
        }
    }

    EntryField {
        id: username
        text: "enter Username or Email"
        anchors.top: tagLine.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 170
    }

    EntryField {
        id: repeatPassword
        x: 110
        y: 554
        opacity: 0
        text: "Repeat Password"
        anchors.top: password.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }

    EntryField {
        id: password
        text: "Password"
        anchors.top: username.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }


    Column {
        id: buttons
        y: 904
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 50
        spacing: 10
        PushButton {
            id: login
            text: "Continue"
        }

        PushButton {
            id: createAccount
            text: "Create Account"

            Connections {
                target: createAccount
                onClicked: rectangle.state = "createAccount"
            }
        }
    }


    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: toCreateAccountState
                loops: 1
                duration: 1000
                running: false
                to: 1000
                from: 0
            }
        ]
        endFrame: 1000
        enabled: true
        startFrame: 0

        KeyframeGroup {
            target: repeatPassword
            property: "opacity"
            Keyframe {
                frame: 0
                value: 0
            }

            Keyframe {
                frame: 1000
                value: 1
            }
        }

        KeyframeGroup {
            target: createAccount
            property: "opacity"
            Keyframe {
                frame: 0
                value: 1
            }

            Keyframe {
                frame: 1000
                value: 0
            }
        }

        KeyframeGroup {
            target: repeatPassword
            property: "anchors.topMargin"
            Keyframe {
                frame: 0
                value: -100
            }

            Keyframe {
                easing.bezierCurve: [0.39,0.575,0.565,1,1,1]
                frame: 1000
                value: 20
            }
        }
    }

    states: [
        State {
            name: "login"
        },
        State {
            name: "createAccount"

            PropertyChanges {
                target: timeline
                enabled: true
            }

            PropertyChanges {
                target: toCreateAccountState
                running: true
            }
        }
    ]
}
