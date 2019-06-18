/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014-2018  Hüssenbergnetz/Matthias Fehring
    https://github.com/Buschtrommel/Framrekkari

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
#include <QLocale>
#include <QTranslator>
#include <QStringBuilder>

#include "hbnsc.h"
#include "hbnsciconprovider.h"

#include "configuration.h"
#include "models/accountsmodel.h"
#include "models/projectsmodel.h"
#include "models/favoredprojectsmodel.h"
#include "models/projectlangstatsmodel.h"
#include "models/projectresourcesmodel.h"
#include "models/projecttranslationsmodel.h"
#include "models/languagesmodel.h"
#include "models/licensesmodel.h"
#include "api/projectsapi.h"
#include "md5generator.h"
#include "languagenamehelper.h"
#include <memory>

int main(int argc, char *argv[])
{
#ifndef CLAZY
    std::unique_ptr<QGuiApplication> app(SailfishApp::application(argc, argv));
#else
    auto app = std::make_unique<QGuiApplication>(argc, argv);
#endif

    app->setOrganizationName(QStringLiteral("harbour-framrekkari"));
    app->setOrganizationDomain(QStringLiteral("huessenbergnetz.de"));
    app->setApplicationName(QStringLiteral("harbour-framrekkari"));
    app->setApplicationDisplayName(QStringLiteral("Framrekkari"));
    app->setApplicationVersion(QStringLiteral(VERSION_STRING));

    qDebug("Starting %s %s.", qUtf8Printable(app->applicationDisplayName()), VERSION_STRING);

    Configuration *configuration = new Configuration(app.get());

    {
        const QString localeString = configuration->language();

        if (localeString != QLatin1String("C") && !localeString.isEmpty()) {
            QLocale::setDefault(QLocale(localeString));
            qDebug("Setting locale to %s.", qUtf8Printable(localeString));
        }

        if (Q_UNLIKELY(!Hbnsc::loadTranslations())) {
            qWarning("Failed to load HBNSC translations for locale %s.", qUtf8Printable(localeString));
        }

#ifndef CLAZY
        const QString l10nDir = SailfishApp::pathTo(QStringLiteral("translations")).toString(QUrl::RemoveScheme);
#else
        const QString l10nDir;
#endif
        auto translator = new QTranslator(app.get());
        if (Q_UNLIKELY(!translator->load(QLocale(), QStringLiteral("framrekkari"), QStringLiteral("_"), l10nDir, QStringLiteral(".qm")))) {
            qWarning("Failed to load app translations for locale %s.", qUtf8Printable(localeString));
        } else {
            if (Q_UNLIKELY(!app->installTranslator(translator))) {
                qWarning("Failed to load app translations for locale %s.", qUtf8Printable(localeString));
            }
        }
    }

    qmlRegisterType<LanguagesModel>("harbour.framrekkari", 1, 0, "LanguagesModel");
    qmlRegisterType<LicensesModel>("harbour.framrekkari", 1, 0, "LicensesModel");

#ifndef CLAZY
    std::unique_ptr<QQuickView> view(SailfishApp::createView());
#else
    auto view = std::make_unique<QQuickView>();
#endif

    auto hbnscIconProvider = Hbnsc::HbnscIconProvider::createProvider(view->engine());
    auto framIconProvider = Hbnsc::BaseIconProvider::createProvider({1.0, 1.25, 1.5, 1.75, 2.0}, QString(), false, QStringLiteral("fram"), view->engine());

    auto *accountsModel = new AccountsModel(app.get());
    auto *projectsModel = new ProjectsModel(app.get());
    auto *favoredProjectsModel = new FavoredProjectsModel(app.get());
    auto *projectsAPI = new ProjectsAPI(app.get());
    auto *projectLangstatsModel = new ProjectLangstatsModel(app.get());
    auto *projectResourceModel = new ProjectResourcesModel(app.get());
    auto *projectTranslationsModel = new ProjectTranslationsModel(app.get());
    auto *md5Generator = new MD5generator(app.get());
    auto *langHelper = new LanguageNameHelper(app.get());

    {
        const QVersionNumber version = QVersionNumber::fromString(QLatin1String(VERSION_STRING));
        view->rootContext()->setContextProperty(QStringLiteral("versionInt"), version.majorVersion() * 100 + version.minorVersion() * 10 + version.microVersion());
    }
    view->rootContext()->setContextProperty(QStringLiteral("config"), configuration);
    view->rootContext()->setContextProperty(QStringLiteral("accountsModel"), accountsModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectsModel"), projectsModel);
    view->rootContext()->setContextProperty(QStringLiteral("favoredProjectsModel"), favoredProjectsModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectsAPI"), projectsAPI);
    view->rootContext()->setContextProperty(QStringLiteral("projectLangstatsModel"), projectLangstatsModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectResourceModel"), projectResourceModel);
    view->rootContext()->setContextProperty(QStringLiteral("projectTranslationsModel"), projectTranslationsModel);
    view->rootContext()->setContextProperty(QStringLiteral("md5Generator"), md5Generator);
    view->rootContext()->setContextProperty(QStringLiteral("langHelper"), langHelper);
    view->rootContext()->setContextProperty(QStringLiteral("appLauncherIcon"), Hbnsc::getLauncherIcon({86, 108, 128, 150, 172}));

#ifndef CLAZY
    view->setSource(SailfishApp::pathToMainQml());
#endif

    view->showFullScreen();

    return app->exec();
}

