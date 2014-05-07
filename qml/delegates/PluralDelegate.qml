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
import "../js/helper.js" as HELPER

ListItem {
    id: pluralItem

    property int count
    property int selectedIndex
    property string lang

    contentHeight: content.height + Theme.paddingLarge
    contentWidth: content.width + Theme.paddingLarge
    width: content.width + Theme.paddingLarge
    height: content.height + Theme.paddingLarge

    ListView.onAdd: AddAnimation { target: pluralItem }
    ListView.onRemove: RemoveAnimation { target: pluralItem }

    Label {
        id: content
//        text: (count === 2 && index === 0) ? qsTr("Singular") : (count === 2 && index > 0) ? qsTr("Plural") : model.plural
        text: HELPER.getPluralNames(count, index, plural, lang)
        anchors.centerIn: parent
        color: selectedIndex === model.index ? Theme.highlightColor : pluralItem.highlighted ? Theme.highlightColor : Theme.primaryColor
    }

}
