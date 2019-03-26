#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include "GraphWidget.h"

#include <QMainWindow>

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

private slots:
    bool loadFile();
    bool saveFile();
    bool saveFileAsNew();
    bool maybeSave();
    void aboutTalky();

public slots:
    void markFileDirty();
    void markFileNonDirty();
};

#endif // EDITORWINDOW_H
