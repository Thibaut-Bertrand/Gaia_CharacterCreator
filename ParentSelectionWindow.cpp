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

#include "ParentSelectionWindow.h"
#include "ui_ParentSelectionWindow.h"


//     %%%%%%%%%%%%%%%%%%%%%%
//     %%% public METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%


/* Constructor */
ParentSelectionWindow::ParentSelectionWindow(GodsData* data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParentSelectionWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Sélection des partents");

    godsData = data;

    this->ui->stackedWidget->setCurrentIndex(0);


    // Population the firstParentCombobox
    // ----------

    for (int i_god = 0; i_god < godsData->godList.length(); i_god++)
    {
        if (godsData->godList[i_god]->canBeFirstParent)
        {
            this->ui->firstParentCombobox->addItem(godsData->godList[i_god]->name);
        }
    }

    this->ui->firstParentCombobox->setCurrentIndex(0);
}


/* Desstructor */
ParentSelectionWindow::~ParentSelectionWindow()
{
    delete ui;
}


//     %%%%%%%%%%%%%%%%%%%%%%%
//     %%% private METHODS %%%
//     %%%%%%%%%%%%%%%%%%%%%%%


//     %%% Parent selection page UI %%%


//     Both parents


/* Enable the given checkboxes. Used when choosing benefits or tares.
 * ----------
 * QVector<CheckboxID *> checkboxesToEnable: the list of pointers to the
 * checkboxes to enabled. */
void ParentSelectionWindow::enableCheckboxes(QVector<CheckboxID *> checkboxesToEnable)
{

}


/* Disable the given checkboxes. Used when choosing benefits or tares. Note that
 * only the unchecked checkboxes will be disabled.
 * ----------
 * QVector<CheckboxID *> checkboxesToDisable: the list of pointers to the
 * checkboxes to disabled. */
void ParentSelectionWindow::disableCheckboxes(QVector<CheckboxID *> checkboxesToDisable)
{

}


/* Set the basic data (Name, description and origin) of the specified god, in
 * the specified layout.
 * ----------
 * QVBoxLayout *layout: the layout which will receive the data (cf the .ui
 * file).
 * int godIndex: the index of the god from which to get the data in the
 * godsData->godList. */
void ParentSelectionWindow::setGodBasicData(QVBoxLayout *layout, int parentNumber)
{
    // Name
    // ----------
    QLabel* nameLabel = new QLabel(godsData->godList[parents[parentNumber]->index]->name.toUpper());
    nameLabel->setStyleSheet("font: bold; font-size: 24px;");
    layout->addWidget(nameLabel);


    // Description
    // ----------
    QHBoxLayout* descriptionLayout = new QHBoxLayout();
    descriptionLayout->setSpacing(0);

    QLabel* descriptionLabel = new QLabel("Description : ");
    descriptionLabel->setStyleSheet("font: bold;");

    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addWidget(new QLabel(godsData->godList[parents[parentNumber]->index]->description));
    descriptionLayout->addStretch();

    layout->addLayout(descriptionLayout);


    // Origin
    // ----------
    QHBoxLayout* originLayout = new QHBoxLayout();
    originLayout->setSpacing(0);

    QLabel* originLabel = new QLabel("Origine : ");
    originLabel->setStyleSheet("font: bold;");

    originLayout->addWidget(originLabel);
    originLayout->addWidget(new QLabel(godsData->godList[parents[parentNumber]->index]->origin));
    originLayout->addStretch();

    layout->addLayout(originLayout);
}


/* Set the benefits of the specified god, in the specified layout.
 * ----------
 * return QVector<CheckboxID*>: the list of the benefit checkboxes of the god of
 * interest.
 * ----------
 * QVBoxLayout *layout: the layout which will receive the data (cf the .ui
 * file).
 * int godIndex: the index of the god from which to get the data in the
 * godsData->godList.
 * int parentNumber: either 0 or 1, helps to identified the checkboxes of the
 * benefits. */
