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
import "../../common"

Row {
    spacing: 10
    width: parent.width

    property string image
    property alias name: contribName.text
    property alias role: contribRole.text
    property string website
    property string twitter
    property string github
    property string linkedin
    property string weibo
    property string bitbucket


    Image {
        id:contribImage
        source: image ? "/usr/share/harbour-framrekkari/images/contributors/" + image : "/usr/share/harbour-framrekkari/images/contributors/placeholder.png"
        sourceSize.height: 86
        sourceSize.width: 86
        width: 86
        height: 86
    }

    Column {
        spacing: 1
        width: parent.width - contribImage.width

        Label {
            id: contribName
            font.pixelSize: Theme.fontSizeSmall
            width: parent.width
            wrapMode: Text.WordWrap
        }

        Label {
            id: contribRole
            font.pixelSize: Theme.fontSizeExtraSmall
            width: parent.width
            wrapMode: Text.WordWrap
        }

        Row {
            id: imageLinks
            spacing: 10

            ImageButton {
                id: browserIcon
                source: "/usr/share/harbour-framrekkari/icons/icon-m-browser.png"
                sourceSize.height: 64
                sourceSize.width: 64
                width: 64
                height: 64
                visible: website ? true : false
                onClicked: Qt.openUrlExternally(website)
            }

            ImageButton {
                id: twitterIcon
                source: "/usr/share/harbour-framrekkari/icons/icon-m-twitter.png"
                sourceSize.height: 64
                sourceSize.width: 64
                height: 64
                width: 64
                visible: twitter ? true : false
                onClicked: Qt.openUrlExternally("https://twitter.com/" + twitter)
            }

            ImageButton {
                id: githubIcon
                source: "/usr/share/harbour-framrekkari/icons/icon-m-github.png"
                sourceSize.height: 64
                sourceSize.width: 64
                height: 64
                width: 64
                visible: github ? true : false
                onClicked: Qt.openUrlExternally("https://github.com/" + github)
            }

            ImageButton {
                id: bitbucketIcon
                source: "/usr/share/harbour-framrekkari/icons/icon-m-bitbucket.png"
                sourceSize.height: 64
                sourceSize.width: 64
                height: 64
                width: 64
                visible: bitbucket ? true : false
                onClicked: Qt.openUrlExternally("https://bitbucket.org/" + bitbucket)
            }

            ImageButton {
                id: linkedinIcon
                source: "/usr/share/harbour-framrekkari/icons/icon-m-linkedin.png"
                sourceSize.height: 64
                sourceSize.width: 64
                height: 64
                width: 64
                visible: linkedin ? true : false
                onClicked: Qt.openUrlExternally("http://www.linkedin.com/profile/view?id=" + linkedin)
            }

            ImageButton {
                id: weiboIcon
                source: "/usr/share/harbour-framrekkari/icons/icon-m-weibo.png"
                sourceSize.height: 64
                sourceSize.width: 64
                height: 64
                width: 64
                visible: weibo ? true : false
                onClicked: Qt.openUrlExternally("http://www.weibo.com/" + weibo)
            }
        }
    }
}

