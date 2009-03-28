#ifndef DICETRAY_H
#define DICETRAY_H

#include <QtCore>
#include "die.h"

class DiceTray
{
    public:
        DiceTray();
        ~DiceTray();
        Die* (*getTray(void))[4][4];
        bool stringFound(QString search);

    private:
        bool stringFound(const QString& search, int row, int col);
        Die* dice[4][4];
        void setTrayMarked(bool val);
};

#endif // DICETRAY_H
