/*
    BTComponents - QML components shared between various Buschtrommel projects
    Copyright (C) 2014-2018  Buschtrommel/Matthias Fehring
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

ListModel {
    id: licensesModel

    ListElement {
        name: "BT SFOS Components"
        author: "Matthias Fehring"
        version: "1.2.1"
        license: "Modified BSD License"
        licenseFile: "BSD-3.qml"
        website: "https://github.com/Buschtrommel/BT_SFOS_Components"
        description: "A set of QML components to use on Sailfish OS."
    }

    ListElement {
        name: "Framrekkari Translations"
        author: "Framrekkari Translators"
        license: "Creative Commons Attribution 4.0 International Public License"
        licenseFile: "CC-BY-4_0.qml"
        website: "https://www.transifex.com/buschtrommel/fuoten"
    }

    ListElement {
        name: "Qt"
        author: "The Qt Company"
        license: "GNU Lesser General Public License, Version 3"
        licenseFile: "LGPLv3.qml"
        website: "https://www.qt.io/"
    }

    ListElement {
        name: "libsailfishapp"
        author: "Jolla Ltd."
        license: "GNU Lesser General Public License, Version 2.1"
        licenseFile: "LGPLv2_1.qml"
        website: "https://sailfishos.org/develop/docs/libsailfishapp/"
    }

    ListElement {
        name: "libsailfishsilica"
        author: "Joll Ltd."
        license: "GNU Lesser General Public License, Version 2.1"
        licenseFile: "LGPLv2_1.qml"
        website: "https://sailfishos.org/develop/docs/silica"
    }

    ListElement {
        name: "Sailfish Silica UI"
        author: "Jolla Ltd."
        license: "Modified BSD License"
        licenseFile: "BSD-3.qml"
        website: "https://sailfishos.org/develop/docs/silica/"
    }
}
