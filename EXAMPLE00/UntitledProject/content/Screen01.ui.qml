/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.2
import QtQuick.Controls 6.2
import UntitledProject
import QtQuick.Timeline 1.0

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        text: qsTr("Hello UntitledProject")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }

    RoundButton {
        id: roundButton
        x: 813
        y: 461
        text: "+"
    }

    Slider {
        id: slider
        x: 850
        y: 582
        from: 0
        value: 1
    }

    AnimatedImage {
        id: animatedImage
        x: 660
        y: 299
        width: 100
        height: 100
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Timeline {
        id: timeline00
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                pingPong: true
                loops: -1
                duration: 1000
                running: true
                to: 1000
                from: 0
            }
        ]
        endFrame: 1000
        enabled: true
        startFrame: 0

        KeyframeGroup {
            target: slider
            property: "value"
            Keyframe {
                frame: 0
                value: 0
            }

            Keyframe {
                frame: 1000
                value: 1
            }
        }
    }
}
