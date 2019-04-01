#include "SettingsLanguageTab.h"
#include "EditorWindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QRadioButton>

SettingsLanguageTab::SettingsLanguageTab(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout;
    languagesGroupBox = new QGroupBox(tr("Choose Language"));

    QRadioButton *enRadioButton = new QRadioButton("English");
    QRadioButton *itRadioButton = new QRadioButton("Italian");
    QRadioButton *ptRadioButton = new QRadioButton("Portuguese");

    connect(enRadioButton, &QRadioButton::toggled, this, &SettingsLanguageTab::onEnglishLanguageToggled);
    connect(itRadioButton, &QRadioButton::toggled, this, &SettingsLanguageTab::onItalianLanguageToggled);
    connect(ptRadioButton, &QRadioButton::toggled, this, &SettingsLanguageTab::onPortugueseLanguageToggled);

    enRadioButton->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(enRadioButton);
    vbox->addWidget(itRadioButton);
    vbox->addWidget(ptRadioButton);
    vbox->addStretch(1);
    languagesGroupBox->setLayout(vbox);

    grid->addWidget(languagesGroupBox, 0, 0);
    setLayout(grid);
}

void SettingsLanguageTab::onEnglishLanguageToggled(bool checked)
{
    if(checked)
        emit languageChanged("en");
}

void SettingsLanguageTab::onItalianLanguageToggled(bool checked)
{
    if(checked)
        emit languageChanged("it");
}

void SettingsLanguageTab::onPortugueseLanguageToggled(bool checked)
{
    if(checked)
        emit languageChanged("pt");
}
