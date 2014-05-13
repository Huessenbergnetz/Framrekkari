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


Page {
    id: settingsPage

    Component.onDestruction: {
        config.set("display/sourceFontSize", sourceFontSize.value)
        config.set("display/translationFontSize", translationFontSize.value)
        config.set("display/stringListFilter", listFilter.currentIndex)
    }

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            width: settingsPage.width
            spacing: Theme.paddingLarge
            PageHeader { title: qsTr("Settings") }

            SectionHeader { text: qsTr("Behavior") }

            ComboBox {
                id: listFilter
                width: parent.width
                label: qsTr("Default list filter")

                menu: ContextMenu {
                    MenuItem { text: qsTr("All") }
                    MenuItem { text: qsTr("Untranslated") }
                    MenuItem { text: qsTr("Not reviewed") }
                    MenuItem { text: qsTr("Reviewed") }
                }
                currentIndex: config.get("display/stringListFilter", 0)
            }

            SectionHeader { text: qsTr("Font sizes") }

            Slider {
                id: sourceFontSize
                anchors { left: parent.left; right: parent.right }
                minimumValue: Theme.fontSizeTiny
                maximumValue: Theme.fontSizeHuge
                valueText: value + "px"
                stepSize: 1
                label: qsTr("Source text font size")
                value: config.get("display/sourceFontSize", Theme.fontSizeExtraSmall)
            }

            Slider {
                id: translationFontSize
                anchors { left: parent.left; right: parent.right }
                minimumValue: Theme.fontSizeTiny
                maximumValue: Theme.fontSizeHuge
                valueText: value + "px"
                stepSize: 1
                label: qsTr("Translation text font size")
                value: config.get("display/translationFontSize", Theme.fontSizeMedium)
            }
        }
    }
}


