/****************************************************************************************
**
** Copyright (C) 2013 Jolla Ltd.
** Contact: Raine Makelainen <raine.makelainen@jollamobile.com>
** All rights reserved.
**
** This file is part of Sailfish Silica UI component package.
**
** You may use this file under the terms of BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the Jolla Ltd nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************************/

import QtQuick 2.0
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

    Behavior on height {
                NumberAnimation { duration: 250; easing.type: Easing.InOutQuad }
            }

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
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge; verticalCenter: parent.verticalCenter }
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
}
