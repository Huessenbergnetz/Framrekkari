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
                text: model.name !== "" ? model.name : model.lang
                color: projectLangItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
                elide: Text.ElideRight
                textFormat: Text.PlainText
            }

            Text {
                id: langCode
                text: model.name !== "" ? model.lang : ""
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
                width: parent.width/4
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
                width: parent.width/4
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

            Text {
                id: untranslated
                width: parent.width/2
                text: qsTr("%n string(s) to translate", "", model.untranslated)
                font.pixelSize: Theme.fontSizeExtraSmall
                color: projectLangItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                maximumLineCount: 1
                elide: Text.ElideRight
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignRight
            }

        }

        ProgressBar {
            width: parent.width
            minimumValue: 0
            maximumValue: overall
            value: model.translated
//            label: qsTr("Finished:") + " " + Number(Number((model.translated/overall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%" + " - " + qsTr("Reviewed:") + " " + Number(Number((model.reviewed/overall)*100).toFixed(1)).toLocaleString(Qt.locale()) + "%"
        }



//        Text {
//            id: description
//            text: model.description
//            font.pixelSize: Theme.fontSizeTiny
//            color: projectLangItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
//            width: parent.width
//            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//        }
    }

//    Component {
//        id: accountMenu
//        ContextMenu {
//            MenuItem {
//                text: qsTr("Edit")
//                onClicked: {
//                    var dialog = pageStack.push("../dialogs/AccountDialog.qml", {name: nameLabel.text, server: serverText.text, user: userText.text, password: model.password, create: false, ignoreSSLErrors: model.ignoreSSLErrors})
//                }
//            }
//            MenuItem {
//                text: qsTr("Delete")
//                onClicked: removeAccount(model.index, nameLabel.text)
//            }
//        }
//    }

//    function removeAccount(index, accName) {
//        remorse.execute(projectLangItem, qsTr("Deleting account %1").arg(accName), function() { accountsModel.remove(index) } );
//    }

//    RemorseItem {
//        id: remorse
//    }
}
