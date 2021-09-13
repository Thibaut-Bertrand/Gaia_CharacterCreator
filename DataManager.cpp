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

#include "DataManager.h"


DataManager::DataManager()
{
    character = new Character();
    godsData = new GodsData();
    powersData = new PowersData();
}


//     %%%%%%%%%%%%%%%%%%%%%%
//     %%% public METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%


void DataManager::openParentWindow()
{
    ParentSelectionWindow* parentSelectionWindow = new ParentSelectionWindow(godsData);

    connect(parentSelectionWindow, SIGNAL(openEncyclopedia()),
            this, SLOT(on_action_Encyclop_die_triggered()));

    connect(parentSelectionWindow, SIGNAL(createCharacter()),
            this, SLOT(characterInitialization()));

    parentSelectionWindow->show();
}


void DataManager::openPowerWindow()
{
    CreateNewPowerWindow* createNewPowerWindow = new CreateNewPowerWindow(powersData);

    connect(createNewPowerWindow, SIGNAL(sendPowersIndexes(QVector<int>)),
            this, SLOT(powerIndexes(QVector<int>)));

    createNewPowerWindow->show();
}


//     %%%%%%%%%%%%%%%%%%%%
//     %%% public SLOTS %%%
//     %%%%%%%%%%%%%%%%%%%%


void DataManager::characterInitialization()
{
    emit(createCharacter());
}


void DataManager::powerIndexes(QVector<int> powerIndexes)
{
    qDebug() << powerIndexes;
}
