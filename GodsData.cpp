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

#include "GodsData.h"


/* Constructor */
GodsData::GodsData()
{
    readQualitiesJsonFile("C:/Users/thibo/Documents/Qt_Projects/Gaia_CharacterCreator/Resources/Data/Qualities.json");
    readGodsJsonFile("C:/Users/thibo/Documents/Qt_Projects/Gaia_CharacterCreator/Resources/Data/Gods.json");

    // Uncomment to print all qualities and check them by eye
//    printAllQualitiesInfo();
}


//     %%%%%%%%%%%%%%%%%%%%%%
//     %%% public METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%


void GodsData::printAllQualitiesInfo()
{
    foreach (const Quality* quality, qualityList)
    {
        qDebug() << "-----";
        qDebug() << "Name: " << quality->name;
        qDebug() << "Type: " << quality->type;

        qDebug() << "Description: " << quality->description;
        qDebug() << "Effects: " << quality->effects;
        qDebug() << "Notes: " << quality->notes;

        if (quality->hasModification)
        {
            qDebug() << "Modification(s):";

            if (quality->changeAttribute)
            {
                qDebug() << "- Add attributes:";
                qDebug() << quality->attributesChange;
            }

            if(quality->addExpertise)
            {
                qDebug() << "- Add expertises:";
                qDebug() << quality->expertisesAdded;
            }

            if(quality->chooseExpertise)
            {
                qDebug() << "- Choose expertises:";
                qDebug() << quality->expertiseToChoose;
                qDebug() << quality->expertiseRankToChoose;
            }

            if(quality->addExpertisePoint)
            {
                qDebug() << "- Add expertise points:";
                qDebug() << quality->expertisePointToAdd;
            }

            if(quality->addPower)
            {
                qDebug() << "- Add powers:";
                qDebug() << quality->powerToAdd;
            }

            if(quality->addPowerPoint)
            {
                qDebug() << "- Add power points:";
                qDebug() << quality->powerPointAdded;
            }

            if(quality->addMiasm)
            {
                qDebug() << "- Add miasm:";
                qDebug() << quality->miasmAdded;
            }

            if(quality->addDevotees)
            {
                qDebug() << "- Add devotees:";
                qDebug() << quality->devoteesAdded;
            }

            if(quality->addDestinyPoint)
            {
                qDebug() << "- Add destiny points:";
                qDebug() << quality->destinyPointAdded;
            }
        }

        else
        {
            qDebug() << "This Quality does not have a (coded) modification.";
        }

        qDebug() << "-----\n";
    }
}


//     %%%%%%%%%%%%%%%%%%%%%%%
//     %%% private METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%%


/* Read the provided .json file and populate a "God" struct for each of them.
 * ----------
 * QString filename: the file path of the .json file to read. */
void GodsData::readGodsJsonFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray jsonData = file.readAll();

    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();

    QJsonValue godValue = object.value("Gods");
    QJsonArray godArray = godValue.toArray();

    foreach (const QJsonValue & god, godArray)
    {
        God* newGod = new God;

        newGod->name = god.toObject().value("Name").toString();
        newGod->description = god.toObject().value("Description").toString();
        newGod->origin = god.toObject().value("Origin").toString();
        newGod->canBeFirstParent = god.toObject().value("FirstParent").toBool();


        QJsonValue officialValue = god.toObject().value("Official");
        QJsonArray officialArray = officialValue.toArray();

        foreach (const QJsonValue & official, officialArray)
        {
            QString newOfficial;
            newOfficial = official.toString();

            newGod->officalList.append(newOfficial);
        }


        QJsonValue bastardValue = god.toObject().value("Bastard");
        QJsonArray bastardArray = bastardValue.toArray();

        foreach (const QJsonValue & bastard, bastardArray)
        {
            QString newBastard;
            newBastard = bastard.toString();

            newGod->bastardList.append(newBastard);
        }


        newGod->canBeMonoparental = god.toObject().value("Monoparental").toBool();
        newGod->isVirgin = god.toObject().value("Virgin").toBool();


        QJsonValue benefitValue = god.toObject().value("Benefits");
        QJsonArray benefitArray = benefitValue.toArray();

        foreach (const QJsonValue & benefit, benefitArray)
        {
//            QString newbenefit;
//            newbenefit = benefit.toString();

//            newGod.benefitList.append(newbenefit);

            int benefitIndex = qualityNameList.indexOf(benefit.toString());
            newGod->benefitList.append(qualityList[benefitIndex]);
        }


        QJsonValue tareValue = god.toObject().value("Tares");
        QJsonArray tareArray = tareValue.toArray();

        foreach (const QJsonValue & tare, tareArray)
        {
//            QString newTare;
//            newTare = tare.toString();

//            newGod.tareList.append(newTare);

            int tareIndex = qualityNameList.indexOf(tare.toString());
            newGod->tareList.append(qualityList[tareIndex]);
        }


        godList.append(newGod);
        godNameList.append(newGod->name);
    }
}
/* Read the provided .json file and populate a "Benefit" struct for each of
 * them.
 * ----------
 * QString filename: the file path of the .json file to read. */
