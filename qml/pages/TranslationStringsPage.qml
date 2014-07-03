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
    id: translationStringsPage
    objectName: "StringList"

    property string accountName: framrekkari.accountName
    property int accountIndex: framrekkari.accountIndex
    property string accountUser: framrekkari.accountUser

    property string projectName
    property string projectSlug
    property string projectSrcLang
    property string lang
    property string langName
    property string resource

    property int projectLangIndex
    property int projectResourceIndex

    property string searchString
    property int searchTarget: 0

    property int filter: config.defaultFilter
    property string filterName: getFilterName()

    property bool inOperation: true

    function getFilterName()
    {
        switch(filter) {
        case 1:
            return qsTr("Untranslated");
        case 2:
            return qsTr("Not reviewed")
        case 3:
            return qsTr("Reviewed")
        case 0:
        default:
            return qsTr("All");
        }
    }

    Component.onCompleted: {
        framrekkari.currentResourceName = translationStringsPage.resource
        projectTranslationsModel.refresh(projectSlug, resource, lang, filter, accountIndex)
    }
    Component.onDestruction: { framrekkari.currentResourceName = ""; projectTranslationsModel.clear(); projectTranslationsModel.modelData = [] }

    Connections {
        target: projectTranslationsModel
        onSavedStringSuccess: {
            projectLangstatsModel.updateTranslationCount(translationStringsPage.projectLangIndex, changedData)
            projectResourceModel.updateTranslationCount(translationStringsPage.projectResourceIndex, translationStringsPage.accountUser, changedData)
        }
        onGotStrings: { translationStringsPage.inOperation = false }
        onGotError: {
            translationStringsPage.inOperation = false
            errorDisplay.text = qsTr("Ooops, the following error occured:") + " " + projectTranslationsModelErrorString
        }
    }

    Binding {
        target: projectTranslationsModel; property: "search"; value: searchString
    }

    Binding {
        target: projectTranslationsModel; property: "searchTarget"; value: searchTarget
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: translationStringsPage.inOperation
        visible: true
        size: BusyIndicatorSize.Large
    }

    Column {
        id: headerContainer
        width: translationStringsPage.width
        add: Transition { FadeAnimation {} }

        PageHeader { title: langName + ": " + resource }

        SearchField {
            id: searchField
            width: parent.width
            EnterKey.onClicked: searchField.focus = false
            EnterKey.iconSource: "image://theme/icon-m-enter-close"
            onTextChanged: searchTimer.restart()
        }

        Timer {
            id: searchTimer
            interval: 300
            repeat: false
            onTriggered: translationStringsPage.searchString = searchField.text
        }

        ComboBox {
            id: searchTargetBox
            label: qsTr("Search for")
            menu: ContextMenu {
                MenuItem { text: qsTr("Source string") }
                MenuItem { text: qsTr("Translation") }
            }
        }

        Binding {
            target: translationStringsPage; property: "searchTarget"; value: searchTargetBox.currentIndex
        }
    }

    SilicaListView {
        id: translationStringsList
        anchors.fill: parent
        currentIndex: -1

        PullDownMenu {
            MenuItem {
                text: qsTr("Refresh")
                onClicked: {
                    projectTranslationsModel.refresh(projectSlug, resource, lang, filter, accountIndex)
                    errorDisplay.enabled = false
                    translationStringsPage.inOperation = true
                }
            }
            MenuItem {
                text: qsTr("Filter:") + " " + filterName
                onClicked: {
                    var dialog = pageStack.push("../dialogs/ListFilterDialog.qml")
                    dialog.accepted.connect(function() {
                        if (translationStringsPage.filter !== dialog.filter) {
                            errorDisplay.enabled = false
                            translationStringsPage.inOperation = true
                            translationStringsPage.filter = dialog.filter
                            translationStringsPage.filterName = dialog.filterName
                            projectTranslationsModel.refresh(projectSlug, resource, lang, filter, accountIndex)
                        }
                    })
                }
            }
        }

        VerticalScrollDecorator {}

        header: Item {
            id: header
            width: headerContainer.width
            height: headerContainer.height
            Component.onCompleted: headerContainer.parent = header
        }

        model: projectTranslationsModel
        delegate: TranslationsDelegate {
            id: translationsDelegate
            searchString: translationStringsPage.searchString
            searchTarget: translationStringsPage.searchTarget
            project: translationStringsPage.projectSlug
            resource: translationStringsPage.resource
            lang: translationStringsPage.lang
            onClicked: {
                pageStack.push(Qt.resolvedUrl("StringPage.qml"), {projectSlug: projectSlug, resourceSlug: resource, langCode: lang, projectSrcLang: projectSrcLang, key: model.key, context: model.context, comment: model.comment, source: model.source, translation: model.translation, reviewed: model.reviewed, pluralized: model.pluralized, modelIdx: model.index, modelCount: translationStringsList.count, lastUpdate: model.lastUpdate, lastCommiter: model.user, tags: model.tags.join(", "), occurrences: model.occurrences, characterLimit: model.characterLimit, dataIdx: model.dataIndex})
            }
        }

        ViewPlaceholder {
            id: errorDisplay
            enabled: false
        }

        ViewPlaceholder {
            id: noContentDisplay
            enabled: !translationStringsPage.inOperation && translationStringsList.count === 0
            text: qsTr("Ooops, you got no results. Check your filter.")
        }
    }
}