QVector<CheckboxID*> ParentSelectionWindow:: setGodBenefits(QVBoxLayout* layout,
                                                            int parentNumber)
{
    // Check parentNumber
    // ----------
    if (parentNumber < 0 || parentNumber > 1)
    {
        qDebug() << "ERROR: invalid parentNumber in setGodBenefits (ParentSelectionWindow)!";
    }

    int godIndex = parents[parentNumber]->index;

    // Benefits
    // ----------
    layout->addWidget(new QLabel(""));

    QLabel* benefitLabel = new QLabel("BIENFAITS");
    benefitLabel->setStyleSheet("font: bold;");
    layout->addWidget(benefitLabel);


    QVBoxLayout* benefitWrapperLayout = new QVBoxLayout;
    benefitWrapperLayout->setSpacing(15);

    QVector<CheckboxID*> checkboxList;

    for (int i_benefit = 0; i_benefit < godsData->godList[godIndex]->benefitList.length(); i_benefit++)
    {
        QString benefitName = godsData->godList[godIndex]->benefitList[i_benefit]->name;

        QHBoxLayout* benefitLayout = new QHBoxLayout;


        // Get the benefit index
        int benefitIndex = godsData->qualityNameList.indexOf(benefitName);


        // Checkbox
        CheckboxID* benefitCheckbox = new CheckboxID("", {parentNumber, i_benefit, benefitIndex});

        connect(benefitCheckbox, SIGNAL(sendIDs(QVector<int>)),
                this, SLOT(benefitInteracted(QVector<int>)));

        checkboxList.append(benefitCheckbox);
        benefitLayout->addWidget(benefitCheckbox);
        benefitLayout->setAlignment(benefitCheckbox, Qt::AlignTop);



        // Label
        ClickableLabel* nameLabel = new ClickableLabel("Bienfaits", benefitName, true);
        nameLabel->setStyleSheet("font: bold;");

        connect(nameLabel, SIGNAL(sendDataToLoad(QString, QString)),
                this, SLOT(requestEncyclopediaOpening(QString, QString)));

        benefitLayout->addWidget(nameLabel);
        benefitLayout->setAlignment(nameLabel, Qt::AlignTop | Qt::AlignLeft);


        // Effects
        QString effects = "";
        if (godsData->qualityList[benefitIndex]->effectsShort != "None")
        {
            effects = godsData->qualityList[benefitIndex]->effectsShort;
        }

        QLabel* effectsLabel = new QLabel(effects);
        effectsLabel->setWordWrap(true);
        effectsLabel->setAlignment(Qt::AlignJustify);
        benefitLayout->addWidget(effectsLabel);


        benefitLayout->addStretch();

        benefitWrapperLayout->addLayout(benefitLayout);
    }

    benefitWrapperLayout->addStretch();
    layout->addLayout(benefitWrapperLayout);

    return checkboxList;
}


/* Set the tares of the specified god, in the specified layout.
 * ----------
 * return QVector<CheckboxID*>: the list of the tare checkboxes of the god of
 * interest.
 * ----------
 * QVBoxLayout *layout: the layout which will receive the data (cf the .ui
 * file).
 * int godIndex: the index of the god from which to get the data in the
 * godsData->godList.
 * int parentNumber: either 0 or 1, helps to identified the checkboxes of the
 * tares. */
QVector<CheckboxID*> ParentSelectionWindow::setGodTares(QVBoxLayout* layout,
                                                        int parentNumber)
{
    // Check parentNumber
    // ----------
    if (parentNumber < 0 || parentNumber > 1)
    {
        qDebug() << "ERROR: invalid parentNumber in setGodTares (ParentSelectionWindow)!";
    }

    int godIndex = parents[parentNumber]->index;


    // Tares
    // ----------
    layout->addWidget(new QLabel(""));

    QLabel* tareLabel = new QLabel("TARES");
    tareLabel->setStyleSheet("font: bold;");
    layout->addWidget(tareLabel);


    QVBoxLayout* tareWrapperLayout = new QVBoxLayout;
    tareWrapperLayout->setSpacing(15);

    QVector<CheckboxID*> checkboxList;

    for (int i_tare = 0; i_tare < godsData->godList[godIndex]->tareList.length(); i_tare++)
    {
        QString tareName = godsData->godList[godIndex]->tareList[i_tare]->name;

        QHBoxLayout* tareLayout = new QHBoxLayout;


        // Get the tare index
        int tareIndex = godsData->qualityNameList.indexOf(tareName);


        // Checkbox
        CheckboxID* tareCheckbox = new CheckboxID("", {parentNumber, i_tare, tareIndex});

        connect(tareCheckbox, SIGNAL(sendIDs(QVector<int>)),
                this, SLOT(tareInteracted(QVector<int>)));

        checkboxList.append(tareCheckbox);
        tareCheckbox->setEnabled(false);
        tareLayout->addWidget(tareCheckbox);
        tareLayout->setAlignment(tareCheckbox, Qt::AlignTop);



        // Label
        ClickableLabel* nameLabel = new ClickableLabel("Tares", tareName, true);
        nameLabel->setStyleSheet("font: bold;");
        tareLayout->addWidget(nameLabel);

        connect(nameLabel, SIGNAL(sendDataToLoad(QString, QString)),
                this, SLOT(requestEncyclopediaOpening(QString, QString)));

        tareLayout->setAlignment(nameLabel, Qt::AlignTop | Qt::AlignLeft);


        // Effects
        QString effects = "";
        if (godsData->qualityList[tareIndex]->effectsShort != "None")
        {
            effects = godsData->qualityList[tareIndex]->effectsShort;
        }

        QLabel* effectsLabel = new QLabel(effects);
        effectsLabel->setWordWrap(true);
        effectsLabel->setAlignment(Qt::AlignJustify);
        tareLayout->addWidget(effectsLabel);


        tareLayout->addStretch();

        tareWrapperLayout->addLayout(tareLayout);
    }

    tareWrapperLayout->addStretch();
    layout->addLayout(tareWrapperLayout);

    return checkboxList;
}


//     First parent


/* Update the layout of the first parent (on the left). This layout is always
 * active, as the character must have at least one parent.
 * The data used to populate the layout depends on the selected god in the
 * firstParentCombobox.
 * When a new parent is selected, the second parent part (on the right) is
 * automatically cleared. */
