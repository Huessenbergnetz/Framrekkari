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
    id: translationItem

    contentHeight: column.height + Theme.paddingMedium
    width: parent.width

//    menu: accountMenu

    ListView.onAdd: AddAnimation { target: translationItem }
    ListView.onRemove: RemoveAnimation { target: translationItem }

//    Image {
//        width: parent.width; height: Math.min(sourceSize.height, parent.contentHeight)
//        anchors { bottom: parent.bottom }
//        sourceSize.width: 480; sourceSize.height: 260
//        source: "image://theme/graphic-gradient-home-bottom"
//        source: "image://theme/graphic-gradient-edge"
//    }


    Column {
        id: column
        anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }

        Text {
            id: source
            width: parent.width
            text: model.source["1"]
            font.pixelSize: Theme.fontSizeSmall
            color: translationItem.highlighted ? Theme.highlightColor : Theme.primaryColor
            wrapMode: Text.WordWrap
            textFormat: Text.PlainText
        }

        Text {
            id: translation
            property bool translated: model.translation["1"] !== ""
            property color normalColor: translated ? Theme.secondaryColor : Theme.secondaryHighlightColor
            width: parent.width
            text: translated ? model.translation["1"] : qsTr("Not translated")
            font.pixelSize: Theme.fontSizeSmall
            color: translationItem.highlighted ? Theme.secondaryHighlightColor : normalColor
            wrapMode: Text.WordWrap
            textFormat: Text.PlainText
        }

    }
}
