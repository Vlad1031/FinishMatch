import QtQuick 2.15
import Match3model 1.0

GridView{
    id: root
    interactive: false

    model: Match3model{
        id: match3model
    }

    delegate: Item{
        id: backgroundDelegate
        width: root.cellWidth; height: root.cellHeight

        Sphere{
            anchors.fill: backgroundDelegate
            anchors.margins: 3
            width: cellWidth; height: cellHeight
        }
    }

    move: transit
    displaced: transit

    Transition {
        id: transit
        NumberAnimation{
            properties: "x, y"
            duration: 200
        }
    }
}

