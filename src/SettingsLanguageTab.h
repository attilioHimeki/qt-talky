#ifndef SETTINGSLANGUAGETAB_H
#define SETTINGSLANGUAGETAB_H

#include <QWidget>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>

class SettingsLanguageTab : public QWidget
{
     Q_OBJECT
public:
    explicit SettingsLanguageTab(QWidget *parent = 0);

private:
    QGroupBox* languagesGroupBox;
    QRadioButton *enRadioButton;
    QRadioButton *itRadioButton;
    QRadioButton *ptRadioButton;

private slots:
    void refreshActiveSettings();
    void onEnglishLanguageToggled(bool checked);
    void onItalianLanguageToggled(bool checked);
    void onPortugueseLanguageToggled(bool checked);

public slots:
    void retranslate();

signals:
    void languageChanged(const QString& langCode);
};

#endif // SETTINGSLANGUAGETAB_H
