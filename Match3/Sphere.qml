import QtQuick 2.15

Rectangle {
    id: rect
    radius: 50

    gradient: Gradient {
        GradientStop { position: 0.0; color: "lightsteelblue" }
        GradientStop { position: 1.0; color: "blue" }
    }
}
