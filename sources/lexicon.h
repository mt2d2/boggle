#ifndef LEXICON_H
#define LEXICON_H

#include <QtCore>

class Lexicon
{
    public:
        Lexicon(QString val);
        ~Lexicon();
        bool hasWord(QString& val);
        QStringList* dictionary;
    private:
        void load();
        QString filePath;

};

#endif // LEXICON_H
