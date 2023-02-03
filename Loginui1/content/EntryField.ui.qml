

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
    width: 500
    height: 100

    implicitWidth: Math.max(
                       buttonBackground ? buttonBackground.implicitWidth : 0,
                       textItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        buttonBackground ? buttonBackground.implicitHeight : 0,
                        textItem.implicitHeight + topPadding + bottomPadding)
    leftPadding: 4
    rightPadding: 4

    text: "My Button"
    hoverEnabled: false

    background: buttonBackground
    Rectangle {
        id: buttonBackground
        color: "#00000000"
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        radius: 50
        border.color: "#ffffff"
    }

    contentItem: textItem
    Text {
        id: textItem
        text: control.text
        font.pixelSize: 34

        opacity: enabled ? 1.0 : 0.3
        color: "#ffffff"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        leftPadding: 50
    }

    states: [
        State {
            name: "normal"
            when: !control.down

            PropertyChanges {
                target: buttonBackground
                color: "#00000000"
                border.color: "#ffffff"
            }

            PropertyChanges {
                target: textItem
                color: "#ffffff"
                font.pixelSize: 34
            }
        },
        State {
            name: "down"
            when: control.down
            PropertyChanges {
                target: textItem
                color: "#ffffff"
                font.pixelSize: 34
            }

            PropertyChanges {
                target: buttonBackground
                color: "#28e7e7e7"
                border.color: "#00000000"
            }
        }
    ]
}
