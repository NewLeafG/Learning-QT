import QtQuick 2.15
import QtQuick.Window 2.15
import an.qt.ColorMaker 1.0
import QtQuick.Controls 2.15
import an.qt.KjUsb 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle{
        id:rectColor
        color: "gray"
        anchors.fill: parent

        Text{
            id:timeLabel;
            anchors.left:parent.left;
            anchors.leftMargin: 4;
            anchors.top:parent.top;
            anchors.topMargin: 4;
            font.pixelSize: 26;
        }

        ColorMaker{
            id:colorMaker;
            color:Qt.green;
        }

        Rectangle {
            id: colorRect;
            anchors.centerIn: parent;
            width: 200;
            height: 200;
            color: "blue";
        }

        Button {
            id: start;
            text: "start";
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 4;
            onClicked: {
                colorMaker.start();
            }
        }
        Button {
            id: stop;
            text: "stop";
            anchors.left: start.right;
            anchors.leftMargin: 4;
            anchors.bottom: start.bottom;
            onClicked: {
                colorMaker.stop();
            }
        }


        function changeAlgorithm(button, algorithm){
            switch(algorithm)
            {
            case 0:
                button.text = "RandomRGB";
                break;
            case 1:
                button.text = "RandomRed";
                break;
            case 2:
                button.text = "RandomGreen";
                break;
            case 3:
                button.text = "RandomBlue";
                break;
            case 4:
                button.text = "LinearIncrease";
                break;
            }
        }

        Button {
            id: colorAlgorithm;
            text: "RandomRGB";
            anchors.left: stop.right;
            anchors.leftMargin: 4;
            anchors.bottom: start.bottom;
            onClicked: {
                var algorithm = (colorMaker.algorithm() + 1) % 5;
                rectColor.changeAlgorithm(colorAlgorithm, algorithm);
                colorMaker.setAlgorithm(algorithm);
            }
        }


        Button {
             id: quit;
             text: "quit";
             anchors.left: colorAlgorithm.right;
             anchors.leftMargin: 4;
             anchors.bottom: start.bottom;
             onClicked: {
                 Qt.quit();
             }
         }

         Component.onCompleted: {
             colorMaker.color = Qt.rgba(0,180,120, 255);
             colorMaker.setAlgorithm(ColorMaker.RandomRGB);
             rectColor.changeAlgorithm(colorAlgorithm, colorMaker.algorithm());
         }

         Connections {
             target: colorMaker;
             onCurrentTime:{
                 timeLabel.text = strTime;
                 timeLabel.color = colorMaker.timeColor;
             }
         }

         Connections {
             target: colorMaker;
             onColorChanged:{
                 colorRect.color = color;
             }
         }

         Connections {
             target: m_kjUsb;
             onMsgReceived:{
                 colorRect.color = color;
             }
         }

    }

    Rectangle{
        id:rectUsb
        color: "green"
        anchors.fill: parent
        opacity: 0.5

        KjUsb{
            id:m_kjUsb
        }

        Text{
            id:t_test;
            anchors.left:parent.left;
            anchors.leftMargin: 40;
            anchors.top:parent.top;
            anchors.topMargin: 40;
            font.pixelSize: 26;
        }

        Button {
             id: pushButton_detectusb;
             text: "检测设备";
             anchors.top: parent.top;
             anchors.topMargin: 40;
             anchors.right: parent.right;
             onClicked: {
                 var stringList=m_kjUsb.on_pushButton_detectusb_clicked().split(',');

                 var num=stringList.length;
                 num-=1;
                for(var i=0;i<num;i++)
                {
                    console.log("stringList", i, stringList[i]);
//                    stringList[i]=(i.toString()+'.'+stringList[i]);
                    listDevices.append({text:stringList[i]});
                }
                if(num>0)
                {
                    cb_devices.currentIndex=0;
                }
             }
         }

        ComboBox {
            id: cb_devices
            editable: true
            anchors.top: pushButton_detectusb.bottom;
            anchors.topMargin: 4;
            anchors.right: parent.right;
            model: ListModel {
                id: listDevices
            }
        }

        Button {
             id: pushButton_usblock;
             text: "连接设备";
             anchors.top: cb_devices.bottom;
             anchors.topMargin: 4;
             anchors.right: parent.right;
             onClicked: {
                 var ret;

                     if(pushButton_usblock.text==="连接设备")
                     {
                         ret=m_kjUsb.on_pushButton_usblock_clicked(cb_devices.currentText,true);
                         if(ret===true)
                         {

                         pushButton_usblock.text="断开连接";
                         }
                     }
                     else if(pushButton_usblock.text==="断开连接")
                     {
                         ret=m_kjUsb.on_pushButton_usblock_clicked(cb_devices.currentText,false);
                         if(ret===true)
                         {
                         pushButton_usblock.text="连接设备";
                         }
                     }

             }
         }

        Connections {
            target: m_kjUsb;
            onMsgReceived:{
                colorRect.color = color;
            }
        }

   }

}
