#include "SettingsLanguageTab.h"
#include "EditorWindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QSettings>
#include <QLocale>

SettingsLanguageTab::SettingsLanguageTab(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout;
    languagesGroupBox = new QGroupBox(tr("Choose Language"), this);

    enRadioButton = new QRadioButton("English", this);
    itRadioButton = new QRadioButton("Italiano", this);
    ptRadioButton = new QRadioButton("Portugûes", this);

    connect(enRadioButton, &QRadioButton::toggled, this, &SettingsLanguageTab::onEnglishLanguageToggled);
    connect(itRadioButton, &QRadioButton::toggled, this, &SettingsLanguageTab::onItalianLanguageToggled);
    connect(ptRadioButton, &QRadioButton::toggled, this, &SettingsLanguageTab::onPortugueseLanguageToggled);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(enRadioButton);
    vbox->addWidget(itRadioButton);
    vbox->addWidget(ptRadioButton);
    vbox->addStretch(1);
    languagesGroupBox->setLayout(vbox);

    grid->addWidget(languagesGroupBox, 0, 0);
    setLayout(grid);

    refreshActiveSettings();
}

void SettingsLanguageTab::refreshActiveSettings()
{
    QSettings settings;
    auto currentLang = settings.value("lang").toString();

    enRadioButton->setChecked(currentLang == "en");
    itRadioButton->setChecked(currentLang == "it");
    ptRadioButton->setChecked(currentLang == "pt");
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

void SettingsLanguageTab::retranslate()
{
    languagesGroupBox->setTitle(tr("Choose Language"));
}

