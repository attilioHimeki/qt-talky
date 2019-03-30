#ifndef SETTINGSLANGUAGETAB_H
#define SETTINGSLANGUAGETAB_H

#include <QWidget>
#include <QGroupBox>
#include <QButtonGroup>

class SettingsLanguageTab : public QWidget
{
     Q_OBJECT
public:
    explicit SettingsLanguageTab(QWidget *parent = 0);

private:
    QGroupBox* createLanguagesGroup();

private slots:
    void onEnglishLanguageToggled(bool checked);
    void onItalianLanguageToggled(bool checked);
    void onPortugueseLanguageToggled(bool checked);

signals:
    void languageChanged(const QString& langCode);
};

#endif // SETTINGSLANGUAGETAB_H
