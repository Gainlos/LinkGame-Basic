#include "LinkGame.h"
TimeKeeper::TimeKeeper()
{
    timer=new QTimer(this);
    ChangeFps(50);
}

void TimeKeeper::ChangeFps(int Fps=50)
{
    timer->start(Fps);
}
