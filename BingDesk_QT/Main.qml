import QtQuick
import QtQuick.Controls
import QtQuick.Window 2.15

Window {
    width: 360
    height: 50
    x: Screen.width-366
    y: 3
    visible: true
    title: qsTr("BingDesk_QT")

    // 隐藏标题栏
    flags: Qt.FramelessWindowHint

    // 设置窗口为完全透明//”#AARRGGBB”
    color: "#06000006"

    Text {
        id: text_notification
        color: "white"
        width: parent.width-2
        height: parent.height-2
        anchors.margins: 6
        anchors.left: parent.left
        anchors.top: parent.top
        // anchors.centerIn: parent
        wrapMode: Text.WordWrap
    }

    Binding {
        target: text_notification
        property: "text"
        value: wallpaperManager.notificationStr
    }

}
