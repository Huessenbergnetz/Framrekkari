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
import "parts"

Page {
    id: about

    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

    SilicaFlickable {
        id: singleItem
        anchors.fill: parent
        contentHeight: contributorCol.height + Theme.paddingLarge
        VerticalScrollDecorator {}

        Column {
            id: contributorCol
            anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right }
            spacing: 10
            PageHeader { title: qsTr("Contributors") }

            SectionHeader { text: qsTr("Author") }

            ContributorItem {
                name: "Buschmann (Matthias Fehring)"
                role: qsTr("Main developer, Markat creator")
                image: "buschmann.png"
                website: "http://www.buschmann23.de"
                twitter: "buschmann23"
                github: "buschmann23"
            }

            SectionHeader { text: qsTr("Thanks to") }

            ContributorItem {
                name: "Jiri Grönroos (artnay)"
                role: qsTr("Finish translation")
            }
        }
    }
}
