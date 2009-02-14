#include "dicetray.h"
#include <algorithm> // For std::random_shuffle

DiceTray::DiceTray()
{
    // Create four QLists of QList<Die*>
    this->dice = new QList<QList<Die*>*>;
    for (int i = 0; i < 4; i++)
        this->dice->append(new QList<Die*>);

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

    // God's dice need to be shaken, so to say
    std::random_shuffle(godsDice.begin(), godsDice.end());

    // Assign game pieces, and delete temporary dice
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            this->dice->at(row)->append(new Die((godsDice.at(0).at(rand() % 6)).toAscii()));
            godsDice.removeAt(0);
        }
    }
}

DiceTray::~DiceTray()
{
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
            this->dice->at(i)->at(j)->setMarked(false);

            if ((search.at(0)) == this->dice->at(i)->at(j)->getLetter())
                found = found || this->stringFound(search, i, j);
        }
    }

    return found;
}

bool DiceTray::stringFound(const QString& search, int row, int col)
{
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

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    this->dice->at(row)->at(col)->setMarked(true);
                    check = check || this->stringFound(search.mid(1), row + i, col + j);
                }
            }
        }

        return check;
    }
}
