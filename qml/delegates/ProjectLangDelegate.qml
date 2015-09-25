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
    id: projectLangItem

    property double overall: model.translated + model.untranslated
    property string srcLang

    contentHeight: column.height + Theme.paddingMedium
    width: parent.width

//    menu: accountMenu

    ListView.onAdd: AddAnimation { target: projectLangItem }
    ListView.onRemove: RemoveAnimation { target: projectLangItem }


    Column {
        id: column
        width: parent.width

        Row {
            anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
            height: nameLabel.height
            spacing: 5

            Label {
                id: nameLabel
                text: langHelper.getLanguageName(model.lang)
                color: projectLangItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
                elide: Text.ElideRight
                textFormat: Text.PlainText
            }

            Text {
                id: langCode
                text: model.lang
                visible: text !== ""
                font.pixelSize: Theme.fontSizeExtraSmall
                color: projectLangItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                anchors.baseline: nameLabel.baseline
            }

            Text {
                id: sourceLanguage
                text: qsTr("(Source language)")
                visible: model.lang === srcLang
                font.pixelSize: Theme.fontSizeExtraSmall
                color: projectLangItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                anchors.baseline: nameLabel.baseline
            }
        }

        Row {
            anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }

            Row {
                width: parent.width/3
                spacing: 5
                height: finished.height

                Image {
                    id: finishedIcon
                    source: "image://theme/icon-s-edit"
                    width: finished.font.pixelSize; height: width;
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: finished
                    text: Number(Number((model.translated/overall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%"
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: projectLangItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                }
            }

            Row {
                width: parent.width/3
                spacing: 5
                height: reviewed.height

                Image {
                    id: reviewedIcon
                    source: "/usr/share/harbour-framrekkari/icons/icon-s-watch.png"
                    width: reviewed.font.pixelSize; height: width;
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: reviewed
                    text: Number(Number((model.reviewed/overall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%"
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: projectLangItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                }
            }

            Row {
                width: parent.width/3
                spacing: 5

                Image {
                    id: untranslatedIcon
                    source: "/usr/share/harbour-framrekkari/icons/icon-s-untranslated-strings.png"
                    width: reviewed.font.pixelSize; height: width;
                    anchors.verticalCenter: parent.verticalCenter
                }

                Label {
                    id: untranslated
                    width: parent.width - untranslatedIcon.width - parent.spacing
                    text: qsTr("%n string(s)", "", model.untranslated)
                    maximumLineCount: 1
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: projectLangItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                    truncationMode: TruncationMode.Fade
                }
            }
        }

        ProgressBar {
            width: parent.width
            minimumValue: 0
            maximumValue: overall
            value: model.translated
        }
    }
}
