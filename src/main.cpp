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

#ifndef CLAZY
#include <sailfishapp.h>
#endif
#include <QtQml>
#include <QGuiApplication>
#include <QQuickView>
#include <QScopedPointer>
#include <QLocale>
#include <QTranslator>
#include <QStringBuilder>

#include "configuration.h"
#include "models/accountsmodel.h"
#include "models/projectsmodel.h"
#include "models/favoredprojectsmodel.h"
#include "models/projectlangstatsmodel.h"
#include "models/projectresourcesmodel.h"
#include "models/projecttranslationsmodel.h"
#include "models/languagemodelfilter.h"
#include "api/projectsapi.h"
#include "md5generator.h"
#include "languagenamehelper.h"

int main(int argc, char *argv[])
{
#ifndef CLAZY
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
#else
    QScopedPointer<QGuiApplication> app(new QGuiApplication(argc, argv));
#endif

    app->setOrganizationName("harbour-framrekkari");
    app->setOrganizationDomain("buschmann23.de");
    app->setApplicationName("harbour-framrekkari");
    app->setApplicationDisplayName(QStringLiteral("Framrekkari"));
    app->setApplicationVersion(VERSION_STRING);

    qDebug("Starting %s %s.", qUtf8Printable(app->applicationDisplayName()), qUtf8Printable(VERSION_STRING));

    Configuration *configuration = new Configuration(app.data());

    {
        QString locale = configuration->language();

        if (locale == QLatin1String("C")) {
            locale = QLocale::system().name();
        }

        QTranslator *translator = new QTranslator(app.data());
        if ((translator->load(QStringLiteral("framrekkari_") % locale, SailfishApp::pathTo(QStringLiteral("translations")).toString(QUrl::RemoveScheme)))) {
            app->installTranslator(translator);
            qDebug("Successfully loaded translation for locale %s.", qUtf8Printable(locale));
        } else {
            qWarning("Failed to load translation for locale %s.", qUtf8Printable(locale));
        }
    }

#ifndef CLAZY
    QScopedPointer<QQuickView> view(SailfishApp::createView());
#else
    QScopedPointer<QQuickView> view(new QQuickView());
#endif

    auto *accountsModel = new AccountsModel(app.data());
    auto *projectsModel = new ProjectsModel(app.data());
    auto *favoredProjectsModel = new FavoredProjectsModel(app.data());
    auto *projectsAPI = new ProjectsAPI(app.data());
    auto *projectLangstatsModel = new ProjectLangstatsModel(app.data());
    auto *projectResourceModel = new ProjectResourcesModel(app.data());
    auto *projectTranslationsModel = new ProjectTranslationsModel(app.data());
    auto *md5Generator = new MD5generator(app.data());
    auto *langHelper = new LanguageNameHelper(app.data());
    auto *languageModel = new LanguageModelFilter(app.data());

    {
        const QVersionNumber version = QVersionNumber::fromString(QLatin1String(VERSION_STRING));
        view->rootContext()->setContextProperty("versionInt", version.majorVersion() * 100 + version.minorVersion() * 10 + version.microVersion());

    }
    view->rootContext()->setContextProperty("versionString", VERSION_STRING);
    view->rootContext()->setContextProperty("config", configuration);
    view->rootContext()->setContextProperty("accountsModel", accountsModel);
    view->rootContext()->setContextProperty("projectsModel", projectsModel);
    view->rootContext()->setContextProperty("favoredProjectsModel", favoredProjectsModel);
    view->rootContext()->setContextProperty("languageModel", languageModel);
    view->rootContext()->setContextProperty("projectsAPI", projectsAPI);
    view->rootContext()->setContextProperty("projectLangstatsModel", projectLangstatsModel);
    view->rootContext()->setContextProperty("projectResourceModel", projectResourceModel);
    view->rootContext()->setContextProperty("projectTranslationsModel", projectTranslationsModel);
    view->rootContext()->setContextProperty("md5Generator", md5Generator);
    view->rootContext()->setContextProperty("langHelper", langHelper);

#ifndef CLAZY
    view->setSource(SailfishApp::pathToMainQml());
#endif

    view->show();

    return app->exec();
}

