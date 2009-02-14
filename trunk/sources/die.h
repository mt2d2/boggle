#ifndef DIE_H
#define DIE_H

#include <QtCore/QChar>

class Die
{
    public:
        Die(const QChar& val);
        ~Die();
        bool isMarked();
        void setMarked(bool val);
        QChar getLetter();

    private:
        QChar letter;
        bool marked;
};

#endif // DIE_H
