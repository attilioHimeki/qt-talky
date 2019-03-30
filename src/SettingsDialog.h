#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

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

signals:
    void languageChanged(const QString& langCode);
};

#endif // SETTINGSDIALOG_H
