/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring
    Contact: Matthias Fehring <kontakt@buschmann23.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: accountDialog

    property string name: "Transifex"
    property string server: "https://www.transifex.com"
    property string user
    property string password
    property bool ignoreSSLErrors: false
    property int index

    property bool create: true
    property bool allSet: nameString.text !== "" && serverString.text !== "" && userString.text !== "" && passwordString.text !== ""

    canAccept: allSet
    acceptDestinationAction: PageStackAction.Pop

    Column {
        width: parent.width

        DialogHeader {
            acceptText: create ? qsTr("Create account") : qsTr("Edit account")
        }

        TextField {
            id: nameString
            anchors { left: parent.left; right: parent.right }
            label: qsTr("Display name"); text: name
            inputMethodHints: Qt.ImhUrlCharactersOnly
            EnterKey.enabled: text || inputMethodComposing
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: serverString.focus = false
        }

        TextField {
            id: serverString
            anchors { left: parent.left; right: parent.right }
            label: qsTr("Server"); text: server
            inputMethodHints: Qt.ImhUrlCharactersOnly
            EnterKey.enabled: text || inputMethodComposing
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: userString.focus = false
        }

        TextField {
            id: userString
            anchors { left: parent.left; right: parent.right }
            label: qsTr("User name"); placeholderText: label; text: user
            EnterKey.enabled: text || inputMethodComposing
            EnterKey.iconSource: "image://theme/icon-m-enter-next"
            EnterKey.onClicked: passwordString.focus = true
        }

        TextField {
            id: passwordString
            anchors { left: parent.left; right: parent.right }
            label: qsTr("Password"); placeholderText: label; text: password
            echoMode: TextInput.Password
            EnterKey.enabled: (text || inputMethodComposing) && canAccept
            EnterKey.iconSource: "image://theme/icon-m-enter-accept"
            EnterKey.onClicked: accountDialog.accept()
        }

        TextSwitch {
            id: ignoreSSLErrorsSwitch
            text: qsTr("Ignore SSL errors")
            anchors { left: parent.left; right: parent.right }
            description: qsTr("Only ignore SSL errors when you really know what you are doing. (Currently there is no system service for handling SSL certificates. For now you have to ignore SSL errors when you are using a self signed certificate.)")
            checked: ignoreSSLErrors
        }
    }

    onAccepted: create ? accountsModel.append(nameString.text, serverString.text, userString.text, passwordString.text, ignoreSSLErrorsSwitch.checked) : accountsModel.edit(nameString.text, serverString.text, userString.text, passwordString.text, ignoreSSLErrorsSwitch.checked, index)

}
