#ifndef LEXICON_H
#define LEXICON_H

#include <QtCore>

class Lexicon
{
    public:
        explicit Lexicon(QString val);
        ~Lexicon();
        bool hasWord(QString val);
    private:
        void load();

        QString filePath;
        QStringList* dictionary;
};

#endif // LEXICON_H
