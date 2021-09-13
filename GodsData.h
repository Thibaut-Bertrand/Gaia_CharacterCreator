/* Gaia_CharacterCreator is a free, open-source application that help players to
 * create their character for the tabletop role play game (ttrgp)
 * "Gaia - Le Dernier Mythe" ("Gaia - The Last Myth"). This game is not (yet?)
 * available to the public, but its author gives its approval for this
 * application.

 * Copyright (C) 2021
 * Author: Thibaut Bertrand
 * Contact: thbt.bertrand@gmail.com

 * =========================

 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.

 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.

 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <https://www.gnu.org/licenses/>.

 * =========================

 * Class description:
 * */

#ifndef GODSDATA_H
#define GODSDATA_H


#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QVector>


class GodsData
{

public:

    GodsData();

    // Merthods
    // ----------

    void printAllQualitiesInfo();


    // Members
    // ----------

    // --- Qualities

    struct Quality
    {
        // --- Information
        QString name = "";
        QString type = "";

        QString reference = "";
        int page = 0;

        QString description = "";
        QString effects = "";
        QString effectsShort = "";
        QString notes = "";


        // --- Modifications
        bool hasModification = true;

        bool changeAttribute = false;
        QMap<QString, int> attributesChange;

        bool addExpertise = false;
        QMap<QString, int> expertisesAdded;

        bool chooseExpertise = false;
        QVector<QString> expertiseToChoose;
        QVector<int> expertiseRankToChoose;

        bool addExpertisePoint = false;
        int expertisePointToAdd = 0;

        bool addPower = false;
        QMap<QString, int> powerToAdd;

        bool addPowerPoint = false;
        int powerPointAdded = 0;

        bool addMiasm = false;
        int miasmAdded = 0;

        bool addDevotees = false;
        int devoteesAdded = 0;

        bool addDestinyPoint = false;
        int destinyPointAdded = 0;
    };

    QVector<Quality*> qualityList;
    QVector<QString> qualityNameList;
    QVector<QString> benefitNameList;
    QVector<QString> tareNameList;


    // --- Gods

    struct God
    {
        QString name = "";
        QString description = "";
        QString origin = "";
        bool canBeFirstParent = true;
        QVector<QString> officalList;
        QVector<QString> bastardList;

        bool canBeMonoparental = false;
        bool isVirgin = false;

        QVector<Quality*> benefitList;
        QVector<Quality*> tareList;
    };

    QVector<God*> godList;
    QVector<QString> godNameList;


private:

    // Methods
    // ----------

    void readGodsJsonFile(QString filename);
    void readQualitiesJsonFile(QString filename);
};

#endif // GODSDATA_H