void ParentSelectionWindow::updateFirstParent()
{
    // Clear the firstParentInformationLayout
    // ----------
    clearLayout(this->ui->firstParentInformationVLayout);
    disableSecondParent();


    // Clear the Parent struct
    // ----------
    resetParent(parents[0]);
    resetParent(parents[1]);

    parents[0]->isActive = true;


    // Populate the firstParentInformationLayout
    // ----------

    // --- Get the god index
    parents[0]->index = getGodIndex(this->ui->firstParentCombobox->currentText());


    // --- Name, description, origin
    setGodBasicData(this->ui->firstParentInformationVLayout, 0);

    areParentVirgin = godsData->godList[parents[0]->index]->isVirgin;


    // --- Secondary parents
    availableSecondParent.clear();

    this->ui->firstParentInformationVLayout->addWidget(new QLabel(""));

    QLabel* parentLabel = new QLabel("SECOND PARENT");
    parentLabel->setStyleSheet("font: bold;");
    this->ui->firstParentInformationVLayout->addWidget(parentLabel);


    // Officials
    QHBoxLayout* officialLayout = new QHBoxLayout();
    officialLayout->setSpacing(0);

    QLabel* officialLabel = new QLabel("Officiels : ");
    officialLabel->setStyleSheet("font: bold;");
    officialLayout->addWidget(officialLabel);

    for (int i_official = 0; i_official < godsData->godList[parents[0]->index]->officalList.length(); i_official++)
    {
        if (i_official > 0)
        {
            officialLayout->addWidget(new QLabel(", "));
        }

        QString officialParent = godsData->godList[parents[0]->index]->officalList[i_official];
        QLabel* officialLabel = new QLabel(officialParent);
        if (officialParent != "None")
        {
            availableSecondParent.append(officialParent);
        }

        officialLayout->addWidget(officialLabel);
    }

    officialLayout->addStretch();

    this->ui->firstParentInformationVLayout->addLayout(officialLayout);


    // Bastards
    QHBoxLayout* bastardLayout = new QHBoxLayout();
    bastardLayout->setSpacing(0);

    QLabel* bastardLabel = new QLabel("Bâtards : ");
    bastardLabel->setStyleSheet("font: bold;");
    bastardLayout->addWidget(bastardLabel);

    for (int i_bastard = 0; i_bastard < godsData->godList[parents[0]->index]->bastardList.length(); i_bastard++)
    {
        if (i_bastard > 0)
        {
            bastardLayout->addWidget(new QLabel(", "));
        }

        QString bastardParent = godsData->godList[parents[0]->index]->bastardList[i_bastard];
        QLabel* bastardLabel = new QLabel(bastardParent);
        if (bastardParent!= "None")
        {
            availableSecondParent.append(bastardParent);
        }

        bastardLayout->addWidget(bastardLabel);
    }

    bastardLayout->addStretch();

    this->ui->firstParentInformationVLayout->addLayout(bastardLayout);

    availableSecondParent.sort();

    // Monoparental
    QHBoxLayout* monoparentalLayout = new QHBoxLayout();
    monoparentalLayout->setSpacing(0);

    QLabel* monoparentalLabel = new QLabel("Monoparental : ");
    monoparentalLabel->setStyleSheet("font: bold;");

    monoparentalLayout->addWidget(monoparentalLabel);

    QString monoparental = "Impossible";
    if (godsData->godList[parents[0]->index]->canBeMonoparental)
    {
        monoparental = "Possible";
    }

    monoparentalLayout->addWidget(new QLabel(monoparental));
    monoparentalLayout->addStretch();

    this->ui->firstParentInformationVLayout->addLayout(monoparentalLayout);


    // Virgin
    if (godsData->godList[parents[0]->index]->isVirgin)
    {
        QLabel* virginLabel = new QLabel("Déesse vierge");
        virginLabel->setStyleSheet("font: bold italic;");
        this->ui->firstParentInformationVLayout->addWidget(virginLabel);
    }


    // --- Parenting choices

    // Second parent
    secondParentCheckbox = new CheckboxID("Deuxième Parent", parents[0]->index);

    connect(secondParentCheckbox, SIGNAL(sendFirstID(int)),
            this, SLOT(secondParentChecked(int)));

    this->ui->firstParentInformationVLayout->addWidget(secondParentCheckbox);


    // Monoparental
    monoparentalCheckbox = new QCheckBox("Monoparental");


    connect(monoparentalCheckbox, SIGNAL(stateChanged(int)),
            this, SLOT(monoparentalChecked(int)));

    this->ui->firstParentInformationVLayout->addWidget(monoparentalCheckbox);


    // Check parenting
    if (!godsData->godList[parents[0]->index]->canBeMonoparental)
    {
        secondParentCheckbox->setChecked(true);
        secondParentCheckbox->setEnabled(false);
        secondParentChecked(parents[0]->index);
    }

    if (!godsData->godList[parents[0]->index]->canBeMonoparental)
    {
        monoparentalCheckbox->setEnabled(false);
    }

    // --- Benefits / Tares

    // Benefits
    parents[0]->benefitCheckboxes = setGodBenefits(this->ui->firstParentInformationVLayout,
                                                   0);


    // Tares
    parents[0]->tareCheckboxes = setGodTares(this->ui->firstParentInformationVLayout,
                                             0);


    this->ui->firstParentInformationVLayout->addStretch();
}


//     Second parents


/* Clear and disable the UI element of the second parent part (on the right).
 * For example when changing the first parent (resetting) or selecting a
 * monoparental first parent. */
