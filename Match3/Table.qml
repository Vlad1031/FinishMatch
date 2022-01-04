import QtQuick 2.15

GridView{
    id: root
    interactive: false
    model: 15

    Rectangle {
        id: rect
        width: cellWidth; height: cellHeight
        radius: 50
        anchors.margins: 3

        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightsteelblue" }
            GradientStop { position: 1.0; color: "blue" }
        }
    }
}

