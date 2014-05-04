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

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "globals.h"


int main(int argc, char *argv[])
{
    QGuiApplication* app = SailfishApp::application(argc, argv);

        app->setOrganizationName("harbour-framrekkari");
        app->setOrganizationDomain("buschmann23.de");
        app->setApplicationName("harbour-framrekkari");
        app->setApplicationVersion(VERSION_STRING);

//        QDir().mkpath(QDir::homePath().append(DATA_DIR));


        QString locale = QLocale::system().name();
        QTranslator *translator = new QTranslator;
        if ((translator->load("framrekkari"+locale, "/usr/share/harbour-framrekkari/translations")))
            app->installTranslator(translator);

        QQuickView* view = SailfishApp::createView();

        view->rootContext()->setContextProperty("versionString", VERSION_STRING);

        view->setSource(QUrl::fromLocalFile("/usr/share/harbour-framrekkari/qml/harbour-framrekkari.qml"));
        view->show();

        return app->exec();
}

