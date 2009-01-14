#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>

#include "dicetray.h"
#include "lexicon.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
    void onStartButtonClicked();
    void onTimerCountdown();
    void closeEvent(QCloseEvent* evt);

protected:
    virtual void changeEvent(QEvent *e);

private:
    void startGame();
    void stopGame();
    void enableBlankBoard();
    void resetBoard();

    DiceTray* diceTray;
    Lexicon* lexicon;
    QStringList* foundWords;
    QStringList* wordsNotFound;

    Ui::MainWindow* m_ui;
    bool isGameRunning;
    QTimer* timer;
    int time;
    QThread* wordSearchThread;

    friend class WordSearchThread;
    class WordSearchThread : public QThread
    {
        public:
            WordSearchThread(MainWindow* p) : parent(p) {}
            void run();
        private:
            MainWindow* parent;
    };

};

#endif // MAINWINDOW_H
