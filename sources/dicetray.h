#ifndef DICETRAY_H
#define DICETRAY_H

#include <QtCore>
#include "die.h"

class DiceTray
{
    public:
        DiceTray();
        ~DiceTray();
        QList<QList<Die*>*>* getTray();
        bool stringFound(QString search);

    private:
        bool stringFound(QString search, int row, int col);
        QList<QList<Die*>*>* dice;
};

#endif // DICETRAY_H
