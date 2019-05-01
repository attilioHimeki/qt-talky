#include "SettingsGeneralTab.h"

#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QSettings>

SettingsGeneralTab::SettingsGeneralTab(QWidget *parent)
    : QWidget(parent)
{
    enableAutosaveCheckBox = new QCheckBox(tr("Enable auto-save"), this);
    connect(enableAutosaveCheckBox, &QCheckBox::toggled, this, &SettingsGeneralTab::onEnableAutosaveToggled);

    autosaveIntervalLabel = new QLabel(tr("Auto-save interval (minutes):"), this);
    autosaveIntervalLabel->setVisible(enableAutosaveCheckBox->isChecked());

    autosaveIntervalField = new QLineEdit("10", this);
    autosaveIntervalField->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*)|([0])$")));
    autosaveIntervalField->setVisible(enableAutosaveCheckBox->isChecked());
    connect(autosaveIntervalField, &QLineEdit::textChanged, this, &SettingsGeneralTab::onAutosaveIntervalChanged);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(enableAutosaveCheckBox);
    mainLayout->addWidget(autosaveIntervalLabel);
    mainLayout->addWidget(autosaveIntervalField);

    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(enableAutosaveCheckBox, &QCheckBox::toggled, [this](bool checked){
           autosaveIntervalField->setVisible(checked);
           autosaveIntervalLabel->setVisible(checked);
       });
}

void SettingsGeneralTab::retranslate()
{
    enableAutosaveCheckBox->setText(tr("Enable auto-save"));
    autosaveIntervalLabel->setText(tr("Auto-save interval:"));
}

void SettingsGeneralTab::onEnableAutosaveToggled(bool checked)
{
    refreshAutosave();
}

void SettingsGeneralTab::onAutosaveIntervalChanged(const QString& key)
{
    refreshAutosave();
}

void SettingsGeneralTab::refreshAutosave()
{
    int intervalMinutes = autosaveIntervalField->text().toInt();
    bool enabled = enableAutosaveCheckBox->isChecked() && intervalMinutes > 0;

    QSettings settings;
    settings.setValue("autosave", enabled);
    settings.setValue("autosaveInterval", intervalMinutes);

    emit enableAutosaveChanged(enabled, intervalMinutes);
}
