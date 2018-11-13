/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014-2018  Hüssenbergnetz/Matthias Fehring
    https://github.com/Buschtrommel/Framrekkari

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
import "pages"

ApplicationWindow
{
    id: framrekkari

    property string accountName
    property int accountIndex
    property string accountUser
    property int accountType
    property string currentProjectName
    property string currentResourceName
    property string currentLangName

    function getCoverMode()
    {
        switch(pageStack.currentPage.objectName) {
            case "MetaDataPage":
                return "meta";
            case "StringPage":
                return "string";
            case "ProjectView":
                return "project";
            case "ResourceView":
                return "resources"
            case "StringList":
                return "stringList"
            default:
                return "overview"
        }
    }

    initialPage: Component { MainPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")

    QtObject {
        id: coverConnector
        property string project: framrekkari.currentProjectName
        property string resource: framrekkari.currentResourceName
        property string lang: framrekkari.currentLangName
        property int projectLangs
        property string source
        property bool translated
        property bool reviewed
        property bool canGoNext
        property int langTranslated
        property int langUntranslated
        property int langReviewed
        property int resourceTranslated
        property int resourceUntranslated
        property int resourceReviewed
        property string mode: "overview"
    }

    Connections {
        target: pageStack
        onCurrentPageChanged: coverConnector.mode = getCoverMode()
    }

    Connections {
        target: projectResourceModel
        onResourceStatsChanged: {
            coverConnector.resourceTranslated = changedResourceStats["translated"]
            coverConnector.resourceUntranslated = changedResourceStats["untranslated"]
            coverConnector.resourceReviewed = changedResourceStats["reviewed"]
        }
    }

    Connections {
        target: projectLangstatsModel
        onLangStatsChanged: {
            coverConnector.langTranslated = changedLangStats["translated"]
            coverConnector.langUntranslated = changedLangStats["untranslated"]
            coverConnector.langReviewed = changedLangStats["reviewed"]
        }
    }
}


