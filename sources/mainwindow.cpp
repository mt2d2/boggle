#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QDialog(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    // Set up the pieces layout manually
    // This cuts down on the huge amounts of redundant code
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            QLabel* label = new QLabel("_");
            label->setFont(QFont("", 18, QFont::Bold));
            label->setAlignment(Qt::AlignCenter);

            this->ui->piecesLayout->addWidget(label, i, j);
        }
    }

    // Setup instance fields
    this->isGameRunning = false;
    this->timer = new QTimer(this);
    this->time = 0;
    this->correctWords = new QStringList();
    this->incorrectWords = new QStringList();
    this->wordsNotFound = new QStringList();
    this->diceTray = NULL;
    this->lexicon = new Lexicon(":/dictionary.txt");
    this->wordSearchThread = new WordSearchThread(this);

    // Make custom connections
    QObject::connect(ui->startButton, SIGNAL(clicked()), SLOT(onStartButtonClicked()));
    QObject::connect(this->timer, SIGNAL(timeout()), SLOT(onTimerCountdown()));
}

void MainWindow::closeEvent(QCloseEvent* evt)
{
    if (this->wordSearchThread != NULL && this->wordSearchThread->isRunning())
    {
        // This waits for the thread to finish its execution
        // Ideally, we would exit straight away, but this CRASHES
        this->wordSearchThread->wait();
    }

    evt->accept();
}

MainWindow::~MainWindow()
{
    delete this->correctWords;
    delete this->incorrectWords;
    delete this->wordsNotFound;
    delete this->wordSearchThread;
    delete this->lexicon;
    delete this->timer;
    delete this->ui;

    // The dice tray is destroyed when the game stops, but delete it just in case the
    // user decides to quit before the game is stopped
    if (this->diceTray != NULL)
        delete this->diceTray;
}

void MainWindow::changeEvent(QEvent *e)
{
    switch(e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::startGame()
{
    isGameRunning = !isGameRunning;

    // Start the game!
    this->newBoard();
    this->time = 180; // 180 (3 minutes)
    this->timer->start(1000);
}

void MainWindow::stopGame()
{
    isGameRunning = !isGameRunning;

    // Let the wordSearcherThread finish
    if (this->wordSearchThread != NULL && this->wordSearchThread->isRunning())
        this->wordSearchThread->wait();

    // Stop
    this->timer->stop();

    QStringList enteredWords = this->ui->wordEdit->toPlainText().simplified().split(" ");

    if (enteredWords.at(0) != "")
    {
        for (int i = 0; i < enteredWords.size(); i++)
        {
            QString wordToTest = enteredWords.at(i);

            if  (this->diceTray->stringFound(wordToTest) && this->lexicon->hasWord(wordToTest) && wordToTest.length() > 2)
                this->correctWords->append(wordToTest);
            else
               this->incorrectWords->append(wordToTest);
        }
    }
    // Remove all correctly found words
    for (int i = 0; i < this->correctWords->size(); i++)
        this->wordsNotFound->removeAll(this->correctWords->at(i));

    QMessageBox msgBox(this);
    msgBox.setText(tr("Score: %1\nValid words: %2\nInvalid Words: %3\n\nWords not found: %4").arg(this->computeWordScore()).arg(this->correctWords->join(", ")).arg(this->incorrectWords->join(", ")).arg(this->wordsNotFound->join(", ")));
    msgBox.exec();

    this->resetBoard();
}

void MainWindow::onStartButtonClicked()
{
    if (isGameRunning)
        this->stopGame();
    else
        this->startGame();
}

void MainWindow::newBoard()
{
    // Start the timer
    this->ui->gameStatus->setText(QString(tr("Time remaining: %1")).arg("3:00"));

    // Change the start button
    this->ui->startButton->setText(tr("Stop"));

    // Empty and enable the entry field
    this->ui->wordEdit->setPlainText("");
    this->ui->wordEdit->setEnabled(true);
    this->ui->wordEdit->setFocus();

    // Label each game piece from diceTray
    this->diceTray = new DiceTray();
    Die* (*pieces)[4][4] = this->diceTray->getTray();

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            (dynamic_cast<QLabel*>(this->ui->piecesLayout->itemAtPosition(i, j)->widget()))->setText(QString((*pieces)[i][j]->getLetter()));

    // Start searching for words
    this->wordSearchThread->start();
}

void MainWindow::resetBoard()
{
    // Reset the scores
    this->correctWords->clear();
    this->incorrectWords->clear();
    this->wordsNotFound->clear();

    // Delete the old tray
    delete this->diceTray;
    this->diceTray = NULL;

    this->ui->gameStatus->setText(QString("<font color=\"black\">%1</font>").arg(tr("Press Start to begin the game...")));

    // Change the start button
    this->ui->startButton->setText(tr("Start"));

    // Empty and enable the entry field
    this->ui->wordEdit->setPlainText(tr("Enter words seperated by one space..."));
    this->ui->wordEdit->setEnabled(false);
    this->ui->startButton->setFocus();

    // Reset all the letters
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            (dynamic_cast<QLabel*>(this->ui->piecesLayout->itemAtPosition(i, j)->widget()))->setText("_");
}

void MainWindow::onTimerCountdown()
{
    if (this->time == 0)
        return this->stopGame();

    this->time--;

    QString minutes = QString("%1").arg((time / 60));
    QString seconds = (time % 60 == 0) ? "00" :  (time % 60 < 10) ? QString("0%1").arg(time % 60) : QString("%1").arg(time % 60);

    this->ui->gameStatus->setText(QString(tr("Time remaining: %1")).arg(minutes + ":" + seconds ));

    if (this->time <= 60)
        this->ui->gameStatus->setText(QString("<font color=\"red\">%1</font>").arg(this->ui->gameStatus->text()));
}

void MainWindow::WordSearchThread::run()
{
//    QTime time;
//    time.start();

    for (int i = 0; i < parent->lexicon->dictionary->size(); i++)
    {
        const QString& word = parent->lexicon->dictionary->at(i);

        if (parent->diceTray->stringFound(word))
            parent->wordsNotFound->append(word);
    }

//    qDebug() << "Total: " << (time.elapsed()) << " ms";
}

int MainWindow::computeWordScore()
{
    int score = 0;

    for (int i = 0; i < this->correctWords->size(); i++)
    {
        if (this->correctWords->at(i).length() <= 4)
            score += 1;
        else if (this->correctWords->at(i).length() == 5)
            score += 2;
        else if (this->correctWords->at(i).length() == 6)
            score += 3;
        else if (this->correctWords->at(i).length() >= 7 && this->correctWords->at(i).length() <= 10)
            score += 5;
        else if (this->correctWords->at(i).length() >= 11)
            score += 8;
    }

    for (int i = 0; i < this->incorrectWords->size(); i++)
    {
        if (this->incorrectWords->at(i).length() <= 4)
            score -= 1;
        else if (this->incorrectWords->at(i).length() == 5)
            score -= 2;
        else if (this->incorrectWords->at(i).length() == 6)
            score -= 3;
        else if (this->incorrectWords->at(i).length() >= 7 && this->incorrectWords->at(i).length() <= 10)
            score -= 5;
        else if (this->incorrectWords->at(i).length() >= 11)
            score -= 8;
    }

    return score;
}
