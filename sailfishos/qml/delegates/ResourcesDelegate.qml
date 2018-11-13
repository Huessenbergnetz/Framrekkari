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
    id: projectResourceItem

    property double overall: model.translated + model.untranslated
    property color secColor: projectResourceItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor

    contentHeight: column.height + Theme.paddingMedium
    width: parent.width

    ListView.onAdd: AddAnimation { target: projectResourceItem }
    ListView.onRemove: RemoveAnimation { target: projectResourceItem }


    Column {
        id: column
        width: parent.width

        Row {
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }

            Column {
                width: parent.width * 0.6

                Label {
                    id: nameLabel
                    text: model.slug
                    color: projectResourceItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    elide: Text.ElideRight
                    textFormat: Text.PlainText
                    width: parent.width
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall
                    height: lastUpdate.height

                    Image {
                        id: timerIcon
                        source: "image://theme/icon-s-date?" + projectResourceItem.secColor
                        width: lastUpdate.font.pixelSize; height: width;
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: lastUpdate
                        text: Qt.formatDateTime(model.lastUpdate, qsTr("dd.MM.yy hh:mmAP"))
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: projectResourceItem.secColor
                    }
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall
                    height: commiter.height

                    Image {
                        id: commiterIcon
                        source: "image://fram/icon-s-owner?" + projectResourceItem.secColor
                        width: commiter.font.pixelSize; height: width;
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: commiter
                        text: model.lastCommiter
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: projectResourceItem.secColor
                    }
                }
            }

            Column {
                width: parent.width * 0.4
                anchors.bottom: parent.bottom

                Row {
                    id: untranslatedRow
                    width: parent.width
                    spacing: Theme.paddingSmall

                    Image {
                        id: untranslatedIcon
                        source: "image://fram/icon-s-untranslated-strings?" + projectResourceItem.secColor
                        width: untranslated.font.pixelSize; height: width;
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Label {
                        id: untranslated
                        width: parent.width - untranslatedIcon.width - parent.spacing
                        text: qsTr("%n string(s)", "", model.untranslated)
                        maximumLineCount: 1
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: projectResourceItem.secColor
                        truncationMode: TruncationMode.Fade
                    }
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall
                    height: finished.height

                    Image {
                        id: finishedIcon
                        source: "image://theme/icon-s-edit?" + projectResourceItem.secColor
                        width: finished.font.pixelSize; height: width;
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: finished
                        text: Number(Number((model.translated/overall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%"
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: projectResourceItem.secColor
                    }
                }

                Row {
                    width: parent.width
                    spacing: Theme.paddingSmall
                    height: reviewed.height

                    Image {
                        id: reviewedIcon
                        source: "image://fram/icon-s-watch?" + projectResourceItem.secColor
                        width: reviewed.font.pixelSize; height: width;
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: reviewed
                        text: Number(Number((model.reviewed/overall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%"
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: projectResourceItem.secColor
                    }
                }
            }
        }

        ProgressBar {
            width: parent.width
            height: Theme.itemSizeExtraSmall
            minimumValue: 0
            maximumValue: overall
            value: model.translated
        }
    }
}