void ParentSelectionWindow::disableSecondParent()
{
    clearLayout(this->ui->secondParentInformationVLayout);

    this->ui->secondParentCombobox->setEnabled(false);
    this->ui->secondParentCombobox->clear();

    this->ui->previousSecondParentButton->setEnabled(false);

    this->ui->nextSecondParentButton->setEnabled(false);
}


/* Update the layout of the second parent (on the right). This layout is only
 * active when a second parent is selected in the first parent part.
 * The data used to populate the layout depends on the selected god in the
 * secondParentCombobox.
 * The second parent does not have supplementary parenting choices, only the
 * first does. */
void ParentSelectionWindow::updateSecondParent()
{
    // Clear the secondParentInformationLayout
    // ----------

    clearLayout(this->ui->secondParentInformationVLayout);


    // Clear the Parent struct
    // ----------
    resetParent(parents[1]);

    parents[1]->isActive = true;


    // Populate the secondParentInformationLayout
    // ----------

    // --- Get the god index
    parents[1]->index = getGodIndex(this->ui->secondParentCombobox->currentText());


    // --- Name, description, origin
    setGodBasicData(this->ui->secondParentInformationVLayout, 1);


    // --- Benefits / Tares

    // Benefits
    parents[1]->benefitCheckboxes = setGodBenefits(this->ui->secondParentInformationVLayout,
                                                   1);


    // Tares
    parents[1]->tareCheckboxes = setGodTares(this->ui->secondParentInformationVLayout,
                                             1);


    this->ui->secondParentInformationVLayout->addStretch();
}


//     %%% Qualities selection page UI %%%



void ParentSelectionWindow::setDetailledQualities(QVBoxLayout *layout,
                                                  int parentNumber,
                                                  int qualityIndex)
{
    // --- Quality name
    QLabel* benefitNameLabel = new QLabel(godsData->qualityList[qualityIndex]->name);
    benefitNameLabel->setStyleSheet("font: bold;");
    layout->addWidget(benefitNameLabel);


    // --- Quality effects
    QLabel* benefitEffectsLabel = new QLabel(godsData->qualityList[qualityIndex]->effects);
    benefitEffectsLabel->setWordWrap(true);
    layout->addWidget(benefitEffectsLabel);


    // --- Quality modifications
    if (godsData->qualityList[qualityIndex]->hasModification)
    {
        if (godsData->qualityList[qualityIndex]->chooseExpertise)
        {
            QLabel* noteLabel = new QLabel("Vous ne pouvez choisir qu'une seule fois une expertise donnée !");
            noteLabel->setStyleSheet("font: italic 10px;");
            noteLabel->setWordWrap(true);
            layout->addWidget(noteLabel);

            for (int i_exp = 0; i_exp < godsData->qualityList[qualityIndex]->expertiseRankToChoose.length(); i_exp++)
            {
                QHBoxLayout* expLayout = new QHBoxLayout;
                QLabel* expLabel = new QLabel("Expertise au rang" + QString::number(godsData->qualityList[qualityIndex]->expertiseRankToChoose[i_exp]) + " :");
                QComboBox* expCombo = new QComboBox;
                for (int j_exp = 0; j_exp < godsData->qualityList[qualityIndex]->expertiseToChoose.length(); j_exp++)
                {
                    expCombo->addItem(godsData->qualityList[qualityIndex]->expertiseToChoose[j_exp]);
                }
                expLayout->addWidget(expLabel);
                expLayout->addWidget(expCombo);
                expLayout->addStretch();
                layout->addLayout(expLayout);
            }
        }
    }
}


/* Set the qualities (benefits and tares) and their details in the appropriate
 * layout for each selected parent. If a quality necessitate a choice (like
 * choosing which bonus to take), the it will display the widget to choose it.
 * ----------
 * QVBoxLayout *layout: the layout that will receive the qualities data.
 * int parentNumber: the number of the parent from which take the info. Either 0
 * or 1. */
void ParentSelectionWindow::updateQualitiesLayout(QVBoxLayout *layout,
                                                  int parentNumber)
{
    // --- Benefits
    QLabel* benefitLabel = new QLabel("BIENFAITS");
    benefitLabel->setStyleSheet("font: bold 16px;");
    layout->addWidget(benefitLabel);


    for (int i_ben = 0; i_ben < parents[parentNumber]->benefitCheckboxes.length(); i_ben++)
    {
        if (parents[parentNumber]->benefitCheckboxes[i_ben]->isChecked())
        {
            int benefitIndex = parents[parentNumber]->benefitCheckboxes[i_ben]->IDs[2];

            setDetailledQualities(layout, parentNumber, benefitIndex);

            layout->addWidget(new QLabel(""));
        }
    }


    // --- Tare
    QLabel* tareLabel = new QLabel("TARES");
    tareLabel->setStyleSheet("font: bold 16px;");
    layout->addWidget(tareLabel);


    for (int i_tare = 0; i_tare < parents[parentNumber]->tareCheckboxes.length(); i_tare++)
    {
        if (parents[parentNumber]->tareCheckboxes[i_tare]->isChecked())
        {
            if (i_tare != 0)
            {
                layout->addWidget(new QLabel(""));
            }

            int tareIndex = parents[parentNumber]->tareCheckboxes[i_tare]->IDs[2];

            setDetailledQualities(layout, parentNumber, tareIndex);
        }
    }


    // Stretch
    layout->addStretch();
}


