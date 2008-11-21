#ifndef LEXICON_H
#define LEXICON_H

#include <QtCore>

class Lexicon
{
    public:
        explicit Lexicon(QString val);
        ~Lexicon();
        bool hasWord(QString val);

        // TODO: Add accessor to the iterator of this list so it can be private
        // THIS IS BAD
        QStringList* dictionary;
    private:
        void load();

        QString filePath;

};

#endif // LEXICON_H
