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

Item {
    id: root
    width: parent.width
    height: expanded ? header.height + text.paintedHeight : header.height

    property string version
    property real time
    property alias text: text.text
    property bool expanded: false

    BackgroundItem {
        id: header

        width: parent.width
        height: Theme.itemSizeSmall
        Row {
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge; verticalCenter: parent.verticalCenter }
            Label {
                anchors { verticalCenter: parent.verticalCenter }
                width: parent.width - icon.width
                text: qsTr("Version") + " " + version + " - " + Qt.formatDateTime(new Date(time), Qt.DefaultLocaleShortDate)
                color: parent.pressed ? Theme.highlightColor : Theme.primaryColor
                truncationMode: TruncationMode.Fade
                maximumLineCount: 1
            }
            Image {
                id: icon
                anchors { verticalCenter: parent.verticalCenter }
                width: 32; height: 32
                source: "image://theme/icon-m-left"
                state: expanded ? "expanded" : "unexpanded"
                states: [
                    State {
                        name: "expanded"
                        PropertyChanges { target: icon; rotation: 270 }
                    },
                    State {
                        name: "unexpanded"
                        PropertyChanges { target: icon; rotation: 0 }
                    }
                ]
                transitions: Transition { RotationAnimation {duration: 250; direction: icon.state === "expanded" ? RotationAnimation.Counterclockwise : RotationAnimation.Clockwise} }
            }
        }
        onClicked:expanded = !expanded
    }


    Text {
        id: text
        visible: expanded
        opacity: expanded ? 1 : 0
        clip: true
        anchors { left: parent.left; right: parent.right; rightMargin: Theme.paddingLarge; top: header.bottom }
        textFormat: Text.RichText
        color: Theme.primaryColor
        wrapMode: Text.WordWrap
        font.pixelSize: Theme.fontSizeSmall
        onLinkActivated: { Qt.openUrlExternally(link) }
        Behavior on opacity { NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad } }
    }
}
