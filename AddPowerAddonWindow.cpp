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

#include "AddPowerAddonWindow.h"
#include "ui_AddPowerAddonWindow.h"


AddPowerAddonWindow::AddPowerAddonWindow(PowersData* data, int index,
                                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPowerAddonWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Ajouter un addon au pouvoir");

    powersData = data;

    powerIndex = index;
}


AddPowerAddonWindow::~AddPowerAddonWindow()
{
    delete ui;
}


void AddPowerAddonWindow::on_addButton_clicked()
{
    this->~AddPowerAddonWindow();
}


void AddPowerAddonWindow::on_cancelButton_clicked()
{
    this->~AddPowerAddonWindow();
}

