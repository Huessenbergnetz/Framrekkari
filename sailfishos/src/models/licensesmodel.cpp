/*
    Framrekkari - Transifex Client for SailfishOS
    Copyright (C) 2014-2019  Hüssenbergnetz/Matthias Fehring
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

#include "licensesmodel.h"

LicensesModel::LicensesModel(QObject *parent) :
    Hbnsc::LicenseModel(parent)
{
    add(QStringLiteral("Framrekkari Translations"),
        QStringLiteral("Framrekkari Translators"),
        QString(),
        QUrl(QStringLiteral("https://www.transifex.com/huessenbergnetz/framrekkari/")),
        tr("The translations for Framrekkari are provided by the community. To see who is responsible for which translation, open the contributors page."),
        QStringLiteral("Creative Commons Attribution 4.0 International Public License"),
        QStringLiteral("CC-BY-4_0.qml"),
        QUrl(QStringLiteral("https://github.com/Huessenbergnetz/Framrekkari/blob/master/LICENSE.translations")),
        QUrl());

    sortLicenses();
}

LicensesModel::~LicensesModel()
{

}

#include "moc_licensesmodel.cpp"
