import QtQuick 2.2
import Sailfish.Silica 1.0
import de.huessenbergnetz.btsc 1.0
import "../models"

AboutPage {
    appTitle: "Framrekkari"
    appDescription: qsTr("Online translation services client for Sailfish OS")
    appHomepage: "http://www.buschmann23.de/entwicklung/anwendungen/framrekkari"
    appCover: "/usr/share/harbour-framrekkari/images/store-cover.jpg"
    appCopyrightYear: "2014–2018"
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
    contactEmail: "kontakt@huessenbergnetz.de"
    contactWebsite: "www.huessenbergnetz.de"
    contactWebsiteLink: "https://www.huessenbergnetz.de"

    paypalLabel: qsTr("Donate via PayPal")
    paypalEmail: "kontakt@buschmann23.de"
    paypalOrganization: "Buschtrommel"
    paypalItem: "Framrekkari"
    paypalMessage: qsTr("Leave a message (English or German):")

    bugUrl: "https://github.com/Buschtrommel/Framrekkari/issues/"
    translateUrl: "https://www.transifex.com/projects/p/framrekkari/"

    licensesModel: LicensesModel {}
}
