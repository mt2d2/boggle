#include "lexicon.h"

Lexicon::Lexicon(QString path)
{
    this->filePath = path;
    this->dictionary = new QStringList();

    qDebug() << "Initial: " << this->dictionary->size();
    this->load();
    qDebug() << "After load: " << this->dictionary->size();
}

Lexicon::~Lexicon()
{
    this->dictionary->clear();
    delete this->dictionary;
}

void Lexicon::load()
{
    QFile file(this->filePath);

    if (! file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (! in.atEnd())
       this->dictionary->append(in.readLine());

    // Sort out the dictionary
    this->dictionary->sort();
}

bool Lexicon::hasWord(QString val)
{
    return this->dictionary->contains(val, Qt::CaseInsensitive);
}
