#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtGui/QDialog>

#include "dicetray.h"
#include "lexicon.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // TODO: These shouldn't be public
    DiceTray* diceTray;
    Lexicon* lexicon;
    QStringList* foundWords;
    QStringList* wordsNotFound;

public slots:
    void onStartButtonClicked();
    void onTimerCountdown();

protected:
    virtual void changeEvent(QEvent *e);

private:
    void startGame();
    void stopGame();
    void enableBlankBoard();
    void resetBoard();

    Ui::MainWindow *m_ui;
    bool isGameRunning;
    QTimer* timer;
    int time;
};

#endif // MAINWINDOW_H
