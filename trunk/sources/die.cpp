#include "die.h"

Die::Die(char val)
{
    this->letter = val;
    this->setMarked(false);
}

Die::~Die()
{
    // delete this->char;
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
