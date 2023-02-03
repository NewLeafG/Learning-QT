import QtQuick
import Charts

//Window {
//    width: 640
//    height: 480
//    visible: true
//    title: qsTr("Hello World")

    Item{
        width: 300; height: 200

        PieChart {
            id: aPieChart
            anchors.centerIn: parent
            width:100; height: 100
            color: "red"

            onChartCleared: console.log("The chart has been cleared")
        }

        MouseArea {
            anchors.fill: parent
            onClicked: aPieChart.clearChart()
        }

        Text {
            anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 20}
            text: "Click anywhere to clear the chart"
        }
    }

//}
