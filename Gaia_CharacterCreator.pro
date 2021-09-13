QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddPowerAddonWindow.cpp \
    AddPowerWindow.cpp \
    ButtonID.cpp \
    Character.cpp \
    CheckboxID.cpp \
    ClickableLabel.cpp \
    CreateNewPowerWindow.cpp \
    DataManager.cpp \
    EncyclopediaWindow.cpp \
    GodsData.cpp \
    ParentSelectionWindow.cpp \
    PowersData.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    AddPowerAddonWindow.h \
    AddPowerWindow.h \
    ButtonID.h \
    Character.h \
    CheckboxID.h \
    ClickableLabel.h \
    CreateNewPowerWindow.h \
    DataManager.h \
    EncyclopediaWindow.h \
    GodsData.h \
    MainWindow.h \
    ParentSelectionWindow.h \
    PowersData.h

FORMS += \
    AddPowerAddonWindow.ui \
    AddPowerWindow.ui \
    CreateNewPowerWindow.ui \
    EncyclopediaWindow.ui \
    MainWindow.ui \
    ParentSelectionWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resources/Data/Gods.json \
    Resources/Data/PowerAddons.json \
    Resources/Data/Powers.json \
    Resources/Data/Qualities.json \
