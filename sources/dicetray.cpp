#include "dicetray.h"
#include <algorithm> // For std::random_shuffle
#include <vector>    // For godsDice
#include <time.h>    // For time()

DiceTray::DiceTray()
{
    // Seed the generator, setup for randomness
    srand((int)time(NULL));

    std::vector<std::string> godsDice;
    godsDice.push_back("LRYTTE");
    godsDice.push_back("ANAEEG");
    godsDice.push_back("AFPKFS");
    godsDice.push_back("YLDEVR");
    godsDice.push_back("VTHRWE");
    godsDice.push_back("IDSYTT");
    godsDice.push_back("XLDERI");
    godsDice.push_back("ZNRNHL");
    godsDice.push_back("EGHWNE");
    godsDice.push_back("OATTOW");
    godsDice.push_back("HCPOAS");
    godsDice.push_back("NMIQHU");
    godsDice.push_back("SEOTIS");
    godsDice.push_back("MTOICU");
    godsDice.push_back("ENSIEU");
    godsDice.push_back("OBBAOJ");

    // God's dice need to be shaken, so to say
    std::random_shuffle(godsDice.begin(), godsDice.end());

    // Assign game pieces, and delete temporary dice
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            this->dice[row][col] = new Die((godsDice.at(0).at(rand() % 6)));
            godsDice.erase(godsDice.begin());
        }
    }
}

std::string DiceTray::toPattern()
{
    std::string toReturn;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            toReturn += this->dice[i][j]->getLetter();

    std::transform(toReturn.begin(), toReturn.end(), toReturn.begin(), tolower);

    return toReturn;
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

bool DiceTray::stringFound(std::string search)
{
    // Make uppercase
    std::transform(search.begin(), search.end(), search.begin(), toupper);

    // The tray should be completely unused for a new word
    this->compareLength = 0;
    char firstLetterOfSearch = search.at(0);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (firstLetterOfSearch == this->dice[i][j]->getLetter())
                if (this->stringFound(search, i, j))
                    return true;
        }
    }

    return false;
}

bool DiceTray::stringFound(const std::string& search, int row, int col)
{
    if (row < 0 || row > 3 || col < 0 || col > 3)
        return false;

    // Get some constants
    Die* die = this->dice[row][col];

    if (die->isMarked())
        return false;
    else if (search.at(this->compareLength) != die->getLetter())
        return false;
    else if ((search.length() - 1) == this->compareLength)
        return true;
    else
    {
        // We've looked at the dice now
        die->setMarked(true);
        this->compareLength++;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (!(i == 0 && j == 0))
                {
                   if (this->stringFound(search, row + i, col + j))
                   {
                        die->setMarked(false); // we've found the word, mark it clean and move along
                        return true;
                   }
               }
            }
        }

        die->setMarked(false);
        this->compareLength--;

        return false;
    }
}
