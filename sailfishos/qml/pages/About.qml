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
import de.huessenbergnetz.hbnsc 1.0
import harbour.framrekkari 1.0
import "../models"

AboutPage {
    appTitle: "Framrekkari"
    appDescription: qsTr("Online translation services client for Sailfish OS")
    appHomepage: "http://www.buschmann23.de/entwicklung/anwendungen/framrekkari"
    appCopyrightYearFrom: "2014"
    appCopyrightYearTo: "2019"
    appCopyrightHolder: "Matthias Fehring"
    appLicense: "GNU General Public License, Version 2"
    appLicenseFile: "GPLv2.qml"

    privacyPolicyQmlFile: Qt.resolvedUrl("../pages/PrivacyPolicy.qml")

    changelogModel: ChangelogModel {}
    bugTrackerBaseUrl: "https://github.com/Buschtrommel/Framrekkari/issues/"

    contributorsModel: ContributorsModel {}
    contributorsAvatarBasePath: "/usr/share/harbour-framrekkari/images/contributors"

    contactCompany: "Hüssenbergnetz"
    contactName: "Matthias Fehring"
    contactStreet: "Zum Südholz"
    contactHouseNo: "8"
    contactZIP: "34439"
    contactCity: "Willebadessen"
    contactCountry: qsTr("Germany")
    contactEmail: Qt.atob("a29udGFrdEBodWVzc2VuYmVyZ25ldHouZGU=")
    contactWebsite: "www.huessenbergnetz.de"
    contactWebsiteLink: "https://www.huessenbergnetz.de/?pk_campaign=Sailfish-App-Framrekkari&pk_kwd=AboutPage"

    paypalLabel: qsTr("Donate via PayPal")
    paypalEmail: Qt.atob("a29udGFrdEBidXNjaG1hbm4yMy5kZQ==")
    paypalOrganization: "Buschtrommel"
    paypalItem: "Framrekkari"
    paypalMessage: qsTr("Leave a message (English or German):")

    bugUrl: "https://github.com/Buschtrommel/Framrekkari/issues/"
    translateUrl: "https://www.transifex.com/projects/p/framrekkari/"

    licensesModel: LicensesModel {}
}
