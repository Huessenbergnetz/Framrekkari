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

ListItem {
    id: accountListItem

    contentHeight: row.height + Theme.paddingSmall
    width: parent.width

    menu: accountMenu

    ListView.onAdd: AddAnimation { target: accountListItem }
    ListView.onRemove: animateRemoval(accountListItem)

    onClicked: {
        framrekkari.accountName = model.name
        framrekkari.accountIndex = model.index
        framrekkari.accountUser = model.user
        framrekkari.accountType = model.type
        pageStack.push(Qt.resolvedUrl("../pages/AccountPage.qml"))
    }

    Row {
        id: row
        anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin }
        spacing: Theme.paddingMedium

        Image {
            id: icon
            width: Theme.iconSizeLarge; height: Theme.iconSizeLarge
            source: HELPER.getAccountIcon(model.type, "l") + "?" + nameLabel.color
            smooth: true
        }

        Column {
            id: column
            width: parent.width

            Label {
                id: nameLabel
                text: model.name
                width: parent.width
                color: accountListItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
                textFormat: Text.PlainText
            }

            Row {
                width: parent.width
                height: server.height
                spacing: Theme.paddingSmall

                Image {
                    id: serverIcon
                    source: "image://fram/icon-s-browser?" + serverText.color
                    width: serverText.font.pixelSize; height: width
                    smooth: true
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: serverText
                    text: model.server
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: accountListItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                    width: parent.width - parent.spacing - serverIcon.width
                    maximumLineCount: 1
                    elide: Text.ElideRight
                }
            }

            Row {
                width: parent.width
                height: server.height
                spacing: Theme.paddingSmall

                Image {
                    id: userIcon
                    source: "image://fram/icon-s-owner?" + userText.color
                    width: userText.font.pixelSize; height: width
                    smooth: true
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: userText
                    text: model.user
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: accountListItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                    width: parent.width - parent.spacing - serverIcon.width
                    maximumLineCount: 1
                    elide: Text.ElideRight
                }
            }
        }
    }

    Component {
        id: accountMenu
        ContextMenu {
            MenuItem {
                text: qsTr("Edit")
                onClicked: {
                    var dialog = pageStack.push("../dialogs/AccountDialog.qml", {name: nameLabel.text, server: serverText.text, user: userText.text, password: model.password, create: false, ignoreSSLErrors: model.ignoreSSLErrors, index: model.index, type: model.type})
                }
            }
            MenuItem {
                text: qsTr("Remove")
                onClicked: removeAccount(model.index, nameLabel.text)
            }
        }
    }

    function removeAccount(index, accName) {
        remorse.execute(accountListItem, qsTr("Removing account %1").arg(accName), function() { ListView.view.model.remove(index) } );
    }

    RemorseItem {
        id: remorse
    }
}
