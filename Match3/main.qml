import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.4

ApplicationWindow{
    id: root
    width: 650; height: 650
    visible: true
    title: "Match3"
    color: "#a9a9a9"
    minimumWidth: 650; minimumHeight: 650
    maximumWidth: 650; maximumHeight: 650

    Rectangle{
        width: 610; height: 570
        x: 20; y: 60
        color: "#a9a9a9"
        border.color: "#000000"
        visible: true

        Table{
            anchors.fill: parent
            anchors.margins: 5
        }
    }

    ButtonRestart{
        y: 10
        onPressed: {
            rectColor = "#FF0000"
            win.open()
        }
        onReleased: { rectColor = "#ffff00" }
    }

    Label{
        id: label_move
        y: 10
        text: "move"
        color: "#000000"
        anchors.margins: 100
        anchors.left: parent.left
    }

    Label{
        id: label_score
        y: 10
        text: "score"
        color: "#000000"
        anchors.margins: 100
        anchors.right: parent.right
    }

    GameOver{
        id: win
    }
}
