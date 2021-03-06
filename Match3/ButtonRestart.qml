import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.4

Button{
    id: root
    property alias rectColor: rect_but.color

    background: Rectangle{
        id: rect_but
        implicitWidth: 90
        implicitHeight: 40
        color: "#ffff00"
        radius: 5
        Text{
            anchors.centerIn: rect_but
            text: "Restart"
            font.pointSize: Math.min(width, height) / 1.5
            font.bold: true
        }
    }
    y: 10
    anchors.horizontalCenter: parent.horizontalCenter
}
