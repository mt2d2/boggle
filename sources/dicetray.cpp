#include "dicetray.h"

DiceTray::DiceTray()
{
    // Create four QLists of QList<Die*>
    this->dice = new QList<QList<Die*>*>;
    for (int i = 0; i < 4; i++)
    {
        QList<Die*>* ptr = new QList<Die*>;
        this->dice->append(ptr);
    }
    // Seed the generator, setup for randomness
    QStringList godsDice = QStringList();
    srand(QTime::currentTime().msec());

    godsDice.append("LRYTTE");
    godsDice.append("ANAEEG");
    godsDice.append("AFPKFS");
    godsDice.append("YLDEVR");
    godsDice.append("VTHRWE");
    godsDice.append("IDSYTT");
    godsDice.append("XLDERI");
    godsDice.append("ZNRNHL");
    godsDice.append("EGHWNE");
    godsDice.append("OATTOW");
    godsDice.append("HCPOAS");
    godsDice.append("NMIQHU");
    godsDice.append("SEOTIS");
    godsDice.append("MTOICU");
    godsDice.append("ENSIEU");
    godsDice.append("OBBAOJ");

    // FIXME: Gods Dice need to be shaken, so to say

    for (int i = 0; i < 16; i++)
        this->dice->at(i / 4)->append(new Die((godsDice.at(i).at(rand() % 6)).toAscii()));
}

DiceTray::~DiceTray()
{
    // Is this needed, is it properly cleaning up all memory?
    for (int i = 0; i < this->dice->size(); i++)
    {
        this->dice->at(i)->clear();
        delete this->dice->at(i);
    }

    this->dice->clear();
    delete this->dice;
}

QList<QList<Die*>*>* DiceTray::getTray()
{
    return this->dice;
}

bool DiceTray::stringFound(QString search)
{
    search = search.toUpper();
    bool found = false;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int m = 0; m < 4; m++)
                for (int n = 0; n < 4; n++)
                    this->dice->at(i)->at(j)->setMarked(false);

            if (search.at(0) == this->dice->at(i)->at(j)->getLetter())
                found = found || this->stringFound(search, i, j);
        }
    }

    return found;
}

bool DiceTray::stringFound(QString search, int row, int col)
{
    search = search.toUpper();

    if (row < 0 || row > 3 || col < 0 || col > 3)
        return false;
    else if (this->dice->at(row)->at(col)->isMarked())
        return false;
    else if (search.at(0) != this->dice->at(row)->at(col)->getLetter())
        return false;
    else if (search.length() == 1 && search.at(0) == this->dice->at(row)->at(col)->getLetter())
        return true;
    else
    {
        bool check = false;

        for (int m = -1; m <= 1; m++)
        {
            for (int n = -1; n <= 1; n++)
            {
                if (m != 0 || n != 0)
                {
                    this->dice->at(row)->at(col)->setMarked(true);
                    check = check || this->stringFound(search.mid(1), row + m, col + n);
                }
            }
        }

        return check;
    }
}
