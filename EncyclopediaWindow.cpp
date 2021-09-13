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

#include "EncyclopediaWindow.h"
#include "ui_EncyclopediaWindow.h"


//     %%%%%%%%%%%%%%%%%%%%%%
//     %%% public METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%


EncyclopediaWindow::EncyclopediaWindow(DataManager* data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncyclopediaWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Encyclopédie");

    dataManager = data;

    this->ui->dataCombobox->addItem("Dieux");
    this->ui->dataCombobox->addItem("Bienfaits");
    this->ui->dataCombobox->addItem("Tares");
    this->ui->dataCombobox->addItem("Pouvoirs");
    this->ui->dataCombobox->addItem("Armes");
    this->ui->dataCombobox->addItem("Armures");

    this->ui->dataCombobox->setCurrentIndex(0);
}

EncyclopediaWindow::~EncyclopediaWindow()
{
    delete ui;
}


//     %%%%%%%%%%%%%%%%%%%%%%%
//     %%% private METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%%


/* Update the dataLayout with the provided list of elements.
 * ----------
 * QString elementList: the list of element to put in the dataLayout, such as
 * god's name, weapon's name... */
void EncyclopediaWindow::updateDataLayout(QVector<QString> elementList)
{
    // Clear the dataLayout
    // ----------
    QLayoutItem *item;

    while ((item = this->ui->dataVLayout->takeAt(0)))
    {
        delete item->widget();
    }

    delete item;


    // Populate the dataLayout
    // ----------
    dataButtonList.clear();

    for (int i_element = 0; i_element < elementList.length(); i_element++)
    {
        ButtonID* newButton = new ButtonID({i_element});

        newButton->setText(elementList[i_element]);

        newButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");


        if (this->ui->dataCombobox->currentText() == "Dieux")
        {
            connect(newButton, SIGNAL(sendText(QString)),
                    this, SLOT(udpateForGods(QString)));
        }

        else if (this->ui->dataCombobox->currentText() == "Bienfaits")
        {
            connect(newButton, SIGNAL(sendText(QString)),
                    this, SLOT(updateForBenefits(QString)));
        }

        else if (this->ui->dataCombobox->currentText() == "Tares")
        {
            connect(newButton, SIGNAL(sendText(QString)),
                    this, SLOT(updateForTares(QString)));
        }


        connect(newButton, SIGNAL(sendIDs(QVector<int>)),
                this, SLOT(updateButton(QVector<int>)));


        this->ui->dataVLayout->addWidget(newButton);

        dataButtonList.append(newButton);
    }

    this->ui->dataVLayout->addStretch();
}


//     %%%%%%%%%%%%%%%%%%%%
//     %%% public SLOTS %%%
//     %%%%%%%%%%%%%%%%%%%%


/* Update the dataLayout and the informationLayout to display the gods related
 * data.
 * ----------
 * QString name: the name of the god to display information about.*/
