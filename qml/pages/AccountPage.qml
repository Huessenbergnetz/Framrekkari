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
import "../delegates"
import "../common"

Page {
    id: accountPage

    property string accountName: framrekkari.accountName
    property int accountIndex: framrekkari.accountIndex
    property int accountType: framrekkari.accountType

    property string openProjectName
    property string openProjectSlug

    Component.onCompleted: favoredProjectsModel.init(accountIndex)


    Connections {
        target: projectsAPI
        onGotProjectError: {
            searchBusy.visible = false
            errorLabel.text = gotProjectErrorString
            errorLabel.visible = true
        }
        onGotProject: {
            if (status === PageStatus.Active) {
                searchBusy.visible = false
                nameLabel.text = project["name"]
                projectItem.source_lang_code = project["source_language_code"]
                projectItem.slug = project["slug"]
                description.text = project["description"]
                projectItem.visible = true
            }
        }
    }


    Column {
        id: headerContainer

        move: Transition { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }
        add: Transition { FadeAnimation {} }

        width: accountPage.width
        spacing: Theme.paddingLarge
        PageHeader { title: accountName }

        OpenSlugField {
            id: searchField
            width: parent.width
            placeholderText: qsTr("Project slug")
            EnterKey.onClicked: { projectItem.visible = false; errorLabel.visible = false; searchBusy.visible = true; searchField.focus = false; projectsAPI.getProject(accountIndex, text, false) }
            EnterKey.iconSource: "image://theme/icon-m-home"
            onTextChanged: if (text === "") errorLabel.visible = false
        }

        Text {
            id: transifexHint
            font.pixelSize: Theme.fontSizeTiny
            color: projectItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: qsTr("You need to enter the exact and correct projekt slug (project name used in the browser URL).")
            visible: accountPage.accountType === 0
        }

        BusyIndicator {
            id: searchBusy
            visible: false
            running: visible
            size: BusyIndicatorSize.Medium
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            id: errorLabel
            anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
            visible: false
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            color: Theme.highlightColor
        }

        BackgroundItem {
            id: projectItem
            visible: false

            property string source_lang_code
            property string slug

            contentHeight: projectItemCol.height + Theme.paddingMedium
            width: parent.width
            height: contentHeight

            onClicked: {
                pageStack.push(Qt.resolvedUrl("ProjectPage.qml"), {projectName: nameLabel.text, projectSlug: projectItem.slug})
            }


            Column {
                id: projectItemCol
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }

                Label {
                    id: nameLabel
                    width: parent.width
                    color: projectItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    elide: Text.ElideRight
                    textFormat: Text.PlainText
                }

                Text {
                    id: sourceLangAndSlug
                    text: qsTr("Source lang:") + " " + projectItem.source_lang_code + " " + qsTr("Slug:") + " " + projectItem.slug
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: projectItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    width: parent.width
                    maximumLineCount: 1
                    elide: Text.ElideRight
                }

                Text {
                    id: description
                    font.pixelSize: Theme.fontSizeTiny
                    color: projectItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
            }
        }

        SectionHeader { text: qsTr("Favorites"); visible: languageListView.count > 0}
    }


    SilicaListView {
        id: languageListView
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Show all projects")
                onClicked: pageStack.push(Qt.resolvedUrl("ProjectsListPage.qml"))
            }
        }

        header: Item {
            id: header
            width: headerContainer.width
            height: headerContainer.height
            Component.onCompleted: headerContainer.parent = header
        }

        model: favoredProjectsModel
        delegate: ProjectsDelegate {}

        VerticalScrollDecorator {}
    }



//    SilicaFlickable {
//        anchors.fill: parent

//        contentHeight: column.height

//        PullDownMenu {
//            MenuItem {
//                text: qsTr("Show all projects")
//                onClicked: pageStack.push(Qt.resolvedUrl("ProjectsListPage.qml"))
//            }
//        }

//        Column {
//            id: column

//            move: Transition { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }
//            add: Transition { FadeAnimation {} }

//            width: accountPage.width
//            spacing: Theme.paddingLarge
//            PageHeader { title: accountName }

//            OpenSlugField {
//                id: searchField
//                width: parent.width
//                placeholderText: qsTr("Project slug")
//                EnterKey.onClicked: { projectItem.visible = false; errorLabel.visible = false; searchBusy.visible = true; searchField.focus = false; projectsAPI.getProject(accountIndex, text, false) }
//                EnterKey.iconSource: "image://theme/icon-m-home"
//                onTextChanged: if (text === "") errorLabel.visible = false
//            }

//            BusyIndicator {
//                id: searchBusy
//                visible: false
//                running: visible
//                size: BusyIndicatorSize.Medium
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            Label {
//                id: errorLabel
//                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
//                visible: false
//                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                color: Theme.highlightColor
//            }

//            BackgroundItem {
//                id: projectItem
//                visible: false

//                property string source_lang_code
//                property string slug

//                contentHeight: projectItemCol.height + Theme.paddingMedium
//                width: parent.width
//                height: contentHeight

//                onClicked: {
//                    pageStack.push(Qt.resolvedUrl("ProjectPage.qml"), {projectName: nameLabel.text, projectSlug: projectItem.slug})
//                }


//                Column {
//                    id: projectItemCol
//                    anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }

//                    Label {
//                        id: nameLabel
//                        width: parent.width
//                        color: projectItem.highlighted ? Theme.highlightColor : Theme.primaryColor
//                        maximumLineCount: 1
//                        truncationMode: TruncationMode.Fade
//                        elide: Text.ElideRight
//                        textFormat: Text.PlainText
//                    }

//                    Text {
//                        id: sourceLangAndSlug
//                        text: qsTr("Source lang:") + " " + projectItem.source_lang_code + " " + qsTr("Slug:") + " " + projectItem.slug
//                        font.pixelSize: Theme.fontSizeExtraSmall
//                        color: projectItem.highlighted ? Theme.highlightColor : Theme.primaryColor
//                        width: parent.width
//                        maximumLineCount: 1
//                        elide: Text.ElideRight
//                    }

//                    Text {
//                        id: description
//                        font.pixelSize: Theme.fontSizeTiny
//                        color: projectItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
//                        width: parent.width
//                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                    }
//                }
//            }

//            SectionHeader { text: qsTr("Favorites"); visible: favoritesList.count > 0}

//            ListView {
//                id: favoritesList
//                width: parent.width
//                height: childrenRect.height
//                model: favoredProjectsModel
//                delegate: ProjectsDelegate {}
//                interactive: false
//            }
//        }
//    }
}


