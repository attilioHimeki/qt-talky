#include "EditorWindow.h"
#include "GraphWidget.h"
#include "JsonEditorWidget.h"

#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QApplication>
#include <QMessageBox>
#include <QJsonDocument>
#include <QSettings>

#include <QDebug>

EditorWindow::EditorWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");

    setMinimumSize(500, 500);

    centralWidget = new QSplitter(Qt::Horizontal, this);
    graphWidget = new GraphWidget(this);
    jsonEditorWidget = new JsonEditorWidget(this);
    centralWidget->addWidget(graphWidget);
    centralWidget->addWidget(jsonEditorWidget);

    connect(graphWidget, &GraphWidget::contentChanged, this, &EditorWindow::markFileDirty);

    hasUnsavedChanges = false;

    setCentralWidget(centralWidget);

    loadEditorSettings();

    setupToolBar();
    setupMenuBar();
    setupSettingsDialog();

    statusBar()->showMessage(tr("Status Bar"));

    setWindowTitle(QCoreApplication::applicationName());
}

void EditorWindow::setupToolBar()
{
#ifdef Q_OS_OSX
    setUnifiedTitleAndToolBarOnMac(true);
#endif
}

void EditorWindow::setupMenuBar()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    QAction* actionNew = fileMenu->addAction(tr("New script"), this, &EditorWindow::newFile);
    actionNew->setShortcut(QKeySequence::New);

    QAction* actionLoad = fileMenu->addAction(tr("Load script..."), this, &EditorWindow::loadFile);
    actionLoad->setShortcut(QKeySequence::Open);

    QAction *actionSave = fileMenu->addAction(tr("Save script"), this, &EditorWindow::saveFile);
    actionSave->setShortcut(QKeySequence::Save);

    QAction *actionSaveAs = fileMenu->addAction(tr("Save script as..."), this, &EditorWindow::saveFileAsNew);
    actionSaveAs->setShortcut(QKeySequence::SaveAs);

    connect(fileMenu, &QMenu::aboutToShow, [this,actionSave](){
           actionSave->setEnabled(hasOpenedSaveFile());
       });


    editMenu = menuBar()->addMenu(tr("Edit"));

    aboutMenu = menuBar()->addMenu(tr("About"));
    aboutMenu->addAction(tr("About"), this, &EditorWindow::aboutTalky);
    aboutMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);

    QAction *actionOpenPrefs = aboutMenu->addAction(tr("Preferences"), this, &EditorWindow::openSettings);
    actionOpenPrefs->setMenuRole(QAction::PreferencesRole);
    actionOpenPrefs->setShortcut(QKeySequence::Preferences);

}

void EditorWindow::setupSettingsDialog()
{
    settingsDialog = new SettingsDialog(this);
    connect(settingsDialog, &SettingsDialog::languageChanged, this, &EditorWindow::changeLanguage);
    connect(this, &EditorWindow::appLanguageChanged, settingsDialog, &SettingsDialog::retranslate);
}

bool EditorWindow::newFile()
{
    if(maybeSave())
    {
        currentOpenedFilePath = QString();

        setWindowTitle(QCoreApplication::applicationName());

        graphWidget->applyNewTree();

        markFileNonDirty();

        return true;
    }

    return false;
}

bool EditorWindow::loadFile()
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR,
                tr("Open Dialog Tree"), "",
                tr("Dialogue Tree (*.json);;All Files (*)"));


        QFile currentLoadFile(fileName);

        if (!currentLoadFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open save file.");
            return false;
        }

        currentOpenedFilePath = fileName;

        QByteArray saveData = currentLoadFile.readAll();

        QString text = QString("%1 - %2").arg(QCoreApplication::applicationName(), fileName);
        setWindowTitle(text);

        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        if(loadDoc.isNull())
        {
            QMessageBox::warning(this, tr("Talky"),
                                 tr("The Json document is not valid"),
                                 QMessageBox::Ok);
            return false;
        }
        else if(loadDoc.isEmpty())
        {
            QMessageBox::warning(this, tr("Talky"),
                                 tr("The Json document is empty"),
                                 QMessageBox::Ok);
            return false;
        }

        QJsonObject jsonObject = loadDoc.object();

        graphWidget->applyLoadedTreeJsonFile(jsonObject);
        jsonEditorWidget->refresh(loadDoc);

        currentLoadFile.close();

        markFileNonDirty();

        return true;
    }

    return false;
}

bool EditorWindow::saveFile()
{
    auto data = graphWidget->serialiseLoadedTree();

    QFile currentLoadFile(currentOpenedFilePath);

    if (!currentLoadFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonDocument saveDoc(data);
    currentLoadFile.write(saveDoc.toJson());

    currentLoadFile.flush();
    currentLoadFile.close();

    markFileNonDirty();

    QJsonObject jsonObject = saveDoc.object();
    jsonEditorWidget->refresh(saveDoc);

    return true;
}

bool EditorWindow::saveFileAsNew()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    QString fileName = dialog.getSaveFileName(this, tr("Create New File"),"","JSON (*.json)");

    currentOpenedFilePath = fileName;

    bool saved = saveFile();
    if(saved)
    {
        QString text = QString("%1 - %2").arg(QCoreApplication::applicationName(), fileName);
        setWindowTitle(text);

        markFileNonDirty();
    }

    return saved;
}

bool EditorWindow::maybeSave()
{
    if (!hasUnsavedChanges)
    {
        return true;
    }
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Unsaved Changes"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret)
    {
        case QMessageBox::Save:
        {
            if(hasOpenedSaveFile())
            {
                return saveFile();
            }
            else
            {
                return saveFileAsNew();
            }
        }
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

void EditorWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
}

void EditorWindow::closeEvent(QCloseEvent* event)
{
    if (maybeSave())
    {
        saveEditorSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void EditorWindow::loadEditorSettings()
{
    QSettings settings;

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(500, 500)).toSize();
    QByteArray state = settings.value("state", QByteArray()).toByteArray();
    restoreState(state);
    resize(size);
    move(pos);

    QString lang = settings.value("lang", defaultLanguage).toString();
    changeLanguage(lang);
}

void EditorWindow::saveEditorSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("state", saveState());
    settings.setValue("lang", currentLanguageCode);
}

bool EditorWindow::hasOpenedSaveFile()
{
    return !currentOpenedFilePath.isNull() && !currentOpenedFilePath.isEmpty();
}

void EditorWindow::markFileDirty()
{
    hasUnsavedChanges = true;
    setWindowModified(true);
}

void EditorWindow::markFileNonDirty()
{
    hasUnsavedChanges = false;
    setWindowModified(false);
}

void EditorWindow::aboutTalky()
{
    QMessageBox::about(this, tr("About Talky"),
                tr("<b>Talky</b> is a node based editor "
                   "to design dialogues and character interactions "
                   "for games."));
}

void EditorWindow::openSettings()
{
    settingsDialog->open();
}

void EditorWindow::changeLanguage(const QString& languageCode)
{
    qApp->removeTranslator(&translator);

    QString resourceFileName = QString(":/languages/talky_%1.qm").arg(languageCode);

    if (translator.load(resourceFileName))
    {
         qApp->installTranslator(&translator);

         currentLanguageCode = languageCode;

         emit appLanguageChanged(languageCode);
    }
    else
    {
        qWarning() << QString("Couldn't find translation file for language %1.").arg(languageCode);
    }
}
