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
    id: projectPage

    property string accountName: framrekkari.accountName
    property int accountIndex: framrekkari.accountIndex

    property string projectName
    property string projectSlug
    property string projectWebsite
    property string projectBugtracker
    property string projectTransInstractions
    property string projectDescription
    property string projectSrcLang

    property bool favored: favoredProjectsModel.isFavored(projectSlug, accountIndex)

    property bool inOperation: true

    Component.onCompleted: projectsAPI.getProject(accountIndex, projectSlug, true)


    Connections {
        target: projectsAPI
        onGotProjectError: {
            errorDisplay.text = qsTr("Ooops, the following error occured:") + " " + gotProjectErrorString
            errorDisplay.enabled = true
            inOperation = false
        }
        onGotProject: {
            projectWebsite = project["homepage"]
            projectBugtracker = project["bug_tracker"] ? project["bug_tracker"] : ""
            projectDescription = project["description"]
            description.text = project["long_description"] !== "" ? project["long_description"] : projectDescription
            owner.text = project["username"] ? project["username"] : ""
            tags.text = project["tags"]
            projectTransInstractions = project["trans_instructions"]
            projectSrcLang = project["source_language_code"]

            var maintainersArray = project["maintainers"]
            var maintainersLength = maintainersArray.length
            var newMaintainersArray = []
            for (var i = 0; i < maintainersLength; i++)
                newMaintainersArray.push(maintainersArray[i]["username"]);

            maintainers.text = newMaintainersArray.join(", ")

            inOperation = false
        }
    }


    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: visible
        visible: inOperation
        size: BusyIndicatorSize.Large
    }

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                text: qsTr("Bugtracker")
                enabled: projectBugtracker !== ""
                onClicked: Qt.openUrlExternally(projectBugtracker)
            }
            MenuItem {
                text: qsTr("Translation instructions")
                enabled: projectTransInstractions !== ""
                onClicked: Qt.openUrlExternally(projectTransInstractions)
            }
            MenuItem {
                text: qsTr("Project website")
                enabled: projectWebsite !== ""
                onClicked: Qt.openUrlExternally(projectWebsite)
            }
            MenuItem {
                text: favored ? qsTr("Remove from favorites") : qsTr("Add to favorites")
                enabled: !inOperation && !errorDisplay.enabled
                onClicked: {
                    if (favored) {
                        favoredProjectsModel.remove(projectSlug, accountIndex)
                    } else {
                        favoredProjectsModel.append(projectName, projectSlug, projectDescription, projectSrcLang, accountIndex)
                    }
                    favored = !favored
                }
            }
        }

        ViewPlaceholder {
            id: errorDisplay
            enabled: false
        }

        Column {
            id: column
            visible: !inOperation && !errorDisplay.enabled

            move: Transition { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }
            add: Transition { FadeAnimation {} }

            width: projectPage.width
            spacing: Theme.paddingLarge
            PageHeader { title: projectName }

            Text {
                id: description
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WordWrap
            }

            Row {
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                height: tags.height
                visible: tags.text !== ""
                spacing: 5

                Image {
                    id: tagIcon
                    source: "/usr/share/harbour-framrekkari/icons/icon-s-tag.png"
                    anchors { top: parent.top; topMargin: 7 }
                    width: tags.font.pixelSize; height: width
                }

                Text {
                    id: tags
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                    wrapMode: Text.WordWrap
                    width: parent.width - tagIcon.width - parent.spacing
                }
            }

            Row {
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                height: owner.height
                visible: owner.text !== ""
                spacing: 5

                Image {
                    id: ownerIcon
                    source: "image://theme/icon-s-task"
                    sourceSize.width: 32; sourceSize.height: 32
                    anchors { top: parent.top; topMargin: 7 }
                    width: tags.font.pixelSize; height: width
                    smooth: true
                }

                Text {
                    id: owner
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                    wrapMode: Text.WordWrap
                    width: parent.width - ownerIcon.width - parent.spacing
                }
            }

            Row {
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                height: maintainers.height
                visible: maintainers.text !== ""
                spacing: 5

                Image {
                    id: maintainerIcon
                    source: "image://theme/icon-m-person"
                    sourceSize.width: 64; sourceSize.height: 64
                    anchors { top: parent.top; topMargin: 7 }
                    width: tags.font.pixelSize; height: width
                    smooth: true
                }

                Text {
                    id: maintainers
                    font.pixelSize: Theme.fontSizeSmall
                    color: Theme.secondaryColor
                    wrapMode: Text.WordWrap
                    width: parent.width - maintainerIcon.width - parent.spacing
                }
            }
        }
    }
}