void ParentSelectionWindow::updateQualitiesSelectionPage()
{
    // Clear data
    // ----------

    // --- Clear layouts
    clearLayout(this->ui->firstParentQualitiesVLayout);
    clearLayout(this->ui->secondParentQualitiesVLayout);


    // --- Reset checkboxes
    QString defaultStylesheet = "font: normal;";

    this->ui->firstLegitLabel->setEnabled(false);
    this->ui->firstLegitLabel->setStyleSheet(defaultStylesheet);
    this->ui->firstBastardLabel->setEnabled(false);
    this->ui->firstBastardLabel->setStyleSheet(defaultStylesheet);
    this->ui->firstCreationBox->setChecked(false);
    this->ui->firstCreationBox->setEnabled(false);
    this->ui->firstCreationBox->setStyleSheet(defaultStylesheet);
    this->ui->firstCreationLabel->setEnabled(false);
    this->ui->firstCreationLabel->setStyleSheet(defaultStylesheet);

    this->ui->secondLegitLabel->setEnabled(false);
    this->ui->secondLegitLabel->setStyleSheet(defaultStylesheet);
    this->ui->secondBastardLabel->setEnabled(false);
    this->ui->secondBastardLabel->setStyleSheet(defaultStylesheet);
    this->ui->secondCreationBox->setChecked(false);
    this->ui->secondCreationBox->setEnabled(false);
    this->ui->secondCreationBox->setStyleSheet(defaultStylesheet);
    this->ui->secondCreationLabel->setEnabled(false);
    this->ui->secondCreationLabel->setStyleSheet(defaultStylesheet);


    // Update data
    // ----------

    // --- Set the name-s
    this->ui->firstParentLabel->setText(godsData->godList[parents[0]->index]->name);

    if (parents[1]->isActive)
    {
        this->ui->secondParentLabel->setText(godsData->godList[parents[1]->index]->name);
    }

    else
    {
        this->ui->secondParentLabel->setText("Pas de second parent");
    }


    // --- Set the legitimacy-ies
    QString activeStylesheet = "font: bold;";

    // Case 1: Only one parent. This parent can be a virin goddess. The
    // charater is obligatorily a legitimate creation.
    if (monoparentalCheckbox->isChecked())
    {
        this->ui->firstLegitLabel->setEnabled(true);
        this->ui->firstLegitLabel->setStyleSheet(activeStylesheet);
        this->ui->firstCreationBox->setChecked(true);
        this->ui->firstCreationBox->setStyleSheet(activeStylesheet);
    }

    else
    {
        // Case 2: Two virgin goddesses. The character is obligatorily a
        // legitimate creation on both side.
        if (areParentVirgin)
        {
            this->ui->firstLegitLabel->setEnabled(true);
            this->ui->firstLegitLabel->setStyleSheet(activeStylesheet);
            this->ui->firstCreationBox->setChecked(true);
            this->ui->firstCreationBox->setStyleSheet(activeStylesheet);
            this->ui->firstCreationLabel->setEnabled(true);
            this->ui->firstCreationLabel->setStyleSheet(activeStylesheet);

            this->ui->secondLegitLabel->setEnabled(true);
            this->ui->secondLegitLabel->setStyleSheet(activeStylesheet);
            this->ui->secondCreationBox->setChecked(true);
            this->ui->secondCreationBox->setStyleSheet(activeStylesheet);
            this->ui->secondCreationLabel->setEnabled(true);
            this->ui->secondCreationLabel->setStyleSheet(activeStylesheet);
        }

        // Case 3: Two parent. The parents aren't virgin godesses. The character
        // can choose to be a creation or not. Its legitimacy depends on the
        // relation of the parents.
        else
        {
            this->ui->firstCreationBox->setEnabled(true);
            this->ui->firstCreationLabel->setEnabled(true);
            this->ui->secondCreationBox->setEnabled(true);
            this->ui->secondCreationLabel->setEnabled(true);


            // Get parents legitimacies
            QVector<bool> legitimacy = getParentLegitimacy();


            // First parent
            if (legitimacy[0])
            {
                this->ui->firstLegitLabel->setEnabled(true);
                this->ui->firstLegitLabel->setStyleSheet(activeStylesheet);
            }

            else
            {
                this->ui->firstBastardLabel->setEnabled(true);
                this->ui->firstBastardLabel->setStyleSheet(activeStylesheet);
            }


            // Second parent
            if (legitimacy[1])
            {
                this->ui->secondLegitLabel->setEnabled(true);
                this->ui->secondLegitLabel->setStyleSheet(activeStylesheet);
            }

            else
            {
                this->ui->secondBastardLabel->setEnabled(true);
                this->ui->secondBastardLabel->setStyleSheet(activeStylesheet);
            }
        }
    }


    // --- Set the qualities
    updateQualitiesLayout(this->ui->firstParentQualitiesVLayout, 0);

    if (parents[1]->isActive)
    {
        updateQualitiesLayout(this->ui->secondParentQualitiesVLayout, 1);
    }
}


//     %%% Utilities %%%


bool ParentSelectionWindow::checkBenefits(int parent)
{

}


bool ParentSelectionWindow::checkTares(int parent)
{

}


