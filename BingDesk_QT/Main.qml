import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("BingDesk_QT")

    // 隐藏标题栏
        flags: Qt.FramelessWindowHint

        // 设置窗口为完全透明
            color: Qt.rgba(0, 0, 6, 0.6)

            Button {
                text: "Fetch Bing Wallpaper"
                anchors.centerIn: parent
                onClicked: wallpaperManager.fetchWallpaper()
            }
}
