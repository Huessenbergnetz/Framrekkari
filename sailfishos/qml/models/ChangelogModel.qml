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

/*
  Types:
  0 - New
  1 - Improved/Enhanced
  2 - Fixed
  3 - Note
*/

import QtQuick 2.2

ListModel {
    ListElement {
        version: "1.1.6"
        date: 1443213797000
        entries: [
            ListElement { type: 1; issue: ""; description: "adopt to minor changes in Sailfish OS 1.1.9.28" },
            ListElement { type: 1; issue: ""; description: "translation updates" }
        ]
    }

    ListElement {
        version: "1.1.5"
        date: 1437130902000
        entries: [
            ListElement { type: 0; issue: ""; description: "Swedish, Norwegian Bokmal, Turkish, Russian, Chinese translations" },
            ListElement { type: 1; issue: ""; description: "translation updates" }
        ]
    }

    ListElement {
        version: "1.1.4"
        date: 1415835700000
        entries: [
            ListElement { type: 0; issue: ""; description: "Catalan, Czech and Dutch (Netherlands) translations" },
            ListElement { type: 1; issue: ""; description: "translation updates" }
        ]
    }

    ListElement {
        version: "1.1.3"
        date: 1404391433000
        entries: [
            ListElement { type: 0; issue: ""; description: "choose UI language in the settings" },
            ListElement { type: 0; issue: ""; description: "Spanish translation by pakoR" },
            ListElement { type: 0; issue: ""; description: "partly Frensh translation by Jean Clovis" }
        ]
    }

    ListElement {
        version: "1.1.2"
        date: 1401095958000
        entries: [
            ListElement { type: 0; issue: ""; description: "Danish translation by Peter Jespersen" },
            ListElement { type: 0; issue: ""; description: "Hungarian translation by László Kara" },
            ListElement { type: 0; issue: ""; description: "Polish translation by maurycy" },
            ListElement { type: 1; issue: ""; description: "data models, use QAbstractListModel instead of QAbstractTableModel" },
            ListElement { type: 2; issue: ""; description: "clear still visible word predictions after source string change" },
            ListElement { type: 2; issue: ""; description: "added missing scroll decorators" }
        ]
    }

    ListElement {
        version: "1.1.1"
        date: 1400160294000
        entries: [
            ListElement { type: 2; issue: ""; description: "crash on filtered lists, when using previous and next on string page" }
        ]
    }

    ListElement {
        version: "1.1.0"
        date: 1400151149000
        entries: [
            ListElement { type: 0; issue: ""; description: "information on cover and some cover actions (next string and copy to clipboard)" },
            ListElement { type: 0; issue: ""; description: "review operations on translation page and in string list context menu" },
            ListElement { type: 0; issue: ""; description: "metadata page attached to translation page" },
            ListElement { type: 0; issue: ""; description: "context menu on source string on translation page for clipboard operations" },
            ListElement { type: 1; issue: ""; description: "added hint to open transifex slug" },
            ListElement { type: 1; issue: ""; description: "better handling of empty string list results" },
            ListElement { type: 2; issue: "1"; description: "forgot to put settings column into a flickable" }
        ]
    }

    ListElement {
        version: "1.0.0"
        date: 1399895644000
        entries: [
            ListElement { type: 0; issue: ""; description: "initial release" }
        ]
    }
}
