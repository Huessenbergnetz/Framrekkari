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

BackgroundItem {
    id: root
    width: parent.width
    height: 0
    clip: true

    property string messagetype: "info"
    property bool shown: false
    property alias message: text.text
    property alias hide: hideTimer.interval

    onMessagetypeChanged: container.color = getColor()

    function getColor()
    {
        switch(messagetype)
        {
        case "success":
            return Theme.rgba("lime", 0.25)
        case "error":
            return Theme.rgba("red", 0.25)
        default:
        case "info":
            return Theme.rgba("powderblue", 0.25)
        }
    }

    function show()
    {
        root.height = container.height
    }

    function close()
    {
        root.height = 0
    }

    Behavior on height { NumberAnimation { duration: 250; easing.type: Easing.InOutQuad } }

    Timer {
        id: hideTimer
        interval: 5000
        running: root.height > 10
        onTriggered: root.close()
    }

    Rectangle {
        id: container
        width: parent.width
        height: text.height + Theme.paddingLarge
        color: getColor()

        Text {
            id: text
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin; verticalCenter: parent.verticalCenter }
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
}
