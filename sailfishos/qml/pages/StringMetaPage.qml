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


Page {
    id: stringMetaPage
    objectName: "MetaDataPage"

    property alias hash: hashText.text
    property alias comment: commentText.text
    property alias lastUpdate: lastUpdateText.text
    property alias lastCommiter: lastCommiterText.text
    property alias tags: tagsText.text
    property alias occurrences: occurrencesText.text
    property int characterLimit

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            width: stringMetaPage.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Metadata")
            }

            SectionHeader { text: qsTr("Tags"); visible: tagsText.visible }

            Text {
                id: tagsText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                visible: text !== ""
            }

            SectionHeader { text: qsTr("Comment"); visible: commentText.visible }

            Text {
                id: commentText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                visible: text !== ""
            }

            SectionHeader { text: qsTr("Occurences"); visible: occurrencesText.visible }

            Text {
                id: occurrencesText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                visible: text !== ""
            }

            SectionHeader { text: qsTr("Character limit"); visible: characterLimitText.visible }

            Text {
                id: characterLimitText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                visible: characterLimit > 0
                text: characterLimit
            }

            SectionHeader { text: qsTr("Last update"); visible: lastUpdateText.text !== "" }

            Text {
                id: lastUpdateText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            SectionHeader { text: qsTr("Last commiter"); visible: lastCommiterText.text !== "" }

            Text {
                id: lastCommiterText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            SectionHeader { text: qsTr("Hash") }

            Text {
                id: hashText
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }


        }
    }
}


