#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include "GraphWidget.h"
#include "JsonEditorWidget.h"
#include "SettingsDialog.h"

#include <QMainWindow>
#include <QTranslator>
#include <QSplitter>

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
    void setupSettingsDialog();
    void setupTimers();

    void loadEditorSettings();
    void saveEditorSettings();
    bool hasOpenedSaveFile();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *aboutMenu;

    QSplitter* centralWidget;
    GraphWidget* graphWidget;
    JsonEditorWidget* jsonEditorWidget;

    QString currentOpenedFilePath;
    bool hasUnsavedChanges;

    SettingsDialog* settingsDialog;

    QTranslator translator;
    QString currentLanguageCode;

    QTimer* autosaveTimer;

private slots:
    bool newFile();
    bool loadFile();
    bool saveFile();
    bool saveFileAsNew();
    bool maybeSave();
    void autosave();
    void aboutTalky();
    void openSettings();

public slots:
    void markFileDirty();
    void markFileNonDirty();
    void changeLanguage(const QString& languageCode);
    void setupAutosave(bool enabled, int intervalMinutes);

    void refreshJsonView();

signals:
    void appLanguageChanged(const QString& langCode);
};

#endif // EDITORWINDOW_H
