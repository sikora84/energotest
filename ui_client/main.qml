import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Window {
    visible: true
    width: 640
    height: 480
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    title: qsTr("Energotest Client")

    MouseArea {
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
            TextField {
                id: login
                x: 26
                y: 37
                width: 199
                height: 24
                Layout.fillWidth: true
                placeholderText: "Username"
            }

            TextField {
                id: password
                x: 251
                y: 38
                width: 199
                height: 23
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: TextInput.PasswordEchoOnEdit
            }

            Button {
                id: get
                x: 491
                y: 38
                width: 112
                height: 25
                text: "Get Entries"
                Layout.fillWidth: true
                onClicked: entries.text = LibraryWrapper.getAllEntries(login.text, password.text)
            }

            Button {
                id: register
                x: 491
                y: 90
                width: 112
                height: 25
                text: "Register User"
                Layout.fillWidth: true
                onClicked: LibraryWrapper.createUser(login.text, password.text)
            }

            Button {
                id: add
                x: 139
                y: 146
                width: 112
                height: 25
                text: "Add Entry"
                Layout.fillWidth: true
                onClicked: LibraryWrapper.createEntry(login.text, password.text, txt.text, priority.text, timestamp.text)
            }

            Label {
                x: 26
                y: 81
                width: 74
                height: 17
                text: "Priority"
            }

            TextField {
                id: priority
                x: 26
                y: 97
                width: 91
                height: 24
                placeholderText: "0-100"
                validator: IntValidator {
                        bottom: 0
                        top: 100
                    }
                Layout.fillWidth: true
            }

            Label {
                x: 26
                y: 132
                width: 74
                height: 17
                text: "Timestamp"
            }

            TextField {
                id: timestamp
                x: 26
                y: 146
                width: 91
                height: 24
                placeholderText: "0-99999"
                validator: IntValidator {
                        bottom: 0
                        top: 99999
                    }
                Layout.fillWidth: true
            }

            Label {
                x: 139
                y: 81
                width: 74
                height: 17
                text: "Text"
            }

            TextField {
                id: txt
                x: 139
                y: 97
                width: 311
                height: 24
                placeholderText: "Text"
                Layout.fillWidth: true
            }

            TextArea {
                id: entries
                x: 26
                y: 190
                width: 577
                height: 252
                textColor: "#1b2024"
                Layout.fillWidth: true
            }
    }
}
