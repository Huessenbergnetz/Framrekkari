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

import QtQuick 2.2
import Sailfish.Silica 1.0
import "../js/helper.js" as HELPER

Dialog {
    id: accountDialog

    property string name: "Transifex"
    property string server: "https://www.transifex.com"
    property string user
    property string password
    property bool ignoreSSLErrors: false
    property int index
    property int type: 0

    property bool create: true
    property bool allSet: nameString.text !== "" && serverString.text !== "" && userString.text !== "" && passwordString.text !== ""

    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

    canAccept: allSet
    acceptDestinationAction: PageStackAction.Pop

    function getTypeInfo()
    {
        switch(type){
        case 0:
        default:
            return _RICHTEXT_STYLESHEET_PREAMBLE + qsTr("Transifex is a collaborative online translation platform. In order to use it you need an account on <a href='https://www.transifex.com'>transifex.com</a>.") + _RICHTEXT_STYLESHEET_APPENDIX
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        Column {
            id: column
            width: parent.width

            DialogHeader {
                acceptText: create ? qsTr("Create account") : qsTr("Edit account")
            }

            ComboBox {
                id: accType
                width: parent.width
                label: qsTr("Account type")
                currentIndex: accountDialog.type
                onCurrentIndexChanged: {
                    accountDialog.type = currentIndex
                    typeInfo.text = getTypeInfo()
                }

                menu: ContextMenu {
                    MenuItem { text: "Transifex" }
                }
            }

            Row {
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }

                Text {
                    id: typeInfo
                    text: getTypeInfo()
                    width: parent.width - icon.width
                    font.pixelSize: Theme.fontSizeTiny
                    color: Theme.secondaryColor
                    wrapMode: Text.WordWrap
                    textFormat: Text.RichText
                    onLinkActivated: { Qt.openUrlExternally(link) }
                }

                Image {
                    id: icon
                    width: 64; height: 64
                    source: HELPER.getAccountIcon(type, "m") + "?" + Theme.primaryColor
                }
            }

            TextField {
                id: nameString
                anchors { left: parent.left; right: parent.right }
                label: qsTr("Display name"); text: name
                inputMethodHints: Qt.ImhNoPredictiveText
                EnterKey.enabled: text || inputMethodComposing
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: serverString.focus = true
            }

            TextField {
                id: serverString
                anchors { left: parent.left; right: parent.right }
                label: qsTr("Server"); text: server
                inputMethodHints: Qt.ImhUrlCharactersOnly | Qt.ImhNoPredictiveText
                EnterKey.enabled: text || inputMethodComposing
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: userString.focus = true
            }

            TextField {
                id: userString
                anchors { left: parent.left; right: parent.right }
                label: qsTr("User name"); placeholderText: label; text: user
                inputMethodHints: Qt.ImhNoPredictiveText
                EnterKey.enabled: text || inputMethodComposing
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: passwordString.focus = true
            }

            TextField {
                id: passwordString
                anchors { left: parent.left; right: parent.right }
                label: qsTr("Password"); placeholderText: label; text: password
                inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase
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
    }

    onAccepted: create ? accountsModel.append(nameString.text, serverString.text, userString.text, passwordString.text, ignoreSSLErrorsSwitch.checked, type) : accountsModel.edit(nameString.text, serverString.text, userString.text, passwordString.text, ignoreSSLErrorsSwitch.checked, type, index)

}
