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

CoverBackground {
    id: cover
    property int langOverall: coverConnector.langTranslated + coverConnector.langUntranslated
    property int resourceOverall: coverConnector.resourceTranslated + coverConnector.resourceUntranslated

    Image {
        source: "/usr/share/harbour-framrekkari/images/cover-background.png"
        x: 0; y: 0; z: -1
        opacity: 0.1
        width: parent.width
    }

    CoverPlaceholder {
        text: "Framrekkari"
        icon.source: "/usr/share/icons/hicolor/" + Theme.iconSizeLauncher + "x" + Theme.iconSizeLauncher + "/apps/harbour-framrekkari.png"
        visible: coverConnector.mode === "overview"
    }

    Column {
        id: generalInfo
        visible: coverConnector.mode !== "string" && coverConnector.mode !== "overview"
        anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge; top: parent.top; topMargin: Theme.paddingLarge }

        Label {
            width: parent.width
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            textFormat: Text.PlainText
            color: Theme.highlightColor
            text: coverConnector.project
            visible: coverConnector.mode === "project" || coverConnector.mode === "resources" || coverConnector.mode === "stringList"
        }

        Text {
            width: parent.width
            textFormat: Text.PlainText
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            visible: coverConnector.mode === "project"
            text: qsTr("%n language(s)", "", coverConnector.projectLangs)
        }

        Label {
            width: parent.width
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            textFormat: Text.PlainText
            color: Theme.highlightColor
            text: coverConnector.lang
            visible: coverConnector.mode === "resources" || coverConnector.mode === "stringList"
        }

        Label {
            width: parent.width
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            textFormat: Text.PlainText
            color: Theme.highlightColor
            text: coverConnector.resource
            visible: coverConnector.mode === "stringList"
        }
    }

    Column {
        id: stats
        visible: coverConnector.mode !== "string" && coverConnector.mode !== "overview"
        anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge; bottom: parent.bottom; bottomMargin: Theme.paddingLarge }

        Row {
            width: parent.width
            spacing: 0
            height: finished.height
            visible: coverConnector.mode === "resources" || coverConnector.mode === "stringList"

            Image {
                id: finishedIcon
                source: "image://theme/icon-s-edit?" + Theme.primaryColor
                width: finished.font.pixelSize; height: width;
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                id: finished
                text: coverConnector.mode === "resources" ? Number(Number((coverConnector.langTranslated/langOverall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%" :
                                                            Number(Number((coverConnector.resourceTranslated/langOverall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%"
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.primaryColor
                width: parent.width - finishedIcon.width
                horizontalAlignment: Text.AlignRight
            }
        }

        Row {
            width: parent.width
            spacing: 0
            height: reviewed.height
            visible: coverConnector.mode === "resources" || coverConnector.mode === "stringList"

            Image {
                id: reviewedIcon
                source: "image://fram/icon-s-watch?" + Theme.primaryColor
                width: reviewed.font.pixelSize; height: width;
                anchors.verticalCenter: parent.verticalCenter
            }

            Text {
                id: reviewed
                text: coverConnector.mode === "resources" ? Number(Number((coverConnector.langReviewed/langOverall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%" :
                                                            Number(Number((coverConnector.resourceReviewed/langOverall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%"
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.primaryColor
                width: parent.width - reviewedIcon.width
                horizontalAlignment: Text.AlignRight
            }
        }
    }

    Column {
        id: stringInfo
        visible: coverConnector.mode === "string" || coverConnector.mode === "meta"
        anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge; top: parent.top; topMargin: Theme.paddingSmall }

        Row {
            width: parent.width
            height: sourceLabel.height
            spacing: Theme.paddingSmall

            Label {
                id: sourceLabel
                width: parent.width - (2*Theme.fontSizeSmall + 2*parent.spacing)
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
                textFormat: Text.PlainText
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Source")
            }

            Image {
                source: "image://theme/icon-s-edit?" + Theme.primaryColor
                width: Theme.fontSizeSmall; height: width;
                anchors.verticalCenter: parent.verticalCenter
                visible: coverConnector.translated
            }

            Image {
                source: "image://fram/icon-s-watch?" + Theme.primaryColor
                width: Theme.fontSizeSmall; height: width;
                anchors.verticalCenter: parent.verticalCenter
                visible: coverConnector.reviewed
            }
        }

        Text {
            id: source
            text: coverConnector.source
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
            width: parent.width
            wrapMode: Text.WordWrap
            maximumLineCount: 7
            elide: Text.ElideRight
        }
    }

    CoverActionList {
        id: oneAction
        enabled: coverConnector.mode === "string" && !coverConnector.canGoNext

        CoverAction {
            iconSource: "image://theme/icon-s-clipboard"
            onTriggered: Clipboard.text = coverConnector.source
        }
    }

    CoverActionList {
        enabled: coverConnector.mode === "string" && coverConnector.canGoNext

        CoverAction {
            iconSource: "image://theme/icon-s-clipboard"
            onTriggered: Clipboard.text = coverConnector.source
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-next"
            onTriggered: pageStack.currentPage.nextPrevious(1)
        }
    }
}


