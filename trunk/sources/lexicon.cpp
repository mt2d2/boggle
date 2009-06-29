#include "lexicon.h"

Lexicon::Lexicon(const QString& path)
{
    this->filePath = path;
    this->dictionary = new QStringList();
    this->lexicon = new QStringList();

    this->load();
}

Lexicon::~Lexicon()
{
    this->dictionary->clear();
    delete this->dictionary;

    this->lexicon->clear();
    delete this->lexicon;
}

void Lexicon::load()
{
    QFile file(this->filePath);

    if (! file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (! in.atEnd())
       this->dictionary->append(in.readLine());

    file.close();
}

void Lexicon::filterLexicon(QString pattern)
{
    // first clear out the existing lexicon
    this->lexicon->clear();

    // build the regexp
    QRegExp rx(QString("[%1]+").arg(pattern.toLower()));

    for (int i = 0; i < this->dictionary->size(); i++)
    {
        QString word = this->dictionary->at(i);

        if (rx.exactMatch(word))
            this->lexicon->append(word);
    }
}

QStringListIterator Lexicon::iterator()
{
    return QStringListIterator(*this->lexicon);
}

bool Lexicon::hasWord(const QString& val)
{
    // QStringList must implement binarySearch into contains; this is quite fast
    return this->lexicon->contains(val, Qt::CaseInsensitive);
}
