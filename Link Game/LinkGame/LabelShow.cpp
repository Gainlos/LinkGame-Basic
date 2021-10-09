#include "LinkGame.h"


LabelShow::LabelShow()
{
    TimeLabel = new QLabel;
}

LabelShow:: ~LabelShow()
{
    delete TimeLabel;
}

void LabelShow::SetLocation(int x, int y, int height, int width)
{
    TimeLabel->setGeometry(x,y,height,width);
}
void LabelShow::ChangeLeftTime(int x)
{
    LeftTime=x;
}
void LabelShow::AddLeftTime(int x)
{
    LeftTime+=x;
}
void LabelShow::ShowTime()
{
    TimeLabel->setText(QString::number(LeftTime));
}
