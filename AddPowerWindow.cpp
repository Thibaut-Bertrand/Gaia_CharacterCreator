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

#include "AddPowerWindow.h"
#include "ui_AddPowerWindow.h"


AddPowerWindow::AddPowerWindow(PowersData* data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPowerWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Ajouter un pouvoir");

    powersData = data;


    for (QString power : powersData->powerNameList)
    {
        ClickableLabel* powerLabel = new ClickableLabel(power);

        connect(powerLabel, SIGNAL(sendDataToLoad(QString)),
                this, SLOT(displaySelectedPowerDetail(QString)));

        this->ui->powerListVLayout->addWidget(powerLabel);
    }
}


AddPowerWindow::~AddPowerWindow()
{
    delete ui;
}


//     %%%%%%%%%%%%%%%%%%%%%%%
//     %%% private METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%%


void AddPowerWindow::clearLayout(QLayout *layout)
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


//     %%%%%%%%%%%%%%%%%%%%%
//     %%% private SLOTS %%%
//     %%%%%%%%%%%%%%%%%%%%%


void AddPowerWindow::displaySelectedPowerDetail(QString powerName)
{
    clearLayout(this->ui->powerDetailVLayout);


    selectedPowerIndex = powersData->getPowerIndex(powerName);


    // --- Basic infos

    // Name
    QLabel* nameLabel = new QLabel(powerName.toUpper());
    nameLabel->setStyleSheet("font: bold 14px;");
    this->ui->powerDetailVLayout->addWidget(nameLabel);


    // Price
    QString price = "Prix : ";
    price += QString::number(powersData->powerList[selectedPowerIndex]->price);
    price += " / rang";
    QLabel* priceLabel = new QLabel(price);
    this->ui->powerDetailVLayout->addWidget(priceLabel);

    // Type
    QString type = "Type : " + powersData->powerList[selectedPowerIndex]->type;
    QLabel* typeLabel = new QLabel(type);
    this->ui->powerDetailVLayout->addWidget(typeLabel);


    // Action
    QString action = "Action : " + powersData->powerList[selectedPowerIndex]->action;
    QLabel* actionlabel = new QLabel(action);
    this->ui->powerDetailVLayout->addWidget(actionlabel);


    // Range
    QString range = "Portée : " + powersData->powerList[selectedPowerIndex]->range;
    QLabel* rangeLabel = new QLabel(range);
    this->ui->powerDetailVLayout->addWidget(rangeLabel);


    // Duration
    QString duration = "Durée : " + powersData->powerList[selectedPowerIndex]->duration;
    QLabel* durationLabel = new QLabel(duration);
    this->ui->powerDetailVLayout->addWidget(durationLabel);


    // Description
    QString description = "Description : " + powersData->powerList[selectedPowerIndex]->description;
    QLabel* descriptionLabel = new QLabel(description);
    descriptionLabel->setWordWrap(true);
    this->ui->powerDetailVLayout->addWidget(descriptionLabel);


    // Effects
    QString effects = "Effets : " + powersData->powerList[selectedPowerIndex]->effects;
    QLabel* effectsLabel = new QLabel(effects);
    effectsLabel->setWordWrap(true);
    this->ui->powerDetailVLayout->addWidget(effectsLabel);


    // Notes
    QString notes = "Notes : " + powersData->powerList[selectedPowerIndex]->notes;
    QLabel* notesLabel = new QLabel(notes);
    notesLabel->setWordWrap(true);
    this->ui->powerDetailVLayout->addWidget(notesLabel);


    // --- Extras & Flaws

    // Extras
    QString extraNames = "Extras :";
    if (powersData->powerList[selectedPowerIndex]->extraList.isEmpty())
    {
        extraNames += " Aucun extra disponible";
    }

    else
    {
        int length = powersData->powerList[selectedPowerIndex]->extraList.length();
        for (int i_extra = 0; i_extra < length; i_extra++)
        {
            extraNames += " ";
            extraNames += powersData->powerList[selectedPowerIndex]->extraList[i_extra]->name;

            if (i_extra < powersData->powerList[selectedPowerIndex]->extraList.length() - 1)
            {
                extraNames += ",";
            }
        }
    }
    QLabel* extraLabel = new QLabel(extraNames);
    extraLabel->setWordWrap(true);
    this->ui->powerDetailVLayout->addWidget(extraLabel);


    // Flaws
    QString flawNames = "Flaws :";
    if (powersData->powerList[selectedPowerIndex]->flawList.isEmpty())
    {
        flawNames += " Aucun extra disponible";
    }

    else
    {
        int length = powersData->powerList[selectedPowerIndex]->flawList.length();
        for (int i_flaw = 0; i_flaw < length; i_flaw++)
        {
            flawNames += " ";
            flawNames += powersData->powerList[selectedPowerIndex]->flawList[i_flaw]->name;

            if (i_flaw < length - 1)
            {
                flawNames += ",";
            }
        }
    }
    QLabel* flawLabel = new QLabel(flawNames);
    flawLabel->setWordWrap(true);
    this->ui->powerDetailVLayout->addWidget(flawLabel);


    this->ui->powerDetailVLayout->addStretch();
}


void AddPowerWindow::on_addButton_clicked()
{
    emit(sendPowerIndex(selectedPowerIndex));

    this->~AddPowerWindow();
}


void AddPowerWindow::on_cancelButton_clicked()
{
    this->~AddPowerWindow();
}

