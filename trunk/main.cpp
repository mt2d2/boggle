#include <QtGui/QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Translate both Qt and the application
    // These translations may move in the future to a seperate directory
    QString locale = application.desktop()->locale().name();
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    application.installTranslator(&qtTranslator);
    QTranslator appTranslator;
    appTranslator.load("QtBoggle_" + locale);
    application.installTranslator(&appTranslator);

    MainWindow window;
    window.show();

    return application.exec();
}
