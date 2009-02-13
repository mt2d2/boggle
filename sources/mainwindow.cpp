#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QDialog(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    // Set up the pieces layout manually
    // This cuts down on the huge amounts of redundant code
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            QLabel* label = new QLabel("_");
            label->setFont(QFont("", 18, QFont::Bold));
            label->setAlignment(Qt::AlignCenter);

            this->m_ui->piecesLayout->addWidget(label, i, j);
        }
    }

    // Setup instance fields
    this->isGameRunning = false;
    this->timer = new QTimer(this);
    this->time = 0;
    this->foundWords = new QStringList();
    this->wordsNotFound = new QStringList();
    this->diceTray = NULL;
    this->lexicon = new Lexicon(":/dictionary.txt");
    this->wordSearchThread = new WordSearchThread(this);

    // Make custom connections
    QObject::connect(m_ui->startButton, SIGNAL(clicked()), SLOT(onStartButtonClicked()));
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
    delete this->foundWords;
    delete this->wordsNotFound;
    delete this->wordSearchThread;
    delete this->lexicon;
    delete this->timer;
    delete this->m_ui;

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
            m_ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::startGame()
{
    isGameRunning = !isGameRunning;

    // Start the game!
    this->enableBlankBoard();
    this->time = 180;   // 180 (3 minutes)
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

    QStringList enteredWords = this->m_ui->wordEdit->toPlainText().split(" ");
    if (enteredWords.at(0) != "")
    {
        for (int i = 0; i < enteredWords.size(); i++)
        {
            QString wordToTest = enteredWords.at(i);
            if  (this->diceTray->stringFound(wordToTest) && this->lexicon->hasWord(wordToTest) && wordToTest.length() > 2)
                this->foundWords->append(wordToTest);
        }
    }

     // Remove all correctly found words
    for (int i = 0; i < this->foundWords->size(); i++)
        this->wordsNotFound->removeAll(this->foundWords->at(i));

    QMessageBox msgBox(this);
    msgBox.setText(tr("Vald words: %1\nWords not found: %2").arg(this->foundWords->join(", ")).arg(this->wordsNotFound->join(", ")));
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

void MainWindow::enableBlankBoard()
{
    // Start the timer
    m_ui->gameStatus->setText(QString(tr("Time remaining: %1")).arg("3:00"));

    // Change the start button
    m_ui->startButton->setText(tr("Stop"));

    // Empty and enable the entry field
    m_ui->wordEdit->setPlainText("");
    m_ui->wordEdit->setEnabled(true);
    m_ui->wordEdit->setFocus();

    // Label each game piece from diceTray
    this->diceTray = new DiceTray();
    QList<QList<Die*>*>* pieces = this->diceTray->getTray();

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            (dynamic_cast<QLabel*>(this->m_ui->piecesLayout->itemAtPosition(i, j)->widget()))->setText(QString(pieces->at(i)->at(j)->getLetter()));

    // Start searching for words
    this->wordSearchThread->start();
}

void MainWindow::resetBoard()
{
    // Reset the scores
    this->foundWords->clear();
    this->wordsNotFound->clear();

    // Delete the old tray
    delete this->diceTray;
    this->diceTray = NULL;

    this->m_ui->gameStatus->setText(QString("<font color=\"black\">%1</font>").arg(tr("Press Start to begin the game...")));

    // Change the start button
    m_ui->startButton->setText(tr("Start"));

    // Empty and enable the entry field
    m_ui->wordEdit->setPlainText(tr("Enter words seperated by one space..."));
    m_ui->wordEdit->setEnabled(false);
     m_ui->startButton->setFocus();

    // Reset all the letters
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            (dynamic_cast<QLabel*>(this->m_ui->piecesLayout->itemAtPosition(i, j)->widget()))->setText("_");
}

void MainWindow::onTimerCountdown()
{
    if (this->time == 0)
        return this->stopGame();

    this->time--;

    QString minutes = QString("%1").arg((time / 60));
    QString seconds = (time % 60 == 0) ? "00" :  (time % 60 < 10) ? QString("0%1").arg(time % 60) : QString("%1").arg(time % 60);

    this->m_ui->gameStatus->setText(QString(tr("Time remaining: %1")).arg(minutes + ":" + seconds ));

    if (this->time <= 60)
        this->m_ui->gameStatus->setText(QString("<font color=\"red\">%1</font>").arg(this->m_ui->gameStatus->text()));
}

void MainWindow::WordSearchThread::run()
{
    for (int i = 0; i < parent->lexicon->dictionary->size(); i++)
    {
        QString word = parent->lexicon->dictionary->at(i);

        if (parent->diceTray->stringFound(word))
            parent->wordsNotFound->append(word);
    }
}
