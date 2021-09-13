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

#ifndef CHARACTER_H
#define CHARACTER_H


#include <QMap>
#include <QString>
#include <QVector>


#include "GodsData.h"
#include "PowersData.h"


class Character
{

public:

    Character();


    struct Parent
    {
        GodsData::God* god;
        QVector<bool> benefits;
        QVector<bool> tares;

        bool isLegetimate = false;
    };


    // Methods
    // ----------

    void initializeStartingPowers();


    // Members
    // ----------
    // --- Character

    // Basic information
    QString player = "";
    QString name = "";

    QVector<QString> authorities = {""};

    QString gender = "";
    int height = 0;
    int weight = 0;
    int age = 0;

    QVector<QString> otherData = {""};


    // Ancestry
    Parent* firstParent = NULL;
    Parent* secondParent = NULL;

    bool hasSecondParent = false;
    bool isCreation = false;


    // Attributes
    struct attribute
    {
        QString name;
        int value = 0;
    };

    QVector<attribute> attributes;


    // Statistics
    int expActual = 0;
    int expTotal = 0;

    int run = 0;
    int swim = 0;
    int fly = 0;

    int destinyActual = 0;
    int destinyMax = 0;

    int devoteesActual = 0;
    int devoteesMax = 0;


    // Vitality
    int lifeActual = 0;
    int lifeMax = 0;
    int mortalityCountDown = 0;

    bool isDizzy = false; // Etourdi
    bool isStunned = false; // Assomé
    bool isIncapacitated = false; // Incapacité
    bool isDying = false; // Mourant

    bool isTired = false; // Fatigué
    bool isExhausted = false; // Crevé


    // Expertises


    // Powers
    QVector<PowersData::ConstructedPower*> powerList;
};

#endif // CHARACTER_H
