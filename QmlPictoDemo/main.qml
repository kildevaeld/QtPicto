import QtQuick 2.5
import QtQuick.Window 2.2
import QmlPicto 0.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log('hello')
            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
            console.log(Awesome.address_book)

        }
    }

    Picto {
        source: Material.access_alarm
        anchors.fill: parent
        color: 'red'
        asynchronous: true
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
