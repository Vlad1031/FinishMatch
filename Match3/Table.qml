import QtQuick 2.15
import Match3model 1.0

GridView{
    id: root
    interactive: false
    cellWidth: width / root.model.myColumns()
    cellHeight: height / root.model.myRows()

    property int countMove: 0
    property int countScore: 0

    model: Match3model{
        id: match3model
    }

    state: "from"
    states: [
        State{
            name: "to"
            PropertyChanges { target: root }
        }
    ]

    delegate: Item{
        id: backgroundDelegate
        width: root.cellWidth; height: root.cellHeight

        Sphere{
            id: spheres
            anchors.fill: backgroundDelegate
            anchors.margins: 3
            width: cellWidth; height: cellHeight
        }

        state: "from"
        states: [
            State{
                name: "to"
                PropertyChanges { target: spheres; scale: 0.8 }
            }
        ]

        MouseArea{
            anchors.fill: parent
            onClicked: {
                root.state = (root.state === "from" ? "to" : "from")
                parent.state = (parent.state === "from" ? "to" : "from")

                console.log("index =", index, root.state)

                if(root.state == "from"){
                    if(root.model.move(index)){
                        countMove++
                        parent.state = (parent.state === "from" ? "from" : "from")
                        console.log("count move =", countMove)
                    }
                }
            }
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
