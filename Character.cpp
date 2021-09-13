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

#include "Character.h"

Character::Character()
{
    attribute pow;
    pow.name = "Puissance";
    attributes.append(pow);

    attribute agi;
    agi.name = "Agilité";
    attributes.append(agi);

    attribute end;
    end.name = "Endurance";
    attributes.append(end);

    attribute acc;
    acc.name = "Precision";
    attributes.append(acc);

    attribute kno;
    kno.name = "Savoir";
    attributes.append(kno);

    attribute intui;
    intui.name = "Intuition";
    attributes.append(intui);

    attribute elo;
    elo.name = "Eloquence";
    attributes.append(elo);

    attribute div;
    div.name = "Divin";
    attributes.append(div);
}


void Character::initializeStartingPowers()
{

}
