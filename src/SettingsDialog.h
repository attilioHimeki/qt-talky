#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "SettingsGeneralTab.h"
#include "SettingsLanguageTab.h"

#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

    SettingsLanguageTab* languagesTab;
    SettingsGeneralTab* generalTab;

public slots:
    void retranslate();

signals:
    void languageChanged(const QString& langCode);
};

#endif // SETTINGSDIALOG_H
