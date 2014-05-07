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

    property string projectName
    property string projectSlug
    property string projectSrcLang
    property string lang
    property string langName
    property string resource

    Component.onCompleted: projectTranslationsModel.refresh(projectSlug, resource, lang, accountIndex)
    Component.onDestruction: projectTranslationsModel.clear()

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: visible
        visible: translationStringsList.count === 0;
        size: BusyIndicatorSize.Large
    }

    SilicaListView {
        id: translationStringsList
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Refresh")
                onClicked: projectTranslationsModel.refresh(projectSlug, resource, lang, accountIndex)
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
    }
}


