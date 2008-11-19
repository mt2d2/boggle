#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    // Make custom connections
    QObject::connect(m_ui->startButton, SIGNAL(clicked()), SLOT(onStartButtonClicked()));

    // Setup instance fields
    this->foundWords = new QStringList();
    this->lexicon = new Lexicon("dictionary.txt");
    this->isGameRunning = false;
    this->diceTray = NULL;
}

MainWindow::~MainWindow()
{
    delete this->diceTray;
    delete this->m_ui;
    delete this->foundWords;
    delete this->lexicon;
}

void MainWindow::changeEvent(QEvent *e)
{
    switch(e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::onStartButtonClicked()
{
    if (isGameRunning)
    {
        // Stop
        QStringList enteredWords = this->m_ui->wordEdit->toPlainText().split(" ");

        if (enteredWords.at(0) != "")
        {
            for (int i = 0; i < enteredWords.size(); i++)
            {
                QString wordToTest = enteredWords.at(i);

                if  (this->diceTray->stringFound(wordToTest) && this->lexicon->hasWord(wordToTest))
                    this->foundWords->append(wordToTest);
            }

            QMessageBox msgBox;
            msgBox.setText("Valid words: " + this->foundWords->join(" "));
            msgBox.exec();
        }
        this->resetBoard();
    }
    else
    {
        // Start the game!
        this->enableBlankBoard();
    }

    isGameRunning = !isGameRunning;
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

    m_ui->letter1->setText(QString(pieces->at(0)->at(0)->getLetter()));
    m_ui->letter2->setText(QString(pieces->at(0)->at(1)->getLetter()));
    m_ui->letter3->setText(QString(pieces->at(0)->at(2)->getLetter()));
    m_ui->letter4->setText(QString(pieces->at(0)->at(3)->getLetter()));

    m_ui->letter5->setText(QString(pieces->at(1)->at(0)->getLetter()));
    m_ui->letter6->setText(QString(pieces->at(1)->at(1)->getLetter()));
    m_ui->letter7->setText(QString(pieces->at(1)->at(2)->getLetter()));
    m_ui->letter8->setText(QString(pieces->at(1)->at(3)->getLetter()));

    m_ui->letter9->setText(QString(pieces->at(2)->at(0)->getLetter()));
    m_ui->letter10->setText(QString(pieces->at(2)->at(1)->getLetter()));
    m_ui->letter11->setText(QString(pieces->at(2)->at(2)->getLetter()));
    m_ui->letter12->setText(QString(pieces->at(2)->at(3)->getLetter()));

    m_ui->letter13->setText(QString(pieces->at(3)->at(0)->getLetter()));
    m_ui->letter14->setText(QString(pieces->at(3)->at(1)->getLetter()));
    m_ui->letter15->setText(QString(pieces->at(3)->at(2)->getLetter()));
    m_ui->letter16->setText(QString(pieces->at(3)->at(3)->getLetter()));

}

void MainWindow::resetBoard()
{
    // Reset the scores
    this->foundWords->clear();

    // Start the timer
    m_ui->gameStatus->setText(tr("Press Start to begin the game..."));

    // Change the start button
    m_ui->startButton->setText(tr("Start"));

    // Empty and enable the entry field
    m_ui->wordEdit->setPlainText(tr("Enter words seperated by one space..."));
    m_ui->wordEdit->setEnabled(false);
    m_ui->startButton->setFocus();

    // Reset all the letters
    m_ui->letter1->setText("_");
    m_ui->letter2->setText("_");
    m_ui->letter3->setText("_");
    m_ui->letter4->setText("_");

    m_ui->letter5->setText("_");
    m_ui->letter6->setText("_");
    m_ui->letter7->setText("_");
    m_ui->letter8->setText("_");

    m_ui->letter9->setText("_");
    m_ui->letter10->setText("_");
    m_ui->letter11->setText("_");
    m_ui->letter12->setText("_");

    m_ui->letter13->setText("_");
    m_ui->letter14->setText("_");
    m_ui->letter15->setText("_");
    m_ui->letter16->setText("_");
}
