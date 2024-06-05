import QtQuick 2.6
import QtQuick.Controls 1.4

Item {

    Button {
        id: addButton
        width: 60
        height: 20
        text: "Add User"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    ListView {
        anchors.top: addButton.bottom
        width: 300
        height: 500
        model: usersModel
        delegate: userDelegate
    }

    Component {
        id: userDelegate

        Row {
            spacing: 5
            topPadding: 10
            leftPadding: 10
            Rectangle{
                border.width: 1
                width: 60
                height: 20
                radius: 3
                Text {
                    anchors.centerIn: parent
                    text: model.name
                }
            }
            Button {
                width: 60
                height: 20
                text: "Edit"
            }
            Button {
                width: 60
                height: 20
                text: "Delete"
            }
        }
    }

    ListModel {
        id: usersModel

         ListElement {
             name: "User1"
         }
         ListElement {
             name: "User2"
         }
         ListElement {
             name: "User3"
         }
         ListElement {
             name: "User4"
         }
     }
}
