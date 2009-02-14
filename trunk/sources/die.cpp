#include "die.h"

Die::Die(const QChar& val)
{
    this->letter = val;
    this->setMarked(false);
}

Die::~Die()
{

}

bool Die::isMarked()
{
    return marked;
}

void Die::setMarked(bool val)
{
    marked = val;
}

QChar Die::getLetter()
{
    return letter;
}
