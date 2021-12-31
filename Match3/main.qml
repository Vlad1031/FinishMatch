import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.4

ApplicationWindow{
    id: root
    width: 650
    height: 650
    visible: true
    title: "Match3"
    color: "#a9a9a9"
    minimumWidth: 450
    minimumHeight: 450

    Table{
        anchors.fill: parent
    }

    ButtonRestart{
        onPressed: {
            rectColor = "#FF0000"
            win.open()
        }
        onReleased: { rectColor = "#ffff00" }
    }

    Label{
        id: label_move
        text: "move"
        color: "#000000"
        anchors.margins: 100
        anchors.left: parent.left
    }

    Label{
        id: label_score
        text: "score"
        color: "#000000"
        anchors.margins: 100
        anchors.right: parent.right
    }

    GameOver{
        id: win
    }
}
