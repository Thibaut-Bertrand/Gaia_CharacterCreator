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

#include "CreateNewPowerWindow.h"
#include "ui_CreateNewPowerWindow.h"


CreateNewPowerWindow::CreateNewPowerWindow(PowersData* data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNewPowerWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Créer un nouveau pouvoir");

    powersData = data;

    compositePowerIndexes.clear();
}


CreateNewPowerWindow::~CreateNewPowerWindow()
{
    delete ui;
}


//     %%%%%%%%%%%%%%%%%%%%%%%
//     %%% private METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%%


void CreateNewPowerWindow::clearLayout(QLayout *layout)
{
    if (layout == NULL)
    {
        return;
    }

    QLayoutItem* item;

    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            item->layout()->deleteLater();
            /* Just using "delete" will cause errors and crashes. Don't do that.
             * Nobody like errors and crashes. They're yucky. */
        }

        if (item->widget())
        {
            delete item->widget();
        }

        delete item;
    }
}


void CreateNewPowerWindow::updatePowerListLayout()
{
    clearLayout(this->ui->powerListVLayout);
    clearLayout(this->ui->powerDetailVLayout);

    for (int index : compositePowerIndexes)
    {
        QString name = powersData->powerNameList[index];
        ClickableLabel* nameLabel = new ClickableLabel(name);

        connect(nameLabel, SIGNAL(sendDataToLoad(QString)),
                this, SLOT(displaySelectedPowerDetail(QString)));

        this->ui->powerListVLayout->addWidget(nameLabel);
    }

    this->ui->powerListVLayout->addStretch();
}


//     %%%%%%%%%%%%%%%%%%%%%
//     %%% private SLOTS %%%
//     %%%%%%%%%%%%%%%%%%%%%


void CreateNewPowerWindow::on_addPowerButton_clicked()
{
    AddPowerWindow* addPowerWindow = new AddPowerWindow(powersData);

    connect(addPowerWindow, SIGNAL(sendPowerIndex(int)),
            this, SLOT(addCompositePower(int)));

    addPowerWindow->show();
}


void CreateNewPowerWindow::on_createPowerButton_clicked()
{
    emit(sendPowersIndexes(compositePowerIndexes));

    this->~CreateNewPowerWindow();
}


void CreateNewPowerWindow::on_cancelButton_clicked()
{
    this->~CreateNewPowerWindow();
}


void CreateNewPowerWindow::addCompositePower(int powerIndex)
{
    if (!compositePowerIndexes.contains(powerIndex))
    {
        compositePowerIndexes.append(powerIndex);

        updatePowerListLayout();
    }

    else
    {
        QMessageBox* msgBox = new QMessageBox;
        msgBox->setText("Ce Pouvoir composite est déjà sélectionné. Un Pouvoir composé ne peut avoir qu'une seule version de chaque Pouvoir composite.");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    }
}


void CreateNewPowerWindow::displaySelectedPowerDetail(QString powerName)
{
    clearLayout(this->ui->powerDetailVLayout);

    int powerIndex = powersData->getPowerIndex(powerName);


    // Addon Button
    // ----------
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    ButtonID* addonButton = new ButtonID(powerIndex);
    addonButton->setText("Ajouter un Addon");

    connect(addonButton, SIGNAL(sendID(int)),
            this, SLOT(openPowerAddonWindow(int)));

    buttonLayout->addWidget(addonButton);
    buttonLayout->addStretch();

    this->ui->powerDetailVLayout->addLayout(buttonLayout);


    // Power details
    // ----------

    // --- Basic infos

    // Name
    QLabel* nameLabel = new QLabel(powerName.toUpper());
    nameLabel->setStyleSheet("font: bold 14px;");
    this->ui->powerDetailVLayout->addWidget(nameLabel);


    this->ui->powerDetailVLayout->addStretch();
}


void CreateNewPowerWindow::openPowerAddonWindow(int powerIndex)
{
    AddPowerAddonWindow* addPowerAddonWindow = new AddPowerAddonWindow(powersData,
                                                                       powerIndex);

    connect(addPowerAddonWindow, SIGNAL(sendExtra(int ,int)),
            this, SLOT(addPowerExtra(int, int)));

    connect(addPowerAddonWindow, SIGNAL(sendFlaw(int ,int)),
            this, SLOT(addPowerFlaw(int, int)));

    addPowerAddonWindow->show();
}


void CreateNewPowerWindow::removeCompositePower(int indexToRemove)
{
    if (indexToRemove >= 0 && indexToRemove < compositePowerIndexes.length())
    {
        compositePowerIndexes.remove(indexToRemove);

        updatePowerListLayout();
    }

    else
    {
        qDebug() << "Tried to remove a non-existing composite Power";
    }
}


void CreateNewPowerWindow::addPowerExtra()
{

}


void CreateNewPowerWindow::removePowerExtra()
{

}


void CreateNewPowerWindow::addPowerFlaw()
{

}


void CreateNewPowerWindow::removePowerFlaw()
{

}
