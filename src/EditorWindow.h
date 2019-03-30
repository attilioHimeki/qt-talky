#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include "GraphWidget.h"
#include "SettingsDialog.h"

#include <QMainWindow>
#include <QTranslator>

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = Q_NULLPTR,
                        Qt::WindowFlags flags = 0);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent* event) override;

private:
    const QString defaultLanguage = "en";

    void setupToolBar();
    void setupMenuBar();

    void loadViewSetup();
    void saveViewSetup();
    bool hasOpenedSaveFile();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *aboutMenu;

    GraphWidget* graphWidget;
    QString currentOpenedFilePath;
    bool hasUnsavedChanges;

    SettingsDialog* settingsDialog;

    QTranslator translator;
    QString currentLanguageCode;

private slots:
    bool loadFile();
    bool saveFile();
    bool saveFileAsNew();
    bool maybeSave();
    void aboutTalky();
    void openSettings();

public slots:
    void markFileDirty();
    void markFileNonDirty();
    void changeLanguage(const QString& languageCode);
};

#endif // EDITORWINDOW_H
