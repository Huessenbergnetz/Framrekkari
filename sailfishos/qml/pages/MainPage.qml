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

import "../delegates"
import "../common"
import "../models"


Page {
    id: mainPage

    FirstStartInfo {
        visible: config.get("system/version", 0) < versionInt
//        visible: true
        name: "Framrekkari"
        version: Qt.application.version
        helpPage: "../pages/Help.qml"
        donationHeader: qsTr("Donate")
        donationText: qsTr("If you like Framrekkari and you want to support the development, consider a small donation.")
        paypalOrganization: "Buschtrommel"
        paypalItem: "Framrekkari"
        paypalEmail: Qt.atob("a29udGFrdEBidXNjaG1hbm4yMy5kZQ==")
        paypalMessage: qsTr("Leave a message (English or German):")
        paypalLabel: qsTr("Donate via PayPal")
        description: qsTr("Framrekkari is a client for various collaborative online translation platforms, that currently supports the Transifex API.")
        changeLogModel: ChangelogModel {}
        changeLogTracker: "https://github.com/Buschtrommel/Framrekkari/issues/"
        onClicked: config.set("system/version", versionInt)
    }

    SilicaListView {
        id: accountsListView
        anchors.fill: parent

        header: PageHeader { title: "Framrekkari" }

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
            MenuItem {
                text: qsTr("Help")
                onClicked: pageStack.push(Qt.resolvedUrl("Help.qml"))
            }
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("Settings.qml"))
            }
            MenuItem {
                text: qsTr("Add account")
                onClicked: pageStack.push(Qt.resolvedUrl("../dialogs/AccountDialog.qml"))
            }
        }

        model: accountsModel
        delegate: AccountsDelegate {}

        VerticalScrollDecorator {}

        ViewPlaceholder {
            enabled: accountsListView.count == 0
            text: qsTr("Please add at least one account for a Transifex instance.")
        }
    }
}