/* Clear the specified layout of everything it contains. If the specified layout
 * contains others layouts, the methods itself is called back.
 * ----------
 * QLayout* layout: the layout to clear. */
void ParentSelectionWindow::clearLayout(QLayout *layout)
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


/* Get the index of the specified god in godsData->godList.
 * ----------
 * return int: the index of the specified god in the godsData->godList.
 * ----------
 * QString godName: the name of the god which index in the godsData->godList is
 * needed. */
int ParentSelectionWindow::getGodIndex(QString godName)
{
    int godIndex = 0;

    while (godsData->godList[godIndex]->name != godName)
    {
        godIndex++;
    }

    return godIndex;
}


/* Get the parent legitimacy. Only called when there's two parent.
 * ----------
 * return QVector<bool>: return two bool, one for each of the two parent. True
 * if the parent consider the character as legitimate, false otherwise. */
QVector<bool> ParentSelectionWindow::getParentLegitimacy()
{
    QVector<bool> legitimacy;


    int firstIndex = parents[0]->index;
    QString firstName = godsData->godList[firstIndex]->name;

    int secondIndex = parents[1]->index;
    QString secondName = godsData->godList[secondIndex]->name;


    // --- First parent
    if (godsData->godList[firstIndex]->officalList.contains(secondName))
    {
        legitimacy.append(true);
    }

    else
    {
        legitimacy.append(false);
    }


    // --- Second parent
    if (godsData->godList[secondIndex]->officalList.contains(firstName))
    {
        legitimacy.append(true);
    }

    else
    {
        legitimacy.append(false);
    }


    return legitimacy;
}


/* Reset the specified struct Parent. Called when the user change the first or
 * second parent (if available). This struct is mainly used to easily track the
 * the benefit and tare checkboxes.
 * ----------
 * Parent *parentToReset: the parent struct to reset to its original values. */
void ParentSelectionWindow::resetParent(Parent *parentToReset)
{
    parentToReset->isActive = false;
    parentToReset->index = 0;
    parentToReset->nbOfBenefit = 0;
    parentToReset->nbOfTare = 0;
    parentToReset->benefitCheckboxes.clear();
    parentToReset->tareCheckboxes.clear();
}


/* Check if the necessary choices have been made if the parent selection page.
 * Reminder :
 * - The first parent have 2 possibility : either obligatory with another one
 * (the second parent is displayed automatically), or can be alone or with
 * another one (in this case, the user must check one of the boxes).
 * - For each parent, the user must select 1 benefit. She can also select 1 tare
 * per parent. In this case, she alsso must select a second benefit for each
 * parent for which a tare is selected.
 * ----------
 * return bool: 0 if enough parent and benefit(s)/tare(s) are selected. 1 if the
 * first parent don't have any parental boxes checked. 2 if the qualities aren't
 * correctly selected. */
int ParentSelectionWindow::validateParentSelection()
{
    // Check parents
    // ----------
    if (!monoparentalCheckbox->isChecked()
            && !secondParentCheckbox->isChecked())
    {
        return 1;
    }


    // Check qualities
    // ----------
    for (int i_parent = 0; i_parent < parents.length(); i_parent++)
    {
        if (parents[i_parent]->isActive)
        {
            if ((parents[i_parent]->nbOfBenefit == 0)

                    || (parents[i_parent]->nbOfBenefit == 2
                        && parents[i_parent]->nbOfTare == 0)

                    || (parents[i_parent]->nbOfBenefit == 1
                        && parents[i_parent]->nbOfTare == 1))
            {
                return 2;
            }
        }
    }

    return 0;
}


//     %%%%%%%%%%%%%%%%%%%%%
//     %%% private SLOTS %%%
//     %%%%%%%%%%%%%%%%%%%%%


//     %%% Utilities %%%


/* Open the encyclopedia by sending a signal to the MainWindow. */
void ParentSelectionWindow::on_encyclopediaButton_clicked()
{
    emit(openEncyclopedia()); // -> Mainwindow
}


/* Open a dialog window that show the steps to take when selecting parents, and
 * what can/cannot be done. */
void ParentSelectionWindow::on_helpButton_clicked()
{

}


/* Go back from the parent selection page to the qualities selection page.
 * Change the next button to confirm button. */
void ParentSelectionWindow::on_previousButton_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
    this->ui->okButton->setText("Suivant");
    this->ui->previousButton->setEnabled(false);
    isOnParentSelectionPage = true;
}


/* If on the parent selection page, go to the qualities selection page.
 * Else, initialize the needed value in the character, then close the window. */
