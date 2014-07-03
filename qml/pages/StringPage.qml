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
import "../common"

Page {
    id: stringPage
    objectName: "StringPage"

    property string accountName: framrekkari.accountName
    property int accountIndex: framrekkari.accountIndex

    property string projectSlug
    property string resourceSlug
    property string langCode
    property string projectSrcLang

    property int modelIdx
    property int modelCount
    property int dataIdx

    property int nextPreviousDirection
    property bool canGoPrevious: modelIdx > 0
    property bool canGoNext: modelIdx < modelCount-1

    property string key
    property var context: []
    property string comment
    property var source
    property var translation
    property bool reviewed
    property bool pluralized
    property string hash: md5Generator.genMd5(key, context)
    property string lastUpdate
    property string lastCommiter
    property string tags
    property string occurrences
    property int characterLimit

    property int pluralIndex: 0

    Component.onCompleted: {
        populateModels()
        updateCover()
    }

    onStatusChanged: {
            if (status == PageStatus.Active) {
                pageStack.pushAttached(Qt.resolvedUrl("StringMetaPage.qml"), {hash: hash, comment: comment, lastUpdate: lastUpdate, lastCommiter: lastCommiter, tags: tags, occurrences: occurrences, characterLimit: characterLimit})

            }
        }

    Component.onDestruction: if (checkCanSave()) save()

    function updateCover()
    {
        coverConnector.source = sourcesModel.get(0).string
        coverConnector.reviewed = stringPage.reviewed
        coverConnector.translated = isTranslated()
        coverConnector.canGoNext = stringPage.canGoNext
    }

    function isTranslated()
    {
        var length = translationsModel.count

        for (var i = 0; i < length; i++)
        {
            if (translationsModel.get(i).string === "")
                return false
        }

        return true
    }

    function populateModels()
    {
        sourcesModel.clear()

        for (var propS in source)
            sourcesModel.append({"plural": propS, "string": source[propS]})

        if (sourcesModel.count > 0) {
            sourceText.text = sourcesModel.get(0).string
        } else {
            sourceText.text = ""
        }

        translationsModel.clear()
        oldTranslationsModel.clear()

        for (var propT in translation) {
            translationsModel.append({"plural": propT, "string": translation[propT]})
            oldTranslationsModel.append({"plural": propT, "string": translation[propT]})
        }

        if (translationsModel.count > 0) {
            translationField.text = translationsModel.get(0).string
        } else {
            translationField.text = ""
        }
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

        projectTranslationsModel.saveString(projectSlug, resourceSlug, langCode, translation, hash, reviewedSwitch.checked, modelIdx, dataIdx, accountIndex)
    }

    function checkCanSave()
    {
        var length = translationsModel.count

        for (var i = 0; i < length; i++)
        {
            if (translationsModel.get(i).string === "")
                return false
        }

        var ret = false

        for (var ii = 0; ii < length; ii++)
        {
            if(translationsModel.get(ii).string !== oldTranslationsModel.get(ii).string)
                ret = true
        }

        if (reviewed !== reviewedSwitch.checked)
            ret = true

        return ret
    }

    function nextPrevious(direction)
    {
        nextPreviousDirection = direction

        if (checkCanSave()) {
            pullDown.busy = true
            save()
        } else {
            getPreviousNext()
        }
    }

    function getPreviousNext()
    {
        pageStack.popAttached()

        switch(nextPreviousDirection)
        {
        case 0:
            modelIdx -= 1;
            break;
        case 1:
            modelIdx += 1;
            break;
        }


        Qt.inputMethod.commit()

        var item = projectTranslationsModel.get(modelIdx)
        key = item["key"]
        context = item["context"]
        comment = item["comment"]
        source = item["source"]
        translation = item["translation"]
        reviewed = item["reviewed"]
        reviewedSwitch.checked = reviewed
        pluralized = item["pluralized"]
        lastUpdate = item["last_update"]
        lastCommiter = item["user"]
        occurrences = item["occurences"]
        characterLimit = item["character_limit"]
        tags = item["tags"].join(", ")
        dataIdx = item["dataIndex"]
        pluralIndex = 0;

        populateModels()
        updateCover()

        pageStack.pushAttached(Qt.resolvedUrl("StringMetaPage.qml"), {hash: hash, comment: comment, lastUpdate: lastUpdate, lastCommiter: lastCommiter, tags: tags, occurrences: occurrences, characterLimit: characterLimit})
    }

    ListModel {
        id: sourcesModel
    }

    ListModel {
        id: translationsModel
    }

    ListModel {
        id: oldTranslationsModel
    }

    Connections {
        target: projectTranslationsModel
        onGotError: {
            pullDown.busy = false
            messageContainer.message = projectTranslationsModelErrorString
            messageContainer.messagetype = "error"
            messageContainer.show()
        }
        onSavedStringSuccess: {
            pullDown.busy = false
            getPreviousNext()
        }
    }

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height + pluralList.height + translationField.height + Theme.paddingLarge

        VerticalScrollDecorator {}

        PullDownMenu {
            id: pullDown
            MenuItem {
                text: qsTr("Previous")
                enabled: canGoPrevious
                onClicked: nextPrevious(0)
            }
        }

        PushUpMenu {
            MenuItem {
                text: qsTr("Next")
                enabled: canGoNext
                onClicked: nextPrevious(1)
            }
        }

        Column {
            id: column
            anchors { left: parent.left; right: parent.right }
            PageHeader { title: key }

            TextSwitch {
                id: reviewedSwitch
                text: qsTr("Reviewed")
                checked: stringPage.reviewed
                onClicked: coverConnector.reviewed = checked
            }

            MessageContainer {
                id: messageContainer
            }

            BackgroundItem {
                id: bgItem
                width: parent.width
                height: menuOpen ? sourceText.height + contextMenu.height : sourceText.height
                property Item contextMenu
                property bool menuOpen: contextMenu != null && contextMenu.parent === bgItem

                onPressAndHold: {
                    if (!contextMenu) contextMenu = contextMenuComp.createObject(root)
                    contextMenu.show(bgItem)
                }

                Text {
                    id: sourceText
                    anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge }
                    font.pixelSize: config.sourceFontSize
                    color: Theme.primaryColor
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    textFormat: Text.PlainText
                }
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
            font.pixelSize: config.translationFontSize
            anchors.top: pluralized ? pluralList.bottom : column.bottom
//            anchors.topMargin: pluralized ? 0 : 7
            onTextChanged: {
                translationsModel.get(pluralIndex).string = text
            }
        }
    }

    Component {
        id: contextMenuComp
        ContextMenu {
            MenuItem {
                text: qsTr("Copy to clipboard")
                onClicked: Clipboard.text = sourceText.text
            }
        }
    }
}


