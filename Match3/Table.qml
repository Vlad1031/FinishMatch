import QtQuick 2.15
import Match3model 1.0

GridView{
    id: root
    interactive: false
    cellWidth: width / root.model.myColumns()
    cellHeight: height / root.model.myRows()

    property int countMove: 0
    property int countScore: 0
    property int index_to: 0
    property variant nameColor
    property alias restartGrid: match3model

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

        Rectangle{
            id: spheres
            anchors.fill: backgroundDelegate
            anchors.margins: 3
            width: cellWidth; height: cellHeight
            radius: 50
            color: model.color
        }

        state: "from"
        states: [
            State{
                name: "to"
                PropertyChanges { target: spheres }
            }
        ]

        MouseArea{
            anchors.fill: parent
            onClicked: {
                root.state = (root.state === "from" ? "to" : "from")
                parent.state = (parent.state === "from" ? "to" : "from")

                console.log("Index:", index, ";", "Color:", spheres.color)

                if(root.state == "to"){
                    index_to = index
                    nameColor = spheres.color
                }

                if(root.state == "from"){
                    root.model.move(index, index_to)
                    if(root.model.combinations()){
                        root.model.drop_match()
                        if(countMove >= 4 || root.model.gameOver()){
                            gameOver.open()
                        }
                        else{
                            root.model.drop_match()
                            countMove++
                        }
                        countScore = root.model.score()
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
            duration: 400
        }
        onRunningChanged: {
            if(!running){
                if(root.model.combinations()){
                    root.model.drop_match()
                    if(countScore > 20){
                        gameOver.open()
                    }
                    else{
                        root.model.drop_match()
                    }
                }
            }
        }
    }

    add: newSphers
    Transition {
        id: newSphers
        NumberAnimation{
            properties: "y"
            duration: 400
            from: -100
        }
        onRunningChanged: {
            if(!running){
                if(root.model.combinations()){
                    root.model.drop_match()
                    if(countScore > 20){
                        gameOver.open()
                    }
                    else{
                        root.model.drop_match()
                    }
                }
            }
        }
    }
}
