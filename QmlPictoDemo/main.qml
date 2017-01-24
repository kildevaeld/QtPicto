import QtQuick 2.5
import QtQuick.Window 2.2
import QmlPicto 0.1
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    toolBar: ToolBar {
        RowLayout {
            ToolButton {

                action: Action {
                    text: "Hello"
                    iconName: 'text-bold'
                    iconSource: Picto.icon(Awesome.plus)
                }
            }
        }

    }

    Image {
        source: Picto.image(Awesome.adjust)
        width:200
        height:200
        sourceSize {
            width: 200; height: 200
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log('hello')
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
            console.log(Awesome.address_book)
            picto.name = Awesome.address_book
        }
    }

    PictoImage {
        id: picto
        name: Material.access_alarm
        anchors.fill: parent
        color: 'red'
    }



    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
}
