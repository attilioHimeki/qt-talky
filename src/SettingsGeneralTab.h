#ifndef SETTINGSGENERALTAB_H
#define SETTINGSGENERALTAB_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

class SettingsGeneralTab : public QWidget
{
     Q_OBJECT
public:
    explicit SettingsGeneralTab(QWidget *parent = 0);

private:
    QCheckBox* enableAutosaveCheckBox;
    QLabel* autosaveIntervalLabel;
    QLineEdit* autosaveIntervalField;

    void refreshAutosave();

private slots:
    void onEnableAutosaveToggled(bool checked);
    void onAutosaveIntervalChanged(const QString& key);

public slots:
    void retranslate();

signals:
    void enableAutosaveChanged(bool enabled, int intervalMinutes);
};

#endif // SETTINGSGENERALTAB_H
