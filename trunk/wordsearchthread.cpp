#include "wordsearchthread.h"

WordSearchThread::WordSearchThread(MainWindow* parent)
{
    this->main = parent;
}


void WordSearchThread::run()
{
    for (int i = 0; i < main->lexicon->dictionary->size(); i++)
    {
        QString word = main->lexicon->dictionary->at(i);

        if (main->diceTray->stringFound(word))
            main->wordsNotFound->append(word);
    }
}
