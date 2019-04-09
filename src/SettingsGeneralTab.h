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

public slots:
    void retranslate();
};

#endif // SETTINGSGENERALTAB_H
