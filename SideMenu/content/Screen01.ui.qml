

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import SideMenu 1.0

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Button {
        id: button
        text: qsTr("Press me")
        anchors.verticalCenter: parent.verticalCenter
        checkable: true
        anchors.horizontalCenter: parent.horizontalCenter
    }


    Image {
        id: back_195_184
        source: "assets/back_195_184.png"
        fillMode: Image.PreserveAspectFit

        Row {
            id: row
            x: 502
            y: 13
            width: 1001
            height: 65
            spacing: -18

            CustomButton {
                id: customButton
                autoExclusive: true
            }

            CustomButton {
                id: customButton1
                autoExclusive: true
            }

            CustomButton {
                id: customButton2
                autoExclusive: true
            }

            CustomButton {
                id: customButton3
                autoExclusive: true
            }

            CustomButton {
                id: customButton4
                autoExclusive: true
            }

            CustomButton {
                id: customButton5
                autoExclusive: true
            }
        }
    }

    Text {
        id: label
        color: "#ffffff"
        text: qsTr("Hello SideMenu")
        anchors.top: button.bottom
        font.family: Constants.font.family
        anchors.topMargin: 45
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

    Connections {
        target: rectangle
        onParentChanged: label.Text="changed"
    }
    states: [
        State {
            name: "clicked"
            when: button.checked

            PropertyChanges {
                target: label
                text: qsTr("Button Checked")
            }
        }
    ]
}
