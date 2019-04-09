#include "SettingsDialog.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialogButtonBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    tabWidget = new QTabWidget(this);

    generalTab = new SettingsGeneralTab(this);
    tabWidget->addTab(generalTab, tr("General"));

    languagesTab = new SettingsLanguageTab(this);
    tabWidget->addTab(languagesTab, tr("Language"));
    connect(languagesTab, &SettingsLanguageTab::languageChanged, this, &SettingsDialog::languageChanged);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setFixedSize(600, 300);

    setWindowTitle(tr("Preferences"));
}

void SettingsDialog::retranslate()
{
    tabWidget->setTabText(0, tr("General"));
    tabWidget->setTabText(1, tr("Language"));

    languagesTab->retranslate();
    generalTab->retranslate();

    setWindowTitle(tr("Preferences"));
}
