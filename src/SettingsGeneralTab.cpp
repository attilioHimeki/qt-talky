#include "SettingsGeneralTab.h"

#include <QVBoxLayout>
#include <QRegExpValidator>

SettingsGeneralTab::SettingsGeneralTab(QWidget *parent)
    : QWidget(parent)
{
    enableAutosaveCheckBox = new QCheckBox(tr("Enable auto-save"), this);

    autosaveIntervalLabel = new QLabel(tr("Auto-save interval:"), this);
    autosaveIntervalLabel->setVisible(enableAutosaveCheckBox->isChecked());

    autosaveIntervalField = new QLineEdit("0", this);
    autosaveIntervalField->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*)|([0])$")));
    autosaveIntervalField->setVisible(enableAutosaveCheckBox->isChecked());

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
