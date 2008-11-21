#ifndef WORDSEARCHTHREAD_H
#define WORDSEARCHTHREAD_H

#include <QThread>

#include "mainwindow.h"

class WordSearchThread : public QThread
{
    public:
        WordSearchThread(MainWindow* parent);

        void run();

    private:
        MainWindow* main;
};

#endif // WORDSEARCHTHREAD_H
