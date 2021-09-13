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

#include "PowersData.h"


PowersData::PowersData()
{
    powerNameList.clear();

    readPowersJsonFile("C:/Users/thibo/Documents/Qt_Projects/Gaia_CharacterCreator/Resources/Data/Powers.json");

    // Uncheck this to print all power infos
//    printAllPowersInfo();
//    printAllPowersInfo(true);


    // Uncheck this to check powers info
//    checkPowersInfo();


    // Just to get the total price of everything at the same... Just 'cause.
//    int pts = 0;

//    for (Power* power : powerList)
//    {
//        pts += power->price;

//        for (Addon* extra : power->extraList)
//        {
//            pts += extra->price;
//        }

//        for (Addon* flaw : power->flawList)
//        {
//            pts += flaw->price;
//        }
//    }

//    qDebug() << "Total price:" << pts;
}


//     %%%%%%%%%%%%%%%%%%%%%%
//     %%% public METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%


/* Check if the present infos in the Power list are correct or not, like if the
 * indicated type, action... are correct or not. */
void PowersData::checkPowersInfo()
{
    QVector<QString> type = {"Contrôle", "Défense", "Général", "Mouvements",
                             "Offensif", "Sensoriel"};
    QVector<QString> action = {"Aucune", "Gratuite", "Mouvements",
                               "Réaction", "Standard", "Variable"};
    QVector<QString> range = {"Contact", "Distance", "Inconnue", "Perception",
                              "Personnelle", "Rang", "Variable"};
    QVector<QString> duration = {"Concentration", "Instantannée", "Permanent",
                                 "Soutenue", "Variable"};


    for (Power* power : powerList)
    {
        if (!type.contains(power->type))
        {
            qDebug() << "The Power" << power->name << "does not have a correct type!";
            qDebug() << "Type:" << power->type;
        }

        if (!action.contains(power->action))
        {
            qDebug() << "The Power" << power->name << "does not have a correct action!";
            qDebug() << "Action:" << power->action;
        }

        if (!range.contains(power->range))
        {
            qDebug() << "The Power" << power->name << "does not have a correct range!";
            qDebug() << "Range:" << power->range;
        }

        if (!duration.contains(power->duration))
        {
            qDebug() << "The Power" << power->name << "does not have a correct duration!";
            qDebug() << "Duration:" << power->duration;
        }
    }
}


int PowersData::getPowerIndex(QString powerName)
{
    return powerNameList.indexOf(powerName);
}


/* Print info extensive info about the Power List.
 * ----------
 * bool detail: false (default) to just print basic infos, and true to print
 * extensive infos. */
void PowersData::printAllPowersInfo(bool detail)
{
    // Just wanted to try another way to iterate through Vector of struct.

    for (Power* power : powerList)
    {
        qDebug() << "-----";
        qDebug() << "Name:" << power->name;
        qDebug() << "Price:" << power->price;
        qDebug() << "Reference:" << power->reference << ", page" << power->page;


        if (detail)
        {
            qDebug() << "Type:" << power->type;
            qDebug() << "Action:" << power->action;
            qDebug() << "Range:" << power->range;
            qDebug() << "Duration:" << power->duration;


            qDebug() << "\nExtras:";

            if (!power->extraList.isEmpty())
            {
                int i = 1;

                for (Addon* addon : power->extraList)
                {
                    qDebug() << "Name:" << addon->name;
                    qDebug() << "Type:" << addon->type;
                    qDebug() << "Description:" << addon->description;
                    qDebug() << "Effects" << addon->effects;
                    qDebug() << "Price:" << addon->price << ", Rank:" << addon->byRank << "\n";
                }
            }

            else
            {
                qDebug() << "This Power does not have any Extra.";
            }


            qDebug() << "\nFlaws:";

            if (!power->flawList.isEmpty())
            {
                int i = 1;

                for (Addon* addon : power->flawList)
                {
                    qDebug() << "Name:" << addon->name;
                    qDebug() << "Type:" << addon->type;
                    qDebug() << "Description:" << addon->description;
                    qDebug() << "Effects" << addon->effects;
                    qDebug() << "Price:" << addon->price << ", Rank:" << addon->byRank << "\n";
                }
            }

            else
            {
                qDebug() << "This Power does not have any Flaw.";
            }
        }


        qDebug() << "-----\n";
    }
}


//     %%%%%%%%%%%%%%%%%%%%%%%
//     %%% private METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%%


void PowersData::readPowersJsonFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray jsonData = file.readAll();

    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();

    QJsonValue powerValue = object.value("Powers");
    QJsonArray powerArray = powerValue.toArray();

    for (QJsonArray::iterator power = powerArray.begin(); power != powerArray.end(); power++)
    {
        Power* newPower = new Power;


        // --- Infos

        // Basic infos
        newPower->name = power->toObject().value("Name").toString();
        powerNameList.append(newPower->name);
        newPower->price = power->toObject().value("Price").toInt();


        // Detailled infos
        newPower->type = power->toObject().value("Type").toString();
        newPower->action = power->toObject().value("Action").toString();
        newPower->range = power->toObject().value("Range").toString();
        newPower->duration = power->toObject().value("Duration").toString();
        newPower->description = power->toObject().value("Description").toString();
        newPower->effects = power->toObject().value("Effects").toString();
        newPower->notes = power->toObject().value("Notes").toString();


        // --- Extras and Flaws

        // Extras
        QJsonValue extraValue = power->toObject().value("Extras");
        QJsonArray extraArray = extraValue.toArray();

        for (QJsonArray::iterator extra = extraArray.begin(); extra != extraArray.end(); extra++)
        {
            Addon* newAddon = new Addon;

            newAddon->name = extra->toObject().value("Name").toString();
            newAddon->type = extra->toObject().value("Type").toString();
            newAddon->description = extra->toObject().value("Description").toString();
            newAddon->effects = extra->toObject().value("Effects").toString();
            newAddon->notes = extra->toObject().value("Notes").toString();
            newAddon->price = extra->toObject().value("Price").toInt();
            newAddon->byRank = extra->toObject().value("Rank").toBool();

            newPower->extraList.append(newAddon);
        }


        // Flaws
        QJsonValue flawValue = power->toObject().value("Flaws");
        QJsonArray flawArray = flawValue.toArray();

        for (QJsonArray::iterator flaw = flawArray.begin(); flaw != flawArray.end(); flaw++)
        {
            Addon* newAddon = new Addon;

            newAddon->name = flaw->toObject().value("Name").toString();
            newAddon->type = flaw->toObject().value("Type").toString();
            newAddon->description = flaw->toObject().value("Description").toString();
            newAddon->effects = flaw->toObject().value("Effects").toString();
            newAddon->notes = flaw->toObject().value("Notes").toString();
            newAddon->price = flaw->toObject().value("Price").toInt();
            newAddon->byRank = flaw->toObject().value("Rank").toBool();

            newPower->flawList.append(newAddon);
        }


        powerList.append(newPower);
    }
}
