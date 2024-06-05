import QtQuick 2.6
import QtQuick.Controls 1.4

Item {

    ListModel {
        id: model

         ListElement {
             name: "PC1"
             ip: "192.168.2.15"
             status: "CONNECTED"
             alert: "Подключен"
         }
         ListElement {
             name: "PC2"
             ip: "10.10.0.5"
             status: "CONNECTED"
             alert: "Обхем свободной оперативной памяти < 95%"
         }
         ListElement {
             name: "PC3"
             ip: "192.168.1.123"
             status: "CONNECTED"
             alert: "Нагрузка ЦП больше 90%"
         }
         ListElement {
             name: "PC4"
             ip: "192.168.1.122"
             status: "DISCONNECTED"
             alert: "Отключен "
         }
         ListElement {
             name: "DNS-Server"
             ip: "192.168.1.2"
             status: "CONNECTED"
             alert: "Заканчивается свободное место на диске D"
         }
         ListElement {
             name: "DHCP-Server"
             ip: "192.168.1.1"
             status: "CONNECTED"
             alert: "Подключен"
         }
         ListElement {
             name: "PC15"
             ip: "192.168.2.66"
             status: "CONNECTED"
             alert: "Подключен"
         }
     }

    Component {
        id: delegate

        Row {
            spacing: 5
            topPadding: 10
            leftPadding: 10
            Rectangle{
                border.width: 1
                width: 120
                height: 20
                radius: 3
                Text {
                    anchors.centerIn: parent
                    text: model.name
                }
            }
            Rectangle{
                border.width: 1
                width: 110
                height: 20
                radius: 3
                Text {
                    anchors.centerIn: parent
                    text: model.ip
                }
            }
            Rectangle{
                border.width: 1
                width: 110
                height: 20
                radius: 3
                color: {
                    if(model.status !==  "CONNECTED")
                        return "red"
                    else
                        return "green"
                }
                Text {
                    anchors.centerIn: parent
                    text: model.status
                }
            }
            Text {
                text: model.alert
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: model
        delegate: delegate
    }
}