void ParentSelectionWindow::on_okButton_clicked()
{
    if (isOnParentSelectionPage)
    {
        /* Check if enough parent are selected, as well as the correct amount of
         * qualities (benefits/tares). */
        int validator = validateParentSelection();

        if (validator == 0)
        {
            // Everything's good !

            this->ui->stackedWidget->setCurrentIndex(1);
            this->ui->okButton->setText("Confirmer");
            this->ui->previousButton->setEnabled(true);
            isOnParentSelectionPage = false;

            updateQualitiesSelectionPage();
        }

        else
        {
            QMessageBox msgBox;

            if (validator == 1)
            {
                // first parent parental check box not checked.
                msgBox.setText("Vous devez faire un choix de parenté : soit "
                               "sélectionner la case \"Second parent\", soit "
                               "sélectionner la case \"Monoparentale\"");
            }

            else if (validator == 2)
            {
                // Benefits/Tares nor correctly selected.
                msgBox.setText("Les Bienfaits et les Tares sont incorrectement "
                               "sélectionnés. Pour rappel, chaque parent doit "
                               "avoir au moins un Bienfait sélectionné. Si une "
                               "Tare est sélectionnée pour un parent, un "
                               "second Bienfait doit être sélectionnés pour ce "
                               "même parent.\nNote : Vous pouvez sélectionner "
                               "une Tare (et deux Bienfaits) pour un parent et "
                               "seulement un Bienfait pour l'autre si vous le "
                               "souhaitez.");
            }

            msgBox.exec();
        }
    }

    else
    {
//        firstParent = this->ui->firstParentCombobox->currentText();
//        firstParentIndex = parents[0]->index;

        if (secondParentCheckbox->isChecked())
        {
//            hasSecondParent = true;
//            secondParent = this->ui->secondParentCombobox->currentText();
//            secondParentIndex = parents[1]->index;
        }

        else
        {
//            isCreation = true;
        }


        emit(createCharacter());

        this->~ParentSelectionWindow();
    }
}


/* Just close the window. */
void ParentSelectionWindow::on_cancelButton_clicked()
{
    this->~ParentSelectionWindow();
}


//     %%% Parent selection %%%


//     First parent


/* Select the previous parent in the firstParentCombobox. */
void ParentSelectionWindow::on_previousFirstParentButton_clicked()
{
    int currentIndex = this->ui->firstParentCombobox->currentIndex();

    if (currentIndex > 0)
    {
        this->ui->firstParentCombobox->setCurrentIndex(currentIndex - 1);
    }

    else
    {
        this->ui->firstParentCombobox->setCurrentIndex(this->ui->firstParentCombobox->count() - 1);
    }
}


/* Select the next parent in the firstParentCombobox. */
void ParentSelectionWindow::on_nextFirstParentButton_clicked()
{
    int currentIndex = this->ui->firstParentCombobox->currentIndex();

    if (currentIndex < this->ui->firstParentCombobox->count() - 1)
    {
        this->ui->firstParentCombobox->setCurrentIndex(currentIndex + 1);
    }

    else
    {
        this->ui->firstParentCombobox->setCurrentIndex(0);
    }
}


/* Called when the firstParentCombobox index is changed.
 * ----------
 * int index: the new index of the firstParentCombobox. */
void ParentSelectionWindow::on_firstParentCombobox_currentIndexChanged(int index)
{
    updateFirstParent();
}


/* Called when the user want to choose a second parent.
 * ----------
 * int godIndex: the index of the first parent in godsData->godList. */
void ParentSelectionWindow::secondParentChecked(int godIndex)
{
    if (secondParentCheckbox->isChecked())
    {
        monoparentalCheckbox->setChecked(false);

        this->ui->secondParentCombobox->setEnabled(true);
        this->ui->previousSecondParentButton->setEnabled(true);
        this->ui->nextSecondParentButton->setEnabled(true);


        // --- Populate the secondParentCombobox

        foreach (QString parent, availableSecondParent)
        {
            this->ui->secondParentCombobox->addItem(parent);
        }

        updateSecondParent();
    }

    else
    {
        disableSecondParent();
    }
}


/* Called when the user change the checked state of the monoparentalCheckbox.
 * ----------
 * int state: either 1 (unchecked) or 2 (checked). */
void ParentSelectionWindow::monoparentalChecked(int state)
{
    // if state = checked
    if (state == 2 && secondParentCheckbox->isChecked())
    {
        secondParentCheckbox->changeCheckState();

        disableSecondParent();
    }
}


//     Second parent


/* Select the previous parent in the secondParentCombobox. */
void ParentSelectionWindow::on_previousSecondParentButton_clicked()
{
    int currentIndex = this->ui->secondParentCombobox->currentIndex();

    if (currentIndex > 0)
    {
        this->ui->secondParentCombobox->setCurrentIndex(currentIndex - 1);
    }

    else
    {
        this->ui->secondParentCombobox->setCurrentIndex(this->ui->secondParentCombobox->count() - 1);
    }
}


/* Select the next parent in the secondParentCombobox. */
void ParentSelectionWindow::on_nextSecondParentButton_clicked()
{

    int currentIndex = this->ui->secondParentCombobox->currentIndex();

    if (currentIndex < this->ui->secondParentCombobox->count() - 1)
    {
        this->ui->secondParentCombobox->setCurrentIndex(currentIndex + 1);
    }

    else
    {
        this->ui->secondParentCombobox->setCurrentIndex(0);
    }
}


/* Called when the secondParentCombobox index is changed.
 * ----------
 * int index: the new index of the secondParentCombobox. */
void ParentSelectionWindow::on_secondParentCombobox_currentIndexChanged(int index)
{
    if (this->ui->secondParentCombobox->isEnabled())
    {
        updateSecondParent();
    }
}


//     Others


/* Called when the user select a benefit.
 * ----------
 * QVector<int> benefitID: only 2 values. The first is the parent (0 or 2), and
 * the second is the index of the selected benefit of this parent (0 to 3). In
 * short: {parent, benefit}. */
