#include "dicetray.h"
#include <algorithm> // For std::random_shuffle

DiceTray::DiceTray()
{
    // Seed the generator, setup for randomness
    srand(QTime::currentTime().msec());

    QStringList godsDice = QStringList();
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
            this->dice[row][col] = new Die((godsDice.at(0).at(rand() % 6)));
            godsDice.removeAt(0);
        }
    }
}

DiceTray::~DiceTray()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
             delete this->dice[i][j];
}

Die* (*DiceTray::getTray(void))[4][4]
{
    return &this->dice;
}

void DiceTray::setTrayMarked(bool val)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            this->dice[i][j]->setMarked(val);
}

bool DiceTray::stringFound(QString search)
{
    search = search.toUpper();
    QChar firstLetterOfSearch = search.at(0);
    bool found = false;

    // Can this be moved out of loop?
    this->setTrayMarked(false);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (firstLetterOfSearch == this->dice[i][j]->getLetter())
                found = found || this->stringFound(search, i, j);
        }
    }

    return found;
}

bool DiceTray::stringFound(const QString& search, int row, int col)
{
    if (row < 0 || row > 3 || col < 0 || col > 3)
        return false;

    // Get some constants
    Die* die = this->dice[row][col];
    QChar diceLetter = die->getLetter();
    QChar firstLetterOfSearch = search.at(0);

    if (die->isMarked())
        return false;
    else if (firstLetterOfSearch != diceLetter)
        return false;
    else if (search.length() == 1)
        return true;
    else
    {
        // We've looked at the dice now
        die->setMarked(true);

        QString newSearch = search.mid(1);
        bool check = false;

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if (!(i == 0 && j == 0))
                    check = check || this->stringFound(newSearch, row + i, col + j);

        return check;
    }
}
