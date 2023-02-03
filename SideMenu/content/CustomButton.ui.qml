

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: control
    width: 180
    height: 70

    implicitWidth: Math.max(
                       buttonBackground ? buttonBackground.implicitWidth : 0,
                       textItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        buttonBackground ? buttonBackground.implicitHeight : 0,
                        textItem.implicitHeight + topPadding + bottomPadding)
    leftPadding: 4
    rightPadding: 4

    text: "My Button"

    background: buttonBackground
    Rectangle {
        id: buttonBackground
        color: "#00000000"
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        radius: 2
        border.color: "#047eff"
        border.width: 0
    }

    contentItem: textItem

    Image {
        id: background
        x: 16
        y: 16
        source: "assets/inactive_button.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: contentItem
        x: -1
        source: "assets/hover_button.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: active_button
        y: -1
        source: "assets/active_button.png"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: textItem
        width: 172
        height: 29
        font.pixelSize: 32

        opacity: enabled ? 1.0 : 0.3
        color: "#ffffff"
        text: "pressed"
        anchors.left: parent.left
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: -6
        anchors.topMargin: -10
    }

    Connections {
        target: control
        onClicked: control.checked = "true"
    }
    states: [
        State {
            name: "checked"
            when: control.checked

            PropertyChanges {
                target: textItem
                text: control.state
            }

            PropertyChanges {
                target: background
                visible: false
            }

            PropertyChanges {
                target: contentItem
                visible: false
            }
        },
        State {
            name: "hover"
            when: control.hovered && !control.checked && !control.pressed

            PropertyChanges {
                target: textItem
                text: control.state
                anchors.leftMargin: -1
                anchors.topMargin: -7
            }

            PropertyChanges {
                target: background
                visible: false
            }

            PropertyChanges {
                target: active_button
                visible: false
            }
        },
        State {
            name: "normal"
            when: !control.pressed && !control.checked && !control.hovered

            PropertyChanges {
                target: textItem
                x: 15
                y: 33
                text: control.state
                anchors.leftMargin: 12
                anchors.topMargin: 5
            }

            PropertyChanges {
                target: active_button
                visible: false
            }

            PropertyChanges {
                target: contentItem
                visible: false
            }

            PropertyChanges {
                target: control
                checkable: true
            }
        }
    ]
}