void ParentSelectionWindow::benefitInteracted(QVector<int> benefitID)
{
    // If the specified checkbox has been checked
    if (parents[benefitID[0]]->benefitCheckboxes[benefitID[1]]->isChecked())
    {
        switch (parents[benefitID[0]]->nbOfBenefit + 1)
        {
        case 1:
            // If it's the first benefit selected, it's all right.
            parents[benefitID[0]]->nbOfBenefit += 1;

            for (int i_box = 0; i_box < parents[benefitID[0]]->tareCheckboxes.length(); i_box++)
            {
                parents[benefitID[0]]->tareCheckboxes[i_box]->setEnabled(true);
            }

            break;

        case 2:
            // If it's the second, all right, but as only 2 benefit per parent can be selected, the other checkboxes are disabled
            parents[benefitID[0]]->nbOfBenefit += 1;

            for (int i_box = 0; i_box < parents[benefitID[0]]->benefitCheckboxes.length(); i_box++)
            {
                if (!parents[benefitID[0]]->benefitCheckboxes[i_box]->isChecked())
                {
                    parents[benefitID[0]]->benefitCheckboxes[i_box]->setEnabled(false);
                }
            }

            break;

        default:
            break;
        }
    }

    // If the specified checkbox has been unchecked
    else
    {
        // Decrement the number of benefits and enable the other checkboxes
        parents[benefitID[0]]->nbOfBenefit -= 1;

        for (int i_box = 0; i_box < parents[benefitID[0]]->benefitCheckboxes.length(); i_box++)
        {
            parents[benefitID[0]]->benefitCheckboxes[i_box]->setEnabled(true);
        }

        if (parents[benefitID[0]]->nbOfBenefit == 0)
        {
            for (int i_box = 0; i_box < parents[benefitID[0]]->tareCheckboxes.length(); i_box++)
            {
                parents[benefitID[0]]->tareCheckboxes[i_box]->setEnabled(false);
                parents[benefitID[0]]->tareCheckboxes[i_box]->setChecked(false);
            }
        }
    }
}


/* Called when the user select a tare.
 * ----------
 * QVector<int> benefitID: only 2 values. The first is the parent (1 or 2), and
 * the second is the index of the selected tare of this parent (1 or 2). */
void ParentSelectionWindow::tareInteracted(QVector<int> tareID)
{
    // If the specified checkbox has been checked
    if (parents[tareID[0]]->tareCheckboxes[tareID[1]]->isChecked())
    {
        switch (parents[tareID[0]]->nbOfTare + 1)
        {
        case 1:
            // If it's the first benefit selected, it's all right, but the other tare box is disable as only one can be selected.
            parents[tareID[0]]->nbOfTare += 1;

            for (int i_box = 0; i_box < parents[tareID[0]]->tareCheckboxes.length(); i_box++)
            {
                if (!parents[tareID[0]]->tareCheckboxes[i_box]->isChecked())
                {
                    parents[tareID[0]]->tareCheckboxes[i_box]->setEnabled(false);
                }
            }
            break;

        default:
            break;
        }
    }

    // If the specified checkbox has been unchecked
    else
    {
        // Decrement the number of benefits and enable the other checkboxes
        parents[tareID[0]]->nbOfTare -= 1;

        for (int i_box = 0; i_box < parents[tareID[0]]->tareCheckboxes.length(); i_box++)
        {
            parents[tareID[0]]->tareCheckboxes[i_box]->setEnabled(true);
        }
    }
}


/* Called when the user click on a ClickableLabel. Request the opening of the
 * encyclopedia for further information.
 * ----------
 * QString category: the encyclopedia category to open.
 * QString element: the element of the category to display. */
void ParentSelectionWindow::requestEncyclopediaOpening(QString category,
                                                       QString element)
{
    qDebug() << category << element;
}


//     %%% Qualities selection %%%


/* Called when the firstCreationBox is interacted with, on the qualities
 * selection page.
 * ----------
 * int arg1: checkbox state. 0 = unchecked ; 2 = checked ; (1 = partially
 * checked but we don't care here). */
void ParentSelectionWindow::on_firstCreationBox_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        this->ui->firstCreationLabel->setStyleSheet("font: normal;");
        this->ui->secondCreationBox->setChecked(false);
        this->ui->secondCreationLabel->setStyleSheet("font: normal;");
    }

    else
    {
        this->ui->firstCreationLabel->setStyleSheet("font: bold;");
        this->ui->secondCreationBox->setChecked(true);
        this->ui->secondCreationLabel->setStyleSheet("font: bold;");
    }
}


/* Called when the firstCreationBox is interacted with, on the qualities
 * selection page.
 * ----------
 * int arg1: checkbox state. 0 = unchecked ; 2 = checked ; (1 = partially
 * checked but we don't care here). */
void ParentSelectionWindow::on_secondCreationBox_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        this->ui->secondCreationLabel->setStyleSheet("font: normal;");
        this->ui->firstCreationBox->setChecked(false);
        this->ui->firstCreationLabel->setStyleSheet("font: normal;");
    }

    else
    {
        this->ui->secondCreationLabel->setStyleSheet("font: bold;");
        this->ui->firstCreationBox->setChecked(true);
        this->ui->firstCreationLabel->setStyleSheet("font: bold;");
    }
}
