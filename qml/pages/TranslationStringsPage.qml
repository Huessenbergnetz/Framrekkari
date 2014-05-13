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

    property int filter: config.get("display/stringListFilter", 0)
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

    Component.onCompleted: projectTranslationsModel.refresh(projectSlug, resource, lang, filter, accountIndex)
    Component.onDestruction: projectTranslationsModel.clear()

    Connections {
        target: projectTranslationsModel
        onSavedStringSuccess: {
            projectLangstatsModel.updateTranslationCount(translationStringsPage.projectLangIndex)
            projectResourceModel.updateTranslationCount(translationStringsPage.projectResourceIndex, translationStringsPage.accountUser)
        }
        onGotStrings: { translationStringsPage.inOperation = false }
        onGotError: {
            translationStringsPage.inOperation = false
            errorDisplay.text = qsTr("Ooops, the following error occured:") + " " + projectTranslationsModelErrorString
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: translationStringsPage.inOperation
        visible: true
        size: BusyIndicatorSize.Large
    }

    SilicaListView {
        id: translationStringsList
        anchors.fill: parent

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

        header: PageHeader { title: langName + ": " + resource }

        model: projectTranslationsModel
        delegate: TranslationsDelegate {
            onClicked: {
                pageStack.push(Qt.resolvedUrl("StringPage.qml"), {projectSlug: projectSlug, resourceSlug: resource, langCode: lang, projectSrcLang: projectSrcLang, key: model.key, context: model.context, comment: model.comment, source: model.source, translation: model.translation, reviewed: model.reviewed, pluralized: model.pluralized, modelIdx: model.index, modelCount: translationStringsList.count})
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


