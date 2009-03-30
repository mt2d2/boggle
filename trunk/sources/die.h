#ifndef DIE_H
#define DIE_H

class Die
{
    public:
        Die(const char& val);
        ~Die();
        bool isMarked();
        void setMarked(bool val);
        char getLetter();

    private:
        char letter;
        bool marked;
};

#endif // DIE_H
