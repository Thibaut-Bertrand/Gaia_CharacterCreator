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

#ifndef PARENTSELECTIONWINDOW_H
#define PARENTSELECTIONWINDOW_H


#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>


#include "Character.h"
#include "CheckboxID.h"
#include "ClickableLabel.h"
#include "GodsData.h"


namespace Ui {
class ParentSelectionWindow;
}


class ParentSelectionWindow : public QDialog
{
    Q_OBJECT


    struct Parent
    {
        bool isActive = false;

        int index = 0;
        QVector<CheckboxID*> benefitCheckboxes; // IDs: parent index | box index | benefit index
        int nbOfBenefit = 0;
        QVector<CheckboxID*> tareCheckboxes; // IDs: parent index | box index | tare index
        int nbOfTare = 0;
    };


public:

    explicit ParentSelectionWindow(GodsData* data, QWidget *parent = nullptr);
    ~ParentSelectionWindow();


private:

    // Methods
    // ----------

    // --- Parent selection page UI

    // Parent selection
    void enableCheckboxes(QVector<CheckboxID*> checkboxesToEnable);
    void disableCheckboxes(QVector<CheckboxID*> checkboxesToDisable);
    void setGodBasicData(QVBoxLayout* layout, int parentNumber);
    QVector<CheckboxID*> setGodBenefits(QVBoxLayout* layout, int parentNumber);
    QVector<CheckboxID*> setGodTares(QVBoxLayout* layout, int parentNumber);


    // First parent
    void updateFirstParent();


    // Second parent
    void disableSecondParent();
    void updateSecondParent();


    // --- Qualities selection page UI
    void setDetailledQualities(QVBoxLayout* layout, int parentNumber,
                               int qualityIndex);
    void updateQualitiesLayout(QVBoxLayout* layout, int parentNumber);
    void updateQualitiesSelectionPage();


    // --- Utilities
    bool checkBenefits(int parent);
    bool checkTares(int parent);
    void clearLayout(QLayout* layout);
    int getGodIndex(QString godName);
    QVector<bool> getParentLegitimacy();
    void resetParent (Parent* parentToReset);
    int validateParentSelection();


    // Members
    // ----------

    Ui::ParentSelectionWindow *ui;

    bool isOnParentSelectionPage = true;

    Character* character;
    GodsData* godsData;


    // --- Parents
    QVector<Parent*> parents = {new Parent, new Parent};


    // Specific to the first
    bool areParentVirgin = false; // Cause if first is, and a second one is picked, then the second is a virgin too.
    CheckboxID* secondParentCheckbox;
    QCheckBox* monoparentalCheckbox;
    QVector<QString> availableSecondParent;


private slots:

    // --- Utilities
    void on_encyclopediaButton_clicked();
    void on_helpButton_clicked();
    void on_previousButton_clicked();
    void on_okButton_clicked();
    void on_cancelButton_clicked();


    // --- Parent selection

    // First parent
    void on_previousFirstParentButton_clicked();
    void on_nextFirstParentButton_clicked();
    void on_firstParentCombobox_currentIndexChanged(int index);

    void secondParentChecked(int godIndex);
    void monoparentalChecked(int state);


    // Second parent
    void on_previousSecondParentButton_clicked();
    void on_nextSecondParentButton_clicked();
    void on_secondParentCombobox_currentIndexChanged(int index);


    // Others
    void benefitInteracted(QVector<int> benefitID);
    void tareInteracted(QVector<int> tareID);
    void requestEncyclopediaOpening(QString category, QString element);


    // --- Qualities Selection
    void on_firstCreationBox_stateChanged(int arg1);
    void on_secondCreationBox_stateChanged(int arg1);


signals:

    void openEncyclopedia();
    void createCharacter();
};

#endif // PARENTSELECTIONWINDOW_H
