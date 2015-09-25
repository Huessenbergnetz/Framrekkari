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

Page {
    id: about

    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

    SilicaFlickable {
        id: singleItem
        anchors.fill: parent
        contentHeight: aboutCol.height + Theme.paddingLarge
        VerticalScrollDecorator {}

        Column {
            id: aboutCol
            anchors { left: parent.left; right: parent.right }
            spacing: 5
            PageHeader { title: qsTr("Privacy policy") }


            Label {
                text: qsTr("What information does Framrekkari collect?")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                color: Theme.highlightColor
                wrapMode: Text.WordWrap
            }


            Text {
                id: text1
                text: qsTr("In order to login to your translation server Framrekkari needs your username and password as well as the server address. These information is not given to the author of Framrekkari or other third parties (except the server operator).")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                font.weight: Font.Light
            }

            Label {
                text: qsTr("What does Framrekkari use your information for?")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                color: Theme.highlightColor
                wrapMode: Text.WordWrap
            }

            Text {
                id: text2
                text: qsTr("Framrekkari needs your login data to connect to your translation server. Your log in data is used to log in to your translation server to perform the tasks of downloading and uploading translations.")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                font.weight: Font.Light
            }

            Label {
                text: qsTr("Does Framrekkari disclose any information to outside parties?")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                color: Theme.highlightColor
                wrapMode: Text.WordWrap
            }

            Text {
                id: text4
                text: qsTr("Framrekkari only uses your data for the login process into the server that you configured. Framrekkari does not send these data to the author of Framrekkari or other third parties. For questions concerning the privacy on the server side, you have to contact your translation service provider.")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                font.weight: Font.Light
            }

            Label {
                text: qsTr("Third party links")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                color: Theme.highlightColor
                wrapMode: Text.WordWrap
            }

            Text {
                id: text5
                text: qsTr("Framrekkari is a client for collaborated translations services like Transifex. It has no preinstalled third party links other than the own application website links on the About page and on this page. Showing translation project details and opening the project webistes is in the user's responsibility. For questions concerning the privacy of this sites you have to contact the site operator.")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                font.weight: Font.Light
            }

            Label {
                text: qsTr("Your consent")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                color: Theme.highlightColor
                wrapMode: Text.WordWrap
            }

            Text {
                id: text6
                text: qsTr("By using Framrekkari, you consent to this privacy policy.")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                font.weight: Font.Light
            }

            Label {
                text: qsTr("Contact")
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                color: Theme.highlightColor
                wrapMode: Text.WordWrap
            }

            Text {
                id: text7
                text: _RICHTEXT_STYLESHEET_PREAMBLE + "<a href='http://www.buschmann23.de/entwicklung/anwendungen/framrekkari'>http://www.buschmann23.de</a>" + _RICHTEXT_STYLESHEET_APPENDIX
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                font.weight: Font.Light
                onLinkActivated: { Qt.openUrlExternally(link) }
            }

            VerticalScrollDecorator {}

        }

    }
}
