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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QDir>
#include <QMainWindow>
#include <QScrollArea>


#include "CreateNewPowerWindow.h"
#include "DataManager.h"
#include "EncyclopediaWindow.h"
#include "ParentSelectionWindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DataManager* dataManager;


private slots:

    // --- UI

    // File
    void on_action_Nouveau_personnage_triggered();
    void on_action_Charger_personnage_triggered();
    void on_action_Sauvegarder_personnage_triggered();
    void on_action_Quitter_triggered();


    // Help
    void on_action_Encyclop_die_triggered();


    // --- Others

    // Character
    void characterInitialization();


    // Power
    void createNewPower();


private:

    Ui::MainWindow *ui;

    EncyclopediaWindow* encyclopediaWindow;
};
#endif // MAINWINDOW_H
