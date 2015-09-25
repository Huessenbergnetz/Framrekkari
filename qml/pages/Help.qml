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

import QtQuick 2.2
import Sailfish.Silica 1.0


Page {
    id: helpPage

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height + Theme.paddingLarge

        VerticalScrollDecorator {}

        Column {
            id: column

            width: helpPage.width
            PageHeader {
                title: qsTr("Help")
            }

            SectionHeader { text: qsTr("General") }

            Text {
                id: general
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                textFormat: Text.StyledText
                text: qsTr("After the start of Framrekkari you will see the main view page that holds your accounts. This will be empty on the first start. Pull down the top menu and choose <i>Add account</i>, in order to add a new account. After you added one, it shows up in the list and you can click on it to open it. The account view gives you access to the service’s search/open functionality and lets you browse through the projects.<br><br>Search or browse for a project to open it. The project page shows the available languages and general information about the project. Clicking on a language will open the project resources. A click on a resource opens the list with the source strings. Click on a string to open it and start translating. Closing the single string page or going to the next or previous string automatically saves your input.")
            }

            SectionHeader { text: qsTr("Transifex API limitations") }

            Text {
                id: transifexLimitations
                anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                textFormat: Text.StyledText
                text: qsTr("Transifex API has some limitations. Biggest one is that it gives access information about languages and resources only to project owner and maintainers but not to normal users. So it is not possible to determine if a user has the rights to change content. You should now by yourself if you are resoponsible for a project language. If you have not enough rights to change something, you will get an error message, but it is not possible for Framrekkari to check this in advance.<br><br>The second big limitation is, that there is no search functionality. You have to enter the correct slug (project name that is used in the browser URL) to open a project directly, or you can browse through all available projects.")
            }
        }
    }
}