void EncyclopediaWindow::udpateForGods(QString name)
{
    // Clear the informationLayout
    // ----------
    clearLayout(this->ui->informationVLayout);


    // Populate the informationLayout
    // ----------

    // --- Get the god index
    int i_god = 0;
    while (dataManager->godsData->godList[i_god]->name != name)
    {
        i_god++;
    }


    // --- Name, description, origin

    // Name
    QLabel* nameLabel = new QLabel(dataManager->godsData->godList[i_god]->name.toUpper());
    nameLabel->setStyleSheet("font: bold; font-size: 24px;");
    this->ui->informationVLayout->addWidget(nameLabel);


    // Description
    QHBoxLayout* descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    QLabel* descriptionLabel = new QLabel("Description : ");
    descriptionLabel->setStyleSheet("font: bold;");

    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addWidget(new QLabel(dataManager->godsData->godList[i_god]->description));
    descriptionLayout->addStretch();

    this->ui->informationVLayout->addLayout(descriptionLayout);


    // Origin
    QHBoxLayout* originLayout = new QHBoxLayout();
    originLayout->setSpacing(0);

    QLabel* originLabel = new QLabel("Origine : ");
    originLabel->setStyleSheet("font: bold;");

    originLayout->addWidget(originLabel);
    originLayout->addWidget(new QLabel(dataManager->godsData->godList[i_god]->origin));
    originLayout->addStretch();

    this->ui->informationVLayout->addLayout(originLayout);


    // --- Secondary parents

    this->ui->informationVLayout->addWidget(new QLabel(""));

    QLabel* parentLabel = new QLabel("SECOND PARENT");
    parentLabel->setStyleSheet("font: bold;");
    this->ui->informationVLayout->addWidget(parentLabel);


    // Officials
    QHBoxLayout* officialLayout = new QHBoxLayout();
    officialLayout->setSpacing(0);

    QLabel* officialLabel = new QLabel("Officiels : ");
    officialLabel->setStyleSheet("font: bold;");
    officialLayout->addWidget(officialLabel);

    for (int j_official = 0; j_official < dataManager->godsData->godList[i_god]->officalList.length(); j_official++)
    {
        if (j_official > 0)
        {
            officialLayout->addWidget(new QLabel(", "));
        }

        ClickableLabel* officialClickableLabel = new ClickableLabel("Dieux", dataManager->godsData->godList[i_god]->officalList[j_official]);

        connect(officialClickableLabel, SIGNAL(sendDataToLoad(QString, QString)),
                this, SLOT(labelClicked(QString, QString)));

        officialLayout->addWidget(officialClickableLabel);
    }

    officialLayout->addStretch();

    this->ui->informationVLayout->addLayout(officialLayout);


    // Bastards
    QHBoxLayout* bastardLayout = new QHBoxLayout();
    bastardLayout->setSpacing(0);

    QLabel* bastardLabel = new QLabel("Bâtards : ");
    bastardLabel->setStyleSheet("font: bold;");
    bastardLayout->addWidget(bastardLabel);

    for (int j_bastard = 0; j_bastard < dataManager->godsData->godList[i_god]->bastardList.length(); j_bastard++)
    {
        if (j_bastard > 0)
        {
            bastardLayout->addWidget(new QLabel(", "));
        }

        ClickableLabel* bastardClickableLabel = new ClickableLabel("Dieux", dataManager->godsData->godList[i_god]->bastardList[j_bastard]);

        connect(bastardClickableLabel, SIGNAL(sendDataToLoad(QString, QString)),
                this, SLOT(labelClicked(QString, QString)));

        bastardLayout->addWidget(bastardClickableLabel);
    }

    bastardLayout->addStretch();

    this->ui->informationVLayout->addLayout(bastardLayout);


    // Monoparental
    QHBoxLayout* monoparentalLayout = new QHBoxLayout();
    monoparentalLayout->setSpacing(0);

    QLabel* monoparentalLabel = new QLabel("Monoparental : ");
    monoparentalLabel->setStyleSheet("font: bold;");

    monoparentalLayout->addWidget(monoparentalLabel);

    QString monoparental = "Impossible";
    if (dataManager->godsData->godList[i_god]->canBeMonoparental)
    {
        monoparental = "Possible";
    }

    monoparentalLayout->addWidget(new QLabel(monoparental));
    monoparentalLayout->addStretch();

    this->ui->informationVLayout->addLayout(monoparentalLayout);


    // Virgin
    if (dataManager->godsData->godList[i_god]->isVirgin)
    {
        QLabel* virginLabel = new QLabel("Déesse vierge");
        virginLabel->setStyleSheet("font: bold italic;");
        this->ui->informationVLayout->addWidget(virginLabel);
    }


    // --- Benefits / Tares

    this->ui->informationVLayout->addWidget(new QLabel(""));

    QLabel* benetareLabel = new QLabel("BIENFAITS ET TARES");
    benetareLabel->setStyleSheet("font: bold;");
    this->ui->informationVLayout->addWidget(benetareLabel);


    // Benefits
    QHBoxLayout* benefitLayout = new QHBoxLayout();
    benefitLayout->setSpacing(0);

    QLabel* benefitLabel = new QLabel("Bienfaits : ");
    benefitLabel->setStyleSheet("font: bold;");
    benefitLayout->addWidget(benefitLabel);

    for (int j_benefit = 0; j_benefit < dataManager->godsData->godList[i_god]->benefitList.length(); j_benefit++)
    {
        if (j_benefit > 0)
        {
            benefitLayout->addWidget(new QLabel(", "));
        }

        ClickableLabel* benefitClickableLabel = new ClickableLabel("Bienfaits", dataManager->godsData->godList[i_god]->benefitList[j_benefit]->name);

        connect(benefitClickableLabel, SIGNAL(sendDataToLoad(QString, QString)),
                this, SLOT(labelClicked(QString, QString)));

        benefitLayout->addWidget(benefitClickableLabel);
    }

    benefitLayout->addStretch();

    this->ui->informationVLayout->addLayout(benefitLayout);


    // Tares
    QHBoxLayout* tareLayout = new QHBoxLayout();
    tareLayout->setSpacing(0);

    QLabel* tareLabel = new QLabel("Tares : ");
    tareLabel->setStyleSheet("font: bold;");
    tareLayout->addWidget(tareLabel);

    for (int j_tare = 0; j_tare < dataManager->godsData->godList[i_god]->tareList.length(); j_tare++)
    {
        if (j_tare > 0)
        {
            tareLayout->addWidget(new QLabel(", "));
        }

        ClickableLabel* tareClickableLabel = new ClickableLabel("Tares", dataManager->godsData->godList[i_god]->tareList[j_tare]->name);

        connect(tareClickableLabel, SIGNAL(sendDataToLoad(QString, QString)),
                this, SLOT(labelClicked(QString, QString)));

        tareLayout->addWidget(tareClickableLabel);
    }

    tareLayout->addStretch();

    this->ui->informationVLayout->addLayout(tareLayout);


    this->ui->informationVLayout->addStretch();
}


