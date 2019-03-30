#include "SettingsGeneralTab.h"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>

SettingsGeneralTab::SettingsGeneralTab(QWidget *parent)
    : QWidget(parent)
{
    QCheckBox *enableAutosaveCheckBox = new QCheckBox(tr("Enable auto-save"));

    QLabel *autosaveIntervalLabel = new QLabel(tr("Auto-save interval:"));
    autosaveIntervalLabel->setVisible(enableAutosaveCheckBox->isChecked());
    QLineEdit *autosaveIntervalField = new QLineEdit("0");
    autosaveIntervalField->setVisible(enableAutosaveCheckBox->isChecked());

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(enableAutosaveCheckBox);
    mainLayout->addWidget(autosaveIntervalLabel);
    mainLayout->addWidget(autosaveIntervalField);

    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(enableAutosaveCheckBox, &QCheckBox::toggled, [this,autosaveIntervalField, autosaveIntervalLabel](bool checked){
           autosaveIntervalField->setVisible(checked);
           autosaveIntervalLabel->setVisible(checked);
       });
}
