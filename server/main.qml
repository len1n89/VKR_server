import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Server")
    TabView {
        id: mainTabView

        anchors.fill: parent
        Tab {
            id: dashTab
            title: "Dashboard"
            DashView {}
        }
        Tab {
            id: setingsTab

            title: "Settings"
            TabView {

                id: setingsTabView
                anchors.fill: parent
                Tab {
                    title: "Agents"
                }
                Tab {
                    title: "Metrics"
                }
                Tab {
                    title: "Alerts"
                }
                Tab {
                    title: "Tresholds"
                }
                Tab {
                    title: "DB"
                }
                Tab {
                    title: "Users"
                    UsersView {}
                }
                Tab {
                    title: "Notifier"
                }
            }
        }
    }

}
