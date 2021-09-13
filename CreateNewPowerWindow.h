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

#ifndef CREATENEWPOWERWINDOW_H
#define CREATENEWPOWERWINDOW_H


#include <QDialog>
#include <QMessageBox>


#include "AddPowerAddonWindow.h"
#include "AddPowerWindow.h"
#include "ButtonID.h"
#include "ClickableLabel.h"
#include "PowersData.h"


namespace Ui {
class CreateNewPowerWindow;
}


class CreateNewPowerWindow : public QDialog
{
    Q_OBJECT


public:

    explicit CreateNewPowerWindow(PowersData* data, QWidget *parent = nullptr);
    ~CreateNewPowerWindow();


private:

    // Methods
    // ----------
    void clearLayout(QLayout* layout);
    void updatePowerListLayout();


    // Members
    // ----------
    Ui::CreateNewPowerWindow *ui;

    PowersData* powersData;

    QVector<int> compositePowerIndexes;


private slots:

    // --- UI
    void on_addPowerButton_clicked();
    void on_createPowerButton_clicked();
    void on_cancelButton_clicked();


    // --- Window
    void displaySelectedPowerDetail(QString powerName);
    void openPowerAddonWindow(int powerIndex);


    // --- Power construction

    // Composite Power
    void addCompositePower(int powerIndex);
    void removeCompositePower(int indexToRemove);


    // Power Addon
    void addPowerExtra();
    void removePowerExtra();
    void addPowerFlaw();
    void removePowerFlaw();


signals:

    void sendPowersIndexes(QVector<int> powerIndexes);
};

#endif // CREATENEWPOWERWINDOW_H
