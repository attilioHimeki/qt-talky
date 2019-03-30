#include "GraphWidget.h"
#include "EditorWindow.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>

int main(int argc, char **argv)
{

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QCoreApplication::setOrganizationName("Attilio Carotenuto");
    QCoreApplication::setOrganizationDomain("attiliocarotenuto.com");
    QCoreApplication::setApplicationName("Talky");

    QApplication app(argc, argv);

    Q_INIT_RESOURCE(resources);

    EditorWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