/* Update the dataLayout and the informationLayout to display the benefits
 * related data.
 * ----------
 * QString name: the name of the god to display information about.*/
void EncyclopediaWindow::updateForBenefits(QString name)
{
    // Clear the informationLayout
    // ----------
    clearLayout(this->ui->informationVLayout);


    // Populate the informationLayout
    // ----------

    // --- Get the benefit index
    int benefitIndex = dataManager->godsData->qualityNameList.indexOf(name);


    // --- Info

    // Name
    QLabel* nameLabel = new QLabel(name.toUpper());
    nameLabel->setStyleSheet("font: bold; font-size: 24px;");
    this->ui->informationVLayout->addWidget(nameLabel);


    // Description
    QHBoxLayout* descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    QLabel* descriptionLabel = new QLabel("Description : ");
    descriptionLabel->setStyleSheet("font: bold;");
    descriptionLabel->setMaximumWidth(100);

    descriptionLayout->addWidget(descriptionLabel);

    QLabel* descriptionTextLabel = new QLabel (dataManager->godsData->qualityList[benefitIndex]->description);
    descriptionTextLabel->setWordWrap(true);

    descriptionLayout->addWidget(descriptionTextLabel);

    this->ui->informationVLayout->addLayout(descriptionLayout);


    // Effects
    QHBoxLayout* effectsLayout = new QHBoxLayout();
    effectsLayout->setSpacing(0);

    QLabel* effectsLabel = new QLabel("Effets : ");
    effectsLabel->setStyleSheet("font: bold;");
    effectsLabel->setMaximumWidth(100);

    effectsLayout->addWidget(effectsLabel);

    QLabel* effectsTextLabel = new QLabel (dataManager->godsData->qualityList[benefitIndex]->effects);
    effectsTextLabel->setWordWrap(true);

    effectsLayout->addWidget(effectsTextLabel);

    this->ui->informationVLayout->addLayout(effectsLayout);


    // Notes
    QHBoxLayout* notesLayout = new QHBoxLayout();
    notesLayout->setSpacing(0);

    QLabel* notesLabel = new QLabel("Notes : ");
    notesLabel->setStyleSheet("font: bold;");
    notesLabel->setMaximumWidth(100);

    notesLayout->addWidget(notesLabel);

    QLabel* notesTextLabel = new QLabel (dataManager->godsData->qualityList[benefitIndex]->notes);
    notesTextLabel->setWordWrap(true);

    notesLayout->addWidget(notesTextLabel);

    this->ui->informationVLayout->addLayout(notesLayout);


    this->ui->informationVLayout->addStretch();
}


/* Update the dataLayout and the informationLayout to display the tares related
 * data.
 * ----------
 * QString name: the name of the god to display information about.*/
