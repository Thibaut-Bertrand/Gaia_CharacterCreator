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

#ifndef CHECKBOXID_H
#define CHECKBOXID_H

#include <QCheckBox>

class CheckboxID : public QCheckBox
{
    Q_OBJECT

public:

    CheckboxID(QString text, int newFirstId);
    CheckboxID(QString text, QVector<int> newIDs);

    // Methods
    // ----------

    void setID(int IDNumber, int newID);
    void setIDs(QVector<int> newIds);
    void sendData();


    void changeCheckState();

    // Members
    // ----------

    QVector<int> IDs;

signals:

    void sendFirstID(int ID);
    void sendIDs(QVector<int> IDs);

private:

    // Methods override
    // ----------

    void mousePressEvent(QMouseEvent *e);

};

#endif // CHECKBOXID_H
