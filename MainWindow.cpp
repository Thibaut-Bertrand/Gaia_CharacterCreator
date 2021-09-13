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

#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Les Terres de Gaïa - Le Dernier Mythe");

    QDir::setCurrent(qApp->applicationDirPath());
    qDebug()<<QDir::currentPath();

    dataManager = new DataManager();

    connect(dataManager, SIGNAL(createCharacter()),
            this, SLOT(characterInitialization()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_Nouveau_personnage_triggered()
{
    dataManager->openParentWindow();
}


void MainWindow::on_action_Charger_personnage_triggered()
{

}


void MainWindow::on_action_Sauvegarder_personnage_triggered()
{

}


void MainWindow::on_action_Quitter_triggered()
{
    qApp->quit();
}


void MainWindow::on_action_Encyclop_die_triggered()
{
    encyclopediaWindow = new EncyclopediaWindow(dataManager);

    encyclopediaWindow->show();
}


void MainWindow::characterInitialization()
{
    // Create the characterTabWidget
    // ----------
    QTabWidget* characterTabWidget = new QTabWidget();


    // --- Personnal data tab
    QWidget* personnalDataTab = new QWidget;
    characterTabWidget->addTab(personnalDataTab, "Données personnelles");

    QVBoxLayout* personnalLayout = new QVBoxLayout;

//    personnalLayout->addWidget(new QLabel("Nouveau personnage !"));
//    personnalLayout->addWidget(new QLabel("Premier parent : " + dataManager->character->firstParent->god->name));
//    if (dataManager->character->secondParent != NULL)
//    {
//        personnalLayout->addWidget(new QLabel("Second parent : " + dataManager->character->secondParent->god->name));
//    }
    personnalLayout->addStretch();
    personnalDataTab->setLayout(personnalLayout);


    // --- Statistics tab (Attributes, Expertises, Vitality, Destiny points...)
    QWidget* statisticsTab = new QWidget;
    characterTabWidget->addTab(statisticsTab, "Attributs");

    QVBoxLayout* statisticsWrapperVLayout = new QVBoxLayout;

    // Attributes layout
    QHBoxLayout* attributesWrapperHLayout = new QHBoxLayout;

    for (int i_att = 0; i_att < dataManager->character->attributes.length(); i_att++)
    {
        attributesWrapperHLayout->addStretch();

        QVBoxLayout* attributeVLayout = new QVBoxLayout;

        QLabel* attributeName = new QLabel(dataManager->character->attributes[i_att].name);
        attributeName->setAlignment(Qt::AlignHCenter);
        attributeName->setStyleSheet("font: bold;");
        QLabel* attributeValue = new QLabel(QString::number(dataManager->character->attributes[i_att].value));
        attributeValue->setAlignment(Qt::AlignHCenter);

        attributeVLayout->addWidget(attributeName);
        attributeVLayout->addWidget(attributeValue);

        attributesWrapperHLayout->addLayout(attributeVLayout);

    }

    attributesWrapperHLayout->addStretch();
    statisticsWrapperVLayout->addLayout(attributesWrapperHLayout);


    statisticsWrapperVLayout->addStretch();

    statisticsTab->setLayout(statisticsWrapperVLayout);

    // --- Ascendance / Benefits and Tares tab
    QWidget* ascendanceTab = new QWidget;
    characterTabWidget->addTab(ascendanceTab, "Ascendance");


    // --- Gear tab
    QWidget* gearTab = new QWidget;
    characterTabWidget->addTab(gearTab, "Trésorerie divine");


    // --- Pillars / Parangons tab
    QWidget* pillarsTab = new QWidget;
    characterTabWidget->addTab(pillarsTab, "Pilliers et Paragons");


    // --- Familiar tab
    QWidget* familiarTab = new QWidget;
    characterTabWidget->addTab(familiarTab, "Familier(s)");


    // --- Power tab
    QWidget* powerTab = new QWidget;

    QVBoxLayout* powerWrapperLayout = new QVBoxLayout;


    // Buttons layout
    QHBoxLayout* powerButtonsLayout = new QHBoxLayout;

    QPushButton* createPowerButton = new QPushButton;
    createPowerButton->setText("Créer un Pouvoir");

    connect(createPowerButton, SIGNAL(clicked()),
            this, SLOT(createNewPower()));

    powerButtonsLayout->addWidget(createPowerButton);


    QPushButton* removePowerButton = new QPushButton;
    removePowerButton->setText("Retirer Pouvoir");
    removePowerButton->setEnabled(false);
    powerButtonsLayout->addWidget(removePowerButton);


    powerButtonsLayout->addStretch();

    powerWrapperLayout->addLayout(powerButtonsLayout);


    // Main Layout
    QHBoxLayout* powerMainLayout = new QHBoxLayout;

    QScrollArea* powerListScrollArea = new QScrollArea;
    powerListScrollArea->setMaximumWidth(150);
    powerMainLayout->addWidget(powerListScrollArea);
    powerWrapperLayout->addLayout(powerMainLayout);


    QScrollArea* powerDetailScrollArea = new QScrollArea;
    powerMainLayout->addWidget(powerDetailScrollArea);
    powerWrapperLayout->addLayout(powerMainLayout);


    powerTab->setLayout(powerWrapperLayout);

    characterTabWidget->addTab(powerTab, "Pouvoirs");




    this->ui->centralVLayout->addWidget(characterTabWidget);
}


void MainWindow::createNewPower()
{
    dataManager->openPowerWindow();
}
