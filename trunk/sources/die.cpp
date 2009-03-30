#include "die.h"

Die::Die(const char& val)
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

char Die::getLetter()
{
    return letter;
}
