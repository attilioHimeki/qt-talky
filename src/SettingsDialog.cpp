#include "SettingsDialog.h"
#include "SettingsGeneralTab.h"
#include "SettingsLanguageTab.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialogButtonBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(new SettingsGeneralTab(this), tr("General"));

    auto languagesTab = new SettingsLanguageTab(this);
    tabWidget->addTab(languagesTab, tr("Language"));
    connect(languagesTab, &SettingsLanguageTab::languageChanged, this, &SettingsDialog::languageChanged);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setFixedSize(600, 300);

    setWindowTitle(tr("Preferences"));
}
