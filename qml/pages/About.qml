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
import "../BTComponents"
import "../models"

AboutPage {

    appTitle: "Framrekkari"
    appVersion: versionString
    appDescription: qsTr("The ownCloud News App client for Sailfish OS")
    appHomepage: "http://ocnews.buschmann23.de"
    appCover: "/usr/share/harbour-ocnews-reader/icons/ocNews-Sailfish-Cover.jpg"
    appCopyright: "© 2013-2014, Buschtrommel"
    appLicense: qsTr("Licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>")

    changelogModel: ChangelogModel {}
    bugTrackerBaseUrl: "https://github.com/Buschtrommel/ocNews/issues/"

    contributorsAvatarBasePath: "/usr/share/harbour-ocnews-reader/icons/contributors"
    contributorsModel: ContributorsModel {}

    privacyPolicyQmlFile: "../Dialogs/PrivacyPolicy.qml"

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
    paypalItem: "ocNews"
    paypalMessage: qsTr("Leave a message (English or German):")

    bugUrl: "https://github.com/Buschtrommel/ocNews/issues"
    translateUrl: "https://www.transifex.com/projects/p/ocnews/"

    licensesModel: ListModel {
        ListElement { text: QT_TR_NOOP("<a href='https://github.com/pycage/tidings'>RescalingRichtext</a> by Martin Grimme is licensed under the terms of the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>.") }
        ListElement { text: QT_TR_NOOP("<a href='https://bitbucket.org/razvanpetru/qslog/'>QsLog</a> by razvanpetru is licensed under the terms of the <a href='https://bitbucket.org/razvanpetru/qslog/src'>New BSD license</a>.") }
    }
}


//Page {
//    id: aboutPage

//    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
//    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

//    property int transifexAccountId: config.getTransifexAccount()

//    function openFramrakkatiProject()
//    {
//        if (transifexAccountId > -1)
//        {
//            framrekkari.accountIndex = transifexAccountId
//            pageStack.push(Qt.resolvedUrl("ProjectPage.qml"), {projectName: "Framrekkari", projectSlug: "framrekkari"})
//        } else {
//            Qt.openUrlExternally("https://www.transifex.com/projects/p/framrekkari/")
//        }
//    }

//    SilicaFlickable {
//        anchors.fill: parent

//        VerticalScrollDecorator {}

//        PullDownMenu {
//            MenuItem {
//                text: qsTr("Website")
//                onClicked: Qt.openUrlExternally("http://www.buschmann23.de/entwicklung/anwendungen/framrekkari")
//            }
//            MenuItem {
//                text: qsTr("Privacy Policy")
//                onClicked: pageStack.push(Qt.resolvedUrl("PrivacyPolicy.qml"))
//            }
//            MenuItem {
//                text: qsTr("Changelog")
//                onClicked: pageStack.push(Qt.resolvedUrl("../BTComponents/Changelog.qml"))
//            }
//            MenuItem {
//                text: qsTr("Contributors")
//                onClicked: pageStack.push(Qt.resolvedUrl("../BTComponents/Contributors.qml"), {avatarBasePath: "/usr/share/harbour-framrekkari/images/contributors", iconBasePath: "/usr/share/harbour-framrekkari/icons"})
//            }
//        }

//        contentHeight: imgCol.height + aboutCol.height + Theme.paddingLarge

//        Column {
//            id: imgCol
//            anchors { left: parent.left; right: parent.right }
//            PageHeader { title: qsTr("About") }

//            Image {
//                visible: true
//                width: parent.width
//                smooth: true
//                sourceSize.width: 540
//                sourceSize.height: 270
//                source: "/usr/share/harbour-framrekkari/images/store-cover.jpg"
//            }
//        }

//        Column {
//            id: aboutCol
//            anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; top: imgCol.bottom; topMargin: 10 }
//            spacing: 5

//            Label {
//                id: labelName
//                textFormat: Text.PlainText
//                text: "Framrekkari " + versionString
//                font.pixelSize: Theme.fontSizeLarge
//                color: Theme.highlightColor
//            }

//            Text {
//                id: description
//                text: qsTr("Online translation services client for Sailfish OS")
//                width: parent.width
//                wrapMode: Text.WordWrap
//                textFormat: Text.PlainText
//                color: Theme.secondaryHighlightColor
//            }

//            Text {
//                id: copyright
//                text: "© 2014, Buschtrommel"
//                width: parent.width
//                wrapMode: Text.WordWrap
//                textFormat: Text.PlainText
//                color: Theme.secondaryColor
//            }

//            SectionHeader  { text: qsTr("Licenses") }

//            Text {
//                id: codeLicense
//                text: _RICHTEXT_STYLESHEET_PREAMBLE + qsTr("Source code is licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>") + _RICHTEXT_STYLESHEET_APPENDIX
//                width: parent.width - Theme.paddingLarge
//                textFormat: Text.RichText
//                wrapMode: Text.WordWrap
//                color: Theme.secondaryColor
//                onLinkActivated: { Qt.openUrlExternally(link) }
//            }

//            SectionHeader { text: qsTr("Contribute") }

//            Row {
//                width: parent.width - Theme.paddingLarge

//                Button {
//                    width: parent.width/2
//                    text: qsTr("Translate")
//                    onClicked: openFramrakkatiProject()
//                }

//                Button {
//                    width: parent.width/2
//                    text: qsTr("Report bugs")
//                    onClicked: Qt.openUrlExternally("https://github.com/Buschtrommel/Framrekkari/issues")
//                }
//            }

//            PaypalChooser {
//                id: donation
//                anchors { left: parent.left; leftMargin: -Theme.paddingLarge; right: parent.right }
//                organization: "Buschtrommel"
//                item: "Framrekkari"
//                email: "kontakt@buschmann23.de"
//                message: qsTr("Leave a message (English or German):")
//            }

//            SectionHeader { text: qsTr("Contact") }

//            Text {
//                id: email
//                text: _RICHTEXT_STYLESHEET_PREAMBLE + "<a href='mailto:kontakt@buschmann23.de'>kontakt@buschmann23.de</a>" + _RICHTEXT_STYLESHEET_APPENDIX
//                color: Theme.primaryColor
//                font.pixelSize: Theme.fontSizeSmall
//                textFormat: Text.RichText
//                onLinkActivated: Qt.openUrlExternally(link)
//             }

//             Text {
//                id: website
//                text: _RICHTEXT_STYLESHEET_PREAMBLE + "<a href='http://www.buschmann23.de/entwicklung/anwendungen/framrekkari/'>www.buschmann23.de/.../framrekkari/</a>" + _RICHTEXT_STYLESHEET_APPENDIX
//                color: Theme.primaryColor
//                font.pixelSize: Theme.fontSizeSmall
//                textFormat: Text.RichText
//                onLinkActivated: Qt.openUrlExternally(link)
//            }
//        }
//    }
//}