void EncyclopediaWindow::updateForTares(QString name)
{
    // Clear the informationLayout
    // ----------
    clearLayout(this->ui->informationVLayout);


    // Populate the informationLayout
    // ----------

    // --- Get the tare index
    int tareIndex = dataManager->godsData->qualityNameList.indexOf(name);


    // --- Info

    // Name
    QLabel* nameLabel = new QLabel(name.toUpper());
    nameLabel->setStyleSheet("font: bold; font-size: 24px;");
    this->ui->informationVLayout->addWidget(nameLabel);


    // Description
    QHBoxLayout* descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    QLabel* descriptionLabel = new QLabel("Description : ");
    descriptionLabel->setStyleSheet("font: bold;");
    descriptionLabel->setMaximumWidth(100);

    descriptionLayout->addWidget(descriptionLabel);

    QLabel* descriptionTextLabel = new QLabel(dataManager->godsData->qualityList[tareIndex]->description);
    descriptionTextLabel->setWordWrap(true);

    descriptionLayout->addWidget(descriptionTextLabel);

    this->ui->informationVLayout->addLayout(descriptionLayout);


    // Effects
    QHBoxLayout* effectsLayout = new QHBoxLayout();
    effectsLayout->setSpacing(0);

    QLabel* effectsLabel = new QLabel("Effets : ");
    effectsLabel->setStyleSheet("font: bold;");
    effectsLabel->setMaximumWidth(100);

    effectsLayout->addWidget(effectsLabel);

    QLabel* effectsTextLabel = new QLabel(dataManager->godsData->qualityList[tareIndex]->effects);
    effectsTextLabel->setWordWrap(true);

    effectsLayout->addWidget(effectsTextLabel);

    this->ui->informationVLayout->addLayout(effectsLayout);


    // Notes
    QHBoxLayout* notesLayout = new QHBoxLayout();
    notesLayout->setSpacing(0);

    QLabel* notesLabel = new QLabel("Notes : ");
    notesLabel->setStyleSheet("font: bold;");
    notesLabel->setMaximumWidth(100);

    notesLayout->addWidget(notesLabel);

    QLabel* notesTextLabel = new QLabel(dataManager->godsData->qualityList[tareIndex]->notes);
    notesTextLabel->setWordWrap(true);

    notesLayout->addWidget(notesTextLabel);

    this->ui->informationVLayout->addLayout(notesLayout);


    this->ui->informationVLayout->addStretch();
}


void EncyclopediaWindow::updateButton(QVector<int> index)
{
    for (int i_button = 0; i_button < dataButtonList.length(); i_button++)
    {
        dataButtonList[i_button]->setStyleSheet("background-color: rgba(255, 255, 255, 0);"
                                                "font-weight: normal;");
    }

    dataButtonList[index[0]]->setStyleSheet("background-color: rgba(255, 255, 255, 0);"
                                            "font-weight: bold;");
}


void EncyclopediaWindow::labelClicked(QString categoryToLoad, QString elementToLoad)
{
    if (this->ui->dataCombobox->currentText() != categoryToLoad)
    {
        this->ui->dataCombobox->setCurrentText(categoryToLoad);
    }

    int i_element = 0;
    while (dataButtonList[i_element]->text() != elementToLoad)
    {
        i_element++;
    }

    dataButtonList[i_element]->sendData();
}


//     %%%%%%%%%%%%%%%%%%%%%
//     %%% private SLOTS %%%
//     %%%%%%%%%%%%%%%%%%%%%


void EncyclopediaWindow::on_dataCombobox_currentTextChanged(const QString &arg1)
{
    // Clear the informationLayout
    // ----------
    clearLayout(this->ui->informationVLayout);


    // Call the update
    // ----------
    if (arg1 == "Dieux")
    {
        updateDataLayout(dataManager->godsData->godNameList);
    }

    else if (arg1 == "Bienfaits")
    {
        updateDataLayout(dataManager->godsData->benefitNameList);
    }

    else if (arg1 == "Tares")
    {
        updateDataLayout(dataManager->godsData->tareNameList);
    }
}


void EncyclopediaWindow::clearLayout(QLayout* layout)
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
            item->layout()->deleteLater(); // Just using "delete" will cause errors and crashes.
        }

        if (item->widget())
        {
            delete item->widget();
        }

        delete item;
    }
}

void EncyclopediaWindow::on_previousBoxButton_clicked()
{
    int currentIndex = this->ui->dataCombobox->currentIndex();

    if (currentIndex > 0)
    {
        this->ui->dataCombobox->setCurrentIndex(currentIndex - 1);
    }

    else
    {
        this->ui->dataCombobox->setCurrentIndex(this->ui->dataCombobox->count() - 1);
    }
}


void EncyclopediaWindow::on_nextBoxButton_clicked()
{
    int currentIndex = this->ui->dataCombobox->currentIndex();

    if (currentIndex < this->ui->dataCombobox->count() - 1)
    {
        this->ui->dataCombobox->setCurrentIndex(currentIndex + 1);
    }

    else
    {
        this->ui->dataCombobox->setCurrentIndex(0);
    }
}


void EncyclopediaWindow::on_closeButton_clicked()
{
    this->~EncyclopediaWindow();
}

