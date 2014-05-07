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
import "../delegates"

Page {
    id: projectPage

    property string accountName: framrekkari.accountName
    property int accountIndex: framrekkari.accountIndex

    property string projectSlug
    property string resourceSlug
    property string langCode
    property string projectSrcLang

    property int modelIdx
    property int modelCount

    property bool canSave

    property string key
    property var context: []
    property string comment
    property var source
    property var translation
    property bool reviewed
    property bool pluralized
    property string hash: md5Generator.genMd5(key, context)

    property int pluralIndex: 0

    Component.onCompleted: {

            for (var propS in source)
                sourcesModel.append({"plural": propS, "string": source[propS]})

            sourceText.text = sourcesModel.get(0).string

            for (var propT in translation)
                translationsModel.append({"plural": propT, "string": translation[propT]})

            translationField.text = translationsModel.get(0).string

            canSave = checkCanSave()
    }

    function changePlural(idx)
    {
        pluralIndex = idx
        translationField.text = translationsModel.get(idx).string
    }

    function save()
    {
        var length = translationsModel.count

        for (var i = 0; i < length; ++i)
        {
            translation[translationsModel.get(i).plural] = translationsModel.get(i).string
        }

        projectTranslationsModel.saveString(projectSlug, resourceSlug, langCode, translation, hash, modelIdx, accountIndex)
    }

    function checkCanSave()
    {
        var length = translationsModel.cout
        var ret = true;

        for (var i = 0; i < length; ++i)
        {
            console.log(translationsModel.get(i).string)
            if (translationsModel.get(i).string === "")
                ret = false
        }

        return ret
    }

    ListModel {
        id: sourcesModel
    }

    ListModel {
        id: translationsModel
    }


    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height + pluralList.height + translationField.height + Theme.paddingLarge

        PullDownMenu {
            MenuItem {
                text: qsTr("Save")
                enabled: canSave
                onClicked: save()
            }
        }


        ViewPlaceholder {
            id: errorDisplay
            enabled: false
        }

        Column {
            id: column
            anchors { left: parent.left; right: parent.right }
            PageHeader { title: hash }

            Text {
                id: sourceText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge }
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }

        ListView {
            id: pluralList
            visible: pluralized
            orientation: ListView.Horizontal
            model: translationsModel
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingRight; top: column.bottom }
            height: Theme.itemSizeSmall
            delegate: PluralDelegate {
                count: translationsModel.count
                selectedIndex: pluralIndex
                lang: langCode
                onClicked: {
                    changePlural(model.index)
                }
            }
        }

        TextArea{
            id: translationField
            width: parent.width
            wrapMode: TextEdit.Wrap
            anchors.top: pluralized ? pluralList.bottom : column.bottom
            anchors.topMargin: pluralized ? 0 : 7
            onTextChanged: {
                translationsModel.get(pluralIndex).string = text
            }
        }
    }
}


