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

#ifndef ENCYCLOPEDIAWINDOW_H
#define ENCYCLOPEDIAWINDOW_H


#include <QDialog>
#include <QLabel>


#include "ButtonID.h"
#include "ClickableLabel.h"
#include "DataManager.h"


namespace Ui {
class EncyclopediaWindow;
}

class EncyclopediaWindow : public QDialog
{
    Q_OBJECT

public:

    explicit EncyclopediaWindow(DataManager* data, QWidget *parent = nullptr);
    ~EncyclopediaWindow();

private:

    // Methods
    // ----------

    void updateDataLayout(QVector<QString> elementList);


    // Members
    // ----------

    Ui::EncyclopediaWindow *ui;

    DataManager* dataManager;

    QVector<ButtonID*> dataButtonList;

public slots:

    void udpateForGods(QString name);
    void updateForBenefits(QString name);
    void updateForTares(QString name);

    void updateButton(QVector<int> index);

    void labelClicked(QString categoryToLoad, QString elementToLoad);

private slots:

    void on_dataCombobox_currentTextChanged(const QString &arg1);

    void clearLayout(QLayout* layout);
    void on_previousBoxButton_clicked();
    void on_nextBoxButton_clicked();
    void on_closeButton_clicked();
};

#endif // ENCYCLOPEDIAWINDOW_H
