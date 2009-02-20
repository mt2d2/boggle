#ifndef LEXICON_H
#define LEXICON_H

#include <QtCore>

class Lexicon
{
    public:
        Lexicon(const QString& val);
        ~Lexicon();
        bool hasWord(const QString& val);
        QStringList* dictionary;
    private:
        void load();
        QString filePath;
};

#endif // LEXICON_H
