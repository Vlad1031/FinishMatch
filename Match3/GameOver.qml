import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.4

Popup{
    id: popup
    anchors.centerIn: parent
    width: 400
    height: 200
    focus: true
    dim: true

    Text {
        text: "Game Over"
        font.pointSize: 25
        font.bold: true

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
    }

    background: Rectangle {
        border.width: 1
        radius: 15
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightsteelblue" }
            GradientStop { position: 1.0; color: "red" }
        }
    }

    Button{
        id: button_restart

        background: Rectangle{
            x: 180
            id: rect_restart
            implicitWidth: 90
            implicitHeight: 40
            color: "#ffff00"
            radius: 5
            Text{
                anchors.centerIn: rect_restart
                text: "Restart"
                font.pointSize: 10
                font.bold: true
            }
        }
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }

    Button{
        id: button_close

        background: Rectangle{
            id: rect_close
            implicitWidth: 90
            implicitHeight: 40
            color: "#ffff00"
            radius: 5
            Text{
                anchors.centerIn: rect_close
                text: "Close"
                font.pointSize: 10
                font.bold: true
            }
        }
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    MouseArea{
        anchors.fill: button_close
        onClicked: Qt.quit()
    }

    closePolicy: Popup.CloseOnEscape
}
