#ifndef LEXICON_H
#define LEXICON_H

#include <QtCore>

class Lexicon
{
    public:
        Lexicon(const QString& val);
        ~Lexicon();
        bool hasWord(const QString& val);
        void filterLexicon(QString pattern);
        QStringListIterator iterator();
    private:
        void load();
        QString filePath;
        QStringList* dictionary;
        QStringList* lexicon;
};

#endif // LEXICON_H
