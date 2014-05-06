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

ListItem {
    id: projectsListItem

    contentHeight: column.height + Theme.paddingMedium
    width: parent.width

//    menu: accountMenu

    ListView.onAdd: AddAnimation { target: projectsListItem }
    ListView.onRemove: RemoveAnimation { target: projectsListItem }

    onClicked: {
        pageStack.push(Qt.resolvedUrl("../pages/ProjectPage.qml"), {projectName: model.name, projectSlug: model.slug})
    }


    Column {
        id: column
        anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }

        Label {
            id: nameLabel
            text: model.name
            width: parent.width
            color: projectsListItem.highlighted ? Theme.highlightColor : Theme.primaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            elide: Text.ElideRight
            textFormat: Text.PlainText
        }

        Text {
            id: sourceLangAndSlug
            text: qsTr("Source lang:") + " " + model.sourceLanguageCode + " " + qsTr("Slug:") + " " + model.slug
            font.pixelSize: Theme.fontSizeExtraSmall
            color: projectsListItem.highlighted ? Theme.highlightColor : Theme.primaryColor
            width: parent.width
            maximumLineCount: 1
            elide: Text.ElideRight
        }

        Text {
            id: description
            text: model.description
            font.pixelSize: Theme.fontSizeTiny
            color: projectsListItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }

//    Component {
//        id: accountMenu
//        ContextMenu {
//            MenuItem {
//                text: qsTr("Edit")
//                onClicked: {
//                    var dialog = pageStack.push("../dialogs/AccountDialog.qml", {name: nameLabel.text, server: serverText.text, user: userText.text, password: model.password, create: false, ignoreSSLErrors: model.ignoreSSLErrors})
//                }
//            }
//            MenuItem {
//                text: qsTr("Delete")
//                onClicked: removeAccount(model.index, nameLabel.text)
//            }
//        }
//    }

//    function removeAccount(index, accName) {
//        remorse.execute(projectsListItem, qsTr("Deleting account %1").arg(accName), function() { accountsModel.remove(index) } );
//    }

//    RemorseItem {
//        id: remorse
//    }
}
