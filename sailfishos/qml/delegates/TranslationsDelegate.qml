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

ListItem {
    id: translationItem

    property string project
    property string resource
    property string lang

    property string searchString
    property int searchTarget: 0

    property bool inOperation: false

    contentHeight: column.height + Theme.paddingMedium
    width: parent.width

    ListView.onAdd: AddAnimation { target: translationItem }
    ListView.onRemove: RemoveAnimation { target: translationItem }

    menu: transMenu

    Connections {
        target: projectTranslationsModel
        onSavedStringSuccess: inOperation = false
        onGotError: inOperation = false
    }

    Item {
        width: gi.width
        height: gi.height
        x: -(width / 2)
        y: 0

        GlassItem {
            id: gi
            width: Theme.itemSizeExtraSmall
            height: width
            color: Theme.highlightColor
            visible: model.reviewed
            opacity: visible ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad } }
        }

        BusyIndicator {
            size: BusyIndicatorSize.Small
            running: visible
            visible: inOperation
            anchors.centerIn: parent
            opacity: visible ? 1 : 0
            Behavior on opacity { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad } }
        }
    }

    Column {
        id: column
        anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin }

        Text {
            id: source
            width: parent.width
            text: translationItem.searchTarget === 0 ? Theme.highlightText(model.source["1"], translationItem.searchString, Theme.highlightColor) : model.source["1"]
            font.pixelSize: Theme.fontSizeSmall
            color: translationItem.highlighted ? Theme.highlightColor : Theme.primaryColor
            wrapMode: Text.WordWrap
            textFormat: Text.StyledText
        }

        Text {
            id: translation
            property bool translated: model.translation["1"] !== ""
            property color normalColor: translated ? Theme.secondaryColor : Theme.secondaryHighlightColor
            width: parent.width
            text: translated ? translationItem.searchTarget === 1 ? Theme.highlightText(model.translation["1"], translationItem.searchString, Theme.highlightColor) : model.translation["1"] : qsTr("Not translated")
            font.pixelSize: Theme.fontSizeSmall
            color: translationItem.highlighted ? Theme.secondaryHighlightColor : normalColor
            wrapMode: Text.WordWrap
            textFormat: Text.StyledText
        }

    }

    Component {
        id: transMenu
        ContextMenu {
            MenuItem {
                text: model.reviewed ? qsTr("Mark as not reviewed") : qsTr("Mark as reviewed")
                enabled: translation.translated
                onClicked: { inOperation = true; projectTranslationsModel.saveString(project, resource, lang, model.translation, md5Generator.genMd5(model.key, model.context), !model.reviewed, model.index, model.dataIndex, framrekkari.accountIndex) }
            }
        }
    }
}