void GodsData::readQualitiesJsonFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray jsonData = file.readAll();

    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();

    QJsonValue qualityValue = object.value("Qualities");
    QJsonArray qualityArray = qualityValue.toArray();

    foreach (const QJsonValue & quality, qualityArray)
    {
        Quality* newQuality = new Quality;

        newQuality->name = quality.toObject().value("Name").toString();
        newQuality->type = quality.toObject().value("Type").toString();

        newQuality->type == "Bienfait" ?
                    benefitNameList.append(newQuality->name) :
                    tareNameList.append(newQuality->name);

        newQuality->description = quality.toObject().value("Description").toString();
        newQuality->effects = quality.toObject().value("Effects").toString();
        newQuality->effectsShort = quality.toObject().value("EffectsShort").toString();
        newQuality->notes = quality.toObject().value("Notes").toString();


        QJsonValue modificationValue = quality.toObject().value("Modifications");
        QJsonArray modificationArray = modificationValue.toArray();

        foreach (const QJsonValue & modification, modificationArray)
        {
            QString type = modification.toObject().value("Type").toString();

            if (type == "AddAttribute")
            {
                newQuality->changeAttribute = true;

                QJsonValue attributeValue = modification.toObject().value("Attributes");
                QJsonArray attributeArray = attributeValue.toArray();

                foreach (const QJsonValue & attribute, attributeArray)
                {
                    QString attributeName;
                    attributeName = attribute.toObject().value("Name").toString();

                    int attributeValue;
                    attributeValue = attribute.toObject().value("Value").toInt();

                    newQuality->attributesChange.insert(attributeName, attributeValue);
                }
            }

            else if (type == "AddExpertise")
            {
                newQuality->addExpertise = true;

                QJsonValue expertiseValue = modification.toObject().value("Expertises");
                QJsonArray expertiseArray = expertiseValue.toArray();

                foreach (const QJsonValue & expertise, expertiseArray)
                {
                    QString expertiseName;
                    expertiseName = expertise.toObject().value("Name").toString();

                    int expertiseValue;
                    expertiseValue = expertise.toObject().value("Value").toInt();

                    newQuality->expertisesAdded.insert(expertiseName, expertiseValue);
                }
            }

            else if (type == "ChooseExpertise")
            {
                newQuality->chooseExpertise = true;

                QJsonValue expertiseValue = modification.toObject().value("Expertises");
                QJsonArray expertiseArray = expertiseValue.toArray();

                foreach (const QJsonValue & expertise, expertiseArray)
                {
                    QJsonArray expertiseNameArray = expertise.toObject().value("Name").toArray();
                    foreach (const QJsonValue & name, expertiseNameArray)
                    {
                        newQuality->expertiseToChoose.append(name.toString());
                    }

                    QJsonArray expertiseValueArray = expertise.toObject().value("Value").toArray();
                    foreach (const QJsonValue & value, expertiseValueArray)
                    {
                        newQuality->expertiseRankToChoose.append(value.toInt());
                    }
                }
            }

            else if (type == "AddExpertisePoint")
            {
                newQuality->addExpertisePoint = true;

                newQuality->expertisePointToAdd = modification.toObject().value("Value").toInt();
            }

            else if (type == "AddPower")
            {
                newQuality->addPower = true;

                QJsonValue powerValue = modification.toObject().value("Powers");
                QJsonArray powerArray = powerValue.toArray();

                foreach (const QJsonValue & power, powerArray)
                {
                    QString powerName;
                    powerName = power.toObject().value("Name").toString();

                    int powerValue;
                    powerValue = power.toObject().value("Value").toInt();

                    newQuality->powerToAdd.insert(powerName, powerValue);
                }
            }

            else if (type == "AddPowerPoint")
            {
                newQuality->addPowerPoint = true;

                newQuality->powerPointAdded = modification.toObject().value("Value").toInt();
            }

            else if (type == "AddMiasm")
            {
                newQuality->addMiasm = true;

                newQuality->miasmAdded = modification.toObject().value("Value").toInt();
            }

            else if (type == "AddDevotees")
            {

            }

            else if (type == "AddDestinyPoint")
            {
                newQuality->addDestinyPoint = true;

                newQuality->destinyPointAdded = modification.toObject().value("Value").toInt();
            }


            else if (type == "None")
            {
                newQuality->hasModification = false;
            }

            else
            {
                newQuality->hasModification = false;

                qDebug() << newQuality->name << "does not have a valid Modification type! Do check for any typo, else just indicate None.";
            }
        }


        qualityList.append(newQuality);
        qualityNameList.append(newQuality->name);
    }
}
