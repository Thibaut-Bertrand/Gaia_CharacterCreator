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

#include "CheckboxID.h"

CheckboxID::CheckboxID(QString text, int newFirstId)
{
    this->setText(text);

    IDs.append(newFirstId);
}


CheckboxID::CheckboxID(QString text, QVector<int> newIDs)
{
    this->setText(text);

    IDs = newIDs;
}


void CheckboxID::setID(int IDNumber, int newID)
{
    if (IDNumber >= 0 && IDNumber < IDs.length())
    {
        IDs[IDNumber] = newID;
    }
}


void CheckboxID::setIDs(QVector<int> newIDs)
{
    if (newIDs.length() == IDs.length())
    {
        IDs = newIDs;
    }
}


void CheckboxID::sendData()
{
    emit sendFirstID(IDs[0]);
    emit sendIDs(IDs);
}


//      %%%%%%%%%%%%%%%%%%%%%%%%%%
//      %%%% METHODS override %%%%
//      %%%%%%%%%%%%%%%%%%%%%%%%%%


/* cf Qt documentation. */
void CheckboxID::mousePressEvent(QMouseEvent *e)
{
    changeCheckState();

    sendData();
}


/***************
 * Inverse the check state of the box.
 ***************/
void CheckboxID::changeCheckState()
{
    if (this->checkState() == Qt::Unchecked)
    {
        this->setCheckState(Qt::Checked);
    }

    else
    {
        this->setCheckState(Qt::Unchecked);
    }
}
