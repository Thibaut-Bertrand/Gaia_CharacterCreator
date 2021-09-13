/* Gaia_CharacterCreator is a free, open-source application that help players to
 * create their character for the tabletop role play game (ttrgp) game
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

#ifndef POWERSDATA_H
#define POWERSDATA_H


#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QVector>


class PowersData
{

public:

    PowersData();


    // Methods
    // ----------

    void checkPowersInfo();
    int getPowerIndex(QString powerName);
    void printAllPowersInfo(bool detail = false);


    // Members
    // ----------

    // --- Powers

    typedef struct Addon
    {
        QString name = "";
        QString type = "";
        QString description = "";
        QString effects = "";
        QString notes = "";

        int price = 0;
        bool byRank = true;
    }Addon;

    struct Power
    {
        // --- Informations

        // Basic infos
        QString name = "";

        QString reference = "";
        int page = 0;

        int price = 0;


        // Basic infos
        QString type = "";
        QString action = "";
        QString range = "";
        QString duration = "";
        QString description = "";
        QString effects = "";
        QString notes = "";


        // --- Extras and Flaws
        QVector<Addon*> extraList;
        QVector<Addon*> flawList;
    };

    QVector<Power*> powerList;

    QVector<QString> powerNameList;


    struct CompositePower
    {
        Power* power;

        QVector<bool> extras;
        QVector<bool> flaws;

        int pricePerRank = 0;
    };


    struct ConstructedPower
    {
        QString powerName = "";
        QString notes = "";

        QVector<CompositePower*> compositePowers;
        QVector<QString> compositePowerNameList;

        int rank = 0;
        int nbOfFreeRank = 0;
        int pricePerRank = 0;
        int totalPrice = 0;
    };


private:

    // Methods
    // ----------

    void readPowersJsonFile(QString filename);
};

#endif // POWERSDATA_H
