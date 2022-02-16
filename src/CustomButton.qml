import QtQuick 2.0
import QtQuick.Controls 2.3

ToolButton {
    id: buttonid
    text: qsTr("ToolButton")
    width: 120


    contentItem: Image {
        id: imageid
        source: undefined
    }
    background: Rectangle {
        anchors.fill: parent
        implicitWidth: 40
        implicitHeight: 40

        color: Qt.darker("#333333", buttonid.enabled
                 && (buttonid.checked
                     || buttonid.highlighted) ? 1.5 : 1.0)
        opacity: enabled ? 1 : 0.3
        visible: buttonid.down || (buttonid.enabled && (buttonid.checked || buttonid.highlighted))
    }
}




