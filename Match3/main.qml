import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.4
import Match3model 1.0

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
            id: table
            anchors.fill: parent
            anchors.margins: 5
            clip: true
        }
    }

    ButtonRestart{
        onPressed: {
            rectColor = "#FF0000"
            gameOver.open()
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

        Label{
            y: 20
            text: table.countMove
            color: "#000000"
            anchors.margins: 15
            anchors.left: parent.left
        }
    }

    Label{
        id: label_score
        y: 10
        text: "score"
        color: "#000000"
        anchors.margins: 100
        anchors.right: parent.right

        Label{
            y: 20
            text: table.countScore
            color: "#000000"
            anchors.margins: 15
            anchors.left: parent.left
        }
    }

    GameOver{
        id: gameOver
    }
}
