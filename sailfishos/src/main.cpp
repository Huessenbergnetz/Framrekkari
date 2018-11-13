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
#include <silicatheme.h>
#include <silicascreen.h>
#endif
#include <QtQml>
#include <QGuiApplication>
#include <QQuickView>
#include <QScopedPointer>
#include <QLocale>
#include <QTranslator>
#include <QStringBuilder>
#include <btsciconprovider.h>

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
#include "framrekkariiconprovider.h"

int main(int argc, char *argv[])
{
#ifndef CLAZY
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
#else
    QScopedPointer<QGuiApplication> app(new QGuiApplication(argc, argv));
#endif

    app->setOrganizationName(QStringLiteral("harbour-framrekkari"));
    app->setOrganizationDomain(QStringLiteral("huessenbergnetz.de"));
    app->setApplicationName(QStringLiteral("harbour-framrekkari"));
    app->setApplicationDisplayName(QStringLiteral("Framrekkari"));
    app->setApplicationVersion(QStringLiteral(VERSION_STRING));

    qDebug("Starting %s %s.", qUtf8Printable(app->applicationDisplayName()), VERSION_STRING);

    Configuration *configuration = new Configuration(app.data());

    {
        QString locale = configuration->language();

        if (locale == QLatin1String("C")) {
            locale = QLocale::system().name();
        }

        qDebug("Setting locale to %s.", qUtf8Printable(locale));

        QLocale::setDefault(QLocale(locale));

        QTranslator *translator = new QTranslator(app.data());
#ifndef CLAZY
        if (translator->load(QStringLiteral("framrekkari_") % locale, SailfishApp::pathTo(QStringLiteral("translations")).toString(QUrl::RemoveScheme))) {
#else
        if (translator->load(QStringLiteral("framrekkari_") % locale, QStringLiteral("/usr/share/harbour-framrekkari/translations"))) {
#endif
            app->installTranslator(translator);
            qDebug("Successfully loaded app translation for locale %s.", qUtf8Printable(locale));
        } else {
            qWarning("Failed to load app translation for locale %s.", qUtf8Printable(locale));
        }

        QTranslator *btscTrans = new QTranslator(app.data());
#ifndef CLAZY
        if (btscTrans->load(QStringLiteral("btsc_") % locale, SailfishApp::pathTo(QStringLiteral("translations")).toString(QUrl::RemoveScheme))) {
#else
        if (btscTrans->load(QStringLiteral("framrekkari_") % locale, QStringLiteral("/usr/share/harbour-framrekkari/translations"))) {
#endif
            app->installTranslator(btscTrans);
            qDebug("Successfully loaded BTSC translation for locale %s.", qUtf8Printable(locale));
        } else {
            qWarning("Failed to load BTSC translation for locale %s.", qUtf8Printable(locale));
        }
    }

#ifndef CLAZY
    QScopedPointer<QQuickView> view(SailfishApp::createView());
#else
    QScopedPointer<QQuickView> view(new QQuickView());
#endif

    qreal pixelRatio = 1.0;
//    bool largeScreen = false;

#ifndef CLAZY
    {
        Silica::Theme theme;
//        Silica::Screen screen;
        pixelRatio = theme.pixelRatio();
//        largeScreen = screen.sizeCategory() >= Silica::Screen::Large;
    }
#endif

    QScopedPointer<BtscIconProvider> btscIconProvider(new BtscIconProvider({1.0, 1.25, 1.5, 1.75, 2.0}, pixelRatio));
    view->engine()->addImageProvider(QStringLiteral("btsc"), btscIconProvider.data());

#ifndef CLAZY
    QScopedPointer<FramrekkariIconProvider> framIconProvider(new FramrekkariIconProvider(SailfishApp::pathTo(QStringLiteral("icons")).toString(QUrl::RemoveScheme|QUrl::NormalizePathSegments|QUrl::StripTrailingSlash), pixelRatio));
#else
    QScopedPointer<FramrekkariIconProvider> framIconProvider(QStringLiteral("icons"), pixelRatio));
#endif
    view->engine()->addImageProvider(QStringLiteral("fram"), framIconProvider.data());

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
        view->rootContext()->setContextProperty(QStringLiteral("versionInt"), version.majorVersion() * 100 + version.minorVersion() * 10 + version.microVersion());
    }
    view->rootContext()->setContextProperty(QStringLiteral("versionString"), QStringLiteral(VERSION_STRING));
    view->rootContext()->setContextProperty(QStringLiteral("config"), configuration);
    view->rootContext()->setContextProperty(QStringLiteral("accountsModel"), accountsModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectsModel"), projectsModel);
    view->rootContext()->setContextProperty(QStringLiteral("favoredProjectsModel"), favoredProjectsModel);
    view->rootContext()->setContextProperty(QStringLiteral("languageModel"), languageModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectsAPI"), projectsAPI);
    view->rootContext()->setContextProperty(QStringLiteral("projectLangstatsModel"), projectLangstatsModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectResourceModel"), projectResourceModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectTranslationsModel"), projectTranslationsModel);
    view->rootContext()->setContextProperty(QStringLiteral("md5Generator"), md5Generator);
    view->rootContext()->setContextProperty(QStringLiteral("langHelper"), langHelper);

#ifndef CLAZY
    view->setSource(SailfishApp::pathToMainQml());
#endif

    view->show();

    return app->exec();
}

