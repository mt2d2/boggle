#ifndef DICETRAY_H
#define DICETRAY_H

#include <string>
#include "die.h"

class DiceTray
{
    public:
        DiceTray();
        ~DiceTray();
        Die* (*getTray(void))[4][4];
        bool stringFound(std::string search);
        std::string toPattern();

    private:
        bool stringFound(const std::string& search, int row, int col);
        Die* dice[4][4];

        // unsigned required to banish warnings?
        unsigned int compareLength;
};

#endif // DICETRAY_H
