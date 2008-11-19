#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QDialog>
#include "dicetray.h"
#include "lexicon.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
    void onStartButtonClicked();

protected:
    virtual void changeEvent(QEvent *e);

private:
    void enableBlankBoard();
    void resetBoard();

    Ui::MainWindow *m_ui;
    bool isGameRunning;
    DiceTray* diceTray;
    Lexicon* lexicon;
    QStringList* foundWords;

};

#endif // MAINWINDOW_H
