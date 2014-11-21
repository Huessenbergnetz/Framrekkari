import QtQuick 2.0
import Sailfish.Silica 1.0
import "../BTComponents"
import "../models"

AboutPage {

    appTitle: "Framrekkari"
    appVersion: versionString
    appDescription: qsTr("Online translation services client for Sailfish OS")
    appHomepage: "http://www.buschmann23.de/entwicklung/anwendungen/framrekkari"
    appCover: "/usr/share/harbour-framrekkari/images/store-cover.jpg"
    appCopyright: "© 2014, Buschtrommel"
    appLicense: qsTr("Licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>")

    changelogModel: ChangelogModel {}
    bugTrackerBaseUrl: "https://github.com/Buschtrommel/Framrekkari/issues/"

    contributorsAvatarBasePath: "/usr/share/harbour-framrekkari/images/contributors"
    contributorsModel: ContributorsModel {}

    privacyPolicyQmlFile: "../pages/PrivacyPolicy.qml"

    contactCompany: "Buschtrommel"
    contactName: "Matthias Fehring"
    contactStreet: "Engelhardstraße"
    contactHouseNo: "32"
    contactZIP: "81369"
    contactCity: qsTr("Munich")
    contactCountry: qsTr("Germany")
    contactEmail: "kontakt@buschmann23.de"
    contactWebsite: "www.buschmann23.de"

    paypalLabel: qsTr("Donate via PayPal")
    paypalEmail: "kontakt@buschmann23.de"
    paypalOrganization: "Buschtrommel"
    paypalItem: "Framrekkari"
    paypalMessage: qsTr("Leave a message (English or German):")

    bugUrl: "https://github.com/Buschtrommel/Framrekkari/issues/"
    translateUrl: "https://www.transifex.com/projects/p/framrekkari/"

    licensesModel: ListModel {
    }
}
