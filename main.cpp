#include <QtGui/QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_de", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    application.installTranslator(&qtTranslator);

    QTranslator translator;
    QString locale = QLocale::system().name();

    translator.load("QtBoggle_de");
    application.installTranslator(&translator);

    MainWindow window;
    window.show();

    return application.exec();
}
