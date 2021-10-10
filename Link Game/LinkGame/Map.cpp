#include "LinkGame.h"
#include <QTime>
#include <QTimer>
#include <ctime>
#include<QDebug>
MapClass::MapClass(QWidget *parent ):QWidget(parent)//初始化计时器状态
{
   // connect(TimeType -> timer , &QTimer::timeout , this, QOverload<>::of(&MapClass::update));
    resize (500,500);
    LeftTimer  = new QTimer;

    TimeLabel = new QLabel(this);
    BeginLabel1 = new QLabel(this);
    BeginLabel2 = new QLabel(this);
    BeginLabel3 = new QLabel(this);
    BeginLabel4 = new QLabel(this);//加this是为了将Label在该Widget中显示，否则会在外面显示
    PropTime = new QTimer;

    HintTimer = new QTimer;
    Cont[ 0 ].Total = Height*Width;
    Prop[ 0 ].Total = Height;
    WoMan.Color = 7;
    PauseLabel = new QLabel(this);

}
void MapClass::ClearTouch()//用于清楚接触的高亮判定
{
    for(int i = 0;i<Height*Width;i ++ )
        Cont[ i ].Touch = false;
}
void MapClass::SrandProp()//用于随机道具的种类和地点（伪随机）
{
    if(!TimerFlag)
    {
        srand(time(NULL));//用时间作rand种子，保证每时每刻的随机数不同
        for(int i = 0;i<Height/2;i ++ )
        {
            Prop[ i ].exist = 1;
            Prop[ i ].Color = (rand()%3) + 3;
            Prop[ i ].x = From + (rand()%Height)*Length;
            Prop[ i ].y = From + Height*Length + ((rand()%3) + 2)*Length;
        }
        for(int i = Height/2;i<Height;i ++ )
        {
            Prop[ i ].exist = 1;
            Prop[ i ].Color = (rand()%3) + 3;//道具使用ColorHex中的第4到6种颜色
            Prop[ i ].y = From + (rand()%Height)*Length;
            Prop[ i ].x = From + Height*Length + ((rand()%3) + 2)*Length;
        }
    }

}
void MapClass::ShowLabel()//用于展示倒计时及分数
{
   // TimeLabel -> setBuddy(QWidget *parent);
    TimeLabel -> setGeometry(From,50,300,20);//用于定位Label的坐标
    QString Str = "倒计时：";
    Str += QString::number(LeftTime);
    if(!IsDoubleMode)
    {
        Str += " , 分数： ";
        Str += QString::number(Score1);
    }
    if(IsDoubleMode)
    {
        Str += " , 分数1：";
        Str += QString::number(Score1);
        Str += " , 分数2： ";
        Str += QString::number(Score2);
    }
    TimeLabel -> setText(Str);
    TimeLabel -> show();
   // qDebug()<<100;
}
void MapClass::AddLeftTime(int x)//用于+1s
{
    LeftTime += x;
}
void MapClass::ChangeLeftTime()//用于-1s
{
    LeftTime -= 1;
}
void MapClass::Connect(TimeKeeper *Timer)
{
    connect(Timer -> timer , &QTimer::timeout , this, QOverload<>::of(&MapClass::update));
}
void MapClass::ConnectLabelAndTime()//用于展示文字且用于绑定计时器
{
    connect(LeftTimer , SIGNAL(timeout()), this ,SLOT(ChangeLeftTime()));
    connect(LeftTimer , SIGNAL(timeout()), this ,SLOT(ShowLabel()));
    connect(PropTime, SIGNAL(timeout()),this,SLOT(SrandProp()));
    connect(HintTimer,SIGNAL(timeout()),this,SLOT(ClearTouch()));
    connect(LeftTimer,SIGNAL(timeout()),this,SLOT(IsTimeOver()));
    connect(LeftTimer,SIGNAL(timeout()),this,SLOT(IsNotHint()));//每秒刷新一次判定
}
void MapClass::IsNotHint()//用于判定游戏是否结束或者无解
{
    bool HintFlag = false,ExistFlag = false;//HIntFlag表示有方块可连接，ExistFlag表示有方块存在
    int i,j;
    for(i = 0;i<Height*Width;i ++ )
    {
        if(Cont[ i ].exist)   {
            ExistFlag = true;
            for(j = i + 1;j<Height*Width; j ++ )//暴力遍历每对方块的可连接性
            {
                if(Cont[ j ].exist)
                {
                    if(IsCanLink(i,j)!= -9) {
                        HintFlag = true;
                        break;
                    }
                }
            }
            if(HintFlag) break;
        }
    }
    if(!HintFlag&&(!ExistFlag))//无方块
    {
        if(IsDoubleMode)
        //QMessageBox::information(this,"Game Over","Game Over!   You Win!!");
        {
            if(Score1>Score2)
                QMessageBox::information(this,"Game Over","Game Over!   Player One Win!!");
            else if(Score1==Score2)
                QMessageBox::information(this,"Game Over","Game Over!   You Two Are Equal!!");
            else if(Score1<Score2)
                QMessageBox::information(this,"Game Over","Game Over!   Player Two Win!!");
        }
        else QMessageBox::information(this,"Game Over","Game Over!   You Win!!");
        ClearPLine();
        IsOrigin = true;
        ClearMap();//清空游戏界面
        ShowBeginLabel();//返回主界面
        LeftTimer -> stop();//停止刷新与倒计时
        PropTime -> stop();
    }
    if(!HintFlag&&ExistFlag)//无连接
    {
        QMessageBox::information(this,"Game Over","Game Over!   You Lost!!");
        ClearPLine();
        IsOrigin = true;
        ClearMap();//清空游戏界面
        ShowBeginLabel();//返回主界面
        LeftTimer -> stop();//停止刷新与倒计时
        PropTime -> stop();
    }
}
void MapClass::IsTimeOver()//用于判定倒计时是否结束
{
    if(LeftTime<= 1)
    {
        QMessageBox::information(this,"GameOver","Game Over!  You  Lost!!");
        ClearPLine();
        IsOrigin = true;
        ClearMap();//清空游戏界面
        ShowBeginLabel();//返回主界面
        LeftTimer -> stop();//停止刷新与倒计时
        PropTime -> stop();
    }
}
void MapClass::paintEvent(QPaintEvent *)//用于画图，同时也是本游戏的图像核心
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 设置 painter 的坐标系装换
     //int side  =  qMin(width(), height());
    //painter.translate(width() / 2, height() / 2);
    //painter.scale(side/200, side/200);
    painter.setPen(Qt::NoPen);
   // painter.setBrush();
    int i;
    for( i  =  0; i < Height*Width ; i ++  )
    {

            if( Cont [  i  ].exist)
            {
                if(Cont[ i ].Touch) painter.setPen(Qt::green);//对选定的加高亮标识
                painter.setBrush(Colorhex[  Cont[  i  ] .Color ]);//画方块
                QPoint Box[ 4 ]  =  {
                    QPoint(Cont [  i  ] .x,Cont [  i  ] .y),
                    QPoint(Cont [  i  ].x  +  Cont [  i  ].Len,Cont [  i  ] .y),
                    QPoint(Cont [  i  ] .x  +  Cont [  i  ].Len,Cont [  i  ] .y  +  Cont [  i  ].Len),
                    QPoint(Cont [  i  ] .x,Cont [  i  ] .y  +  Cont [  i  ].Len),
                   };
                painter.drawConvexPolygon(Box, 4);
                painter.setPen(Qt::NoPen);
         }
    }
    for( i  =  0; i < Height ; i ++  )
    {

            if( Prop [  i  ].exist)
            {
               // if(Prop[ i ].Touch) painter.setPen(Qt::green);
                painter.setBrush( Colorhex[  Prop[  i  ] .Color ]);//画道具，以四个点作正方形
                QPoint Box[ 4 ]  =  {
                    QPoint(Prop [  i  ] .x,Prop [  i  ] .y),
                    QPoint(Prop [  i  ].x  +  Prop [  i  ].Len,Prop [  i  ] .y),
                    QPoint(Prop [  i  ] .x  +  Prop [  i  ].Len,Prop [  i  ] .y  +  Prop [  i  ].Len),
                    QPoint(Prop [  i  ] .x,Prop [  i  ] .y  +  Prop [  i  ].Len),
                   };
                painter.drawConvexPolygon(Box, 4);
               // painter.setPen(Qt::NoPen);
         }
    }
    painter.setBrush(Colorhex[  Man .Color ]);//画人
    QPoint Box[ 4 ]  =  {
        QPoint( Man .x, Man .y),
        QPoint(Man .x  +  Man.Len,Man .y),
        QPoint(Man .x  +  Man.Len,Man .y  +  Man.Len),
        QPoint(Man .x,Man .y  +  Man.Len),
       };
    painter.drawConvexPolygon(Box, 4);
    if(IsDoubleMode) //判断是否是双人模式
    {
        painter.setBrush(Colorhex[  WoMan .Color ]);
        QPoint Box[ 4 ]  =  {
            QPoint( WoMan .x, WoMan .y),
            QPoint(WoMan .x  +  WoMan.Len,WoMan .y),
            QPoint(WoMan .x  +  WoMan.Len,WoMan .y  +  WoMan.Len),
            QPoint(WoMan .x,WoMan .y  +  WoMan.Len),
           };
        painter.drawConvexPolygon(Box, 4);
    }
    if(PLine.Start>= 0)
    {
        //10007是直线，单折线：-1是左上角，-2是左下角，-3是右下角，-4是右上角；边线：-5是向下，-6是向上，-7是向左，-8是向右；
        //双折线：Judge&0x1000，正则先直后折，0则先折后直，Judge&0xFFF得到点的坐标。
            painter.setPen(Qt::black);
            if(PLine.Judge == 10007) painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
            else if(PLine.Judge == -1)
            {
                painter.drawLine(qMin(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,qMin(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2);
            }
           else if(PLine.Judge == -2)
            {
                painter.drawLine(qMin(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,qMin(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2);
            }
            else if(PLine.Judge == -3)
            {
                painter.drawLine(qMax(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,qMax(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2);
            }
            else if(PLine.Judge == -4)
            {
                painter.drawLine(qMax(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,qMax(Cont[ PLine.Start ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ PLine.Start ].y,Cont[ PLine.End ].y) + Length/2);
            }
            else if(PLine.Judge == -5)
            {
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,Cont[ PLine.Start ].x + Length/2,Cont[ Height*Width-1 ].y + Length/2*3);
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ Height*Width-1 ].y + Length/2*3,Cont[ PLine.End ].x + Length/2,Cont[ Height*Width-1 ].y + Length/2*3);
                painter.drawLine(Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ Height*Width-1 ].y + Length/2*3);
            }
           else  if(PLine.Judge == -6)
            {
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,Cont[ PLine.Start ].x + Length/2,Cont[ 0 ].y-Length/2);
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ 0 ].y-Length/2,Cont[ PLine.End ].x + Length/2,Cont[ 0 ].y-Length/2);
                painter.drawLine(Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ 0 ].y-Length/2);
            }
            else if(PLine.Judge == -7)
            {
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,Cont[ 0 ].x-Length/2,Cont[ PLine.Start ].y + Length/2);
                painter.drawLine(Cont[ 0 ].x-Length/2,Cont[ PLine.Start ].y + Length/2,Cont[ 0 ].x-Length/2,Cont[ PLine.End ].y + Length/2);
                painter.drawLine(Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2,Cont[ 0 ].x-Length/2,Cont[ PLine.End ].y + Length/2);
            }
           else  if(PLine.Judge == -8)
            {
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,Cont[ Height-1 ].x + Length/2*3,Cont[ PLine.Start ].y + Length/2);
                painter.drawLine(Cont[ Height-1 ].x + Length/2*3,Cont[ PLine.Start ].y + Length/2,Cont[ Height-1 ].x + Length/2*3,Cont[ PLine.End ].y + Length/2);
                painter.drawLine(Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2,Cont[ Height-1 ].x + Length/2*3,Cont[ PLine.End ].y + Length/2);
            }
           else if((PLine.Judge&(0x1000))>0)
            {
                int i = PLine.Judge&(0xFFF);
                painter.drawLine(Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2,Cont[ i ].x + Length/2,Cont[ i ].y + Length/2);
                if(IsCanOneCornorLink(i,PLine.End) == -1)
                {
                    painter.drawLine(qMin(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                    painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMin(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2);
                }
                if(IsCanOneCornorLink(i,PLine.End) == -2)
                {
                    painter.drawLine(qMin(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                    painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMin(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2);
                }
                if(IsCanOneCornorLink(i,PLine.End) == -3)
                {
                    painter.drawLine(qMax(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                    painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMax(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2);
                }
                if(IsCanOneCornorLink(i,PLine.End) == -4)
                {
                    painter.drawLine(qMax(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2,Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2);
                    painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMax(Cont[ i ].x,Cont[ PLine.End ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.End ].y) + Length/2);
                }
            }
           else  if((PLine.Judge>= 0)&&((PLine.Judge&(0x1000)) == 0))
            {
                 int i = PLine.Judge&(0xFFF);
                 painter.drawLine(Cont[ PLine.End ].x + Length/2,Cont[ PLine.End ].y + Length/2,Cont[ i ].x + Length/2,Cont[ i ].y + Length/2);
                 if(IsCanOneCornorLink(i,PLine.Start) == -1)
                 {
                     painter.drawLine(qMin(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2,Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2);
                     painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMin(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2);
                 }
                 if(IsCanOneCornorLink(i,PLine.Start) == -2)
                 {
                     painter.drawLine(qMin(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2,Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2);
                     painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMin(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2);
                 }
                 if(IsCanOneCornorLink(i,PLine.Start) == -3)
                 {
                     painter.drawLine(qMax(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2,Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2);
                     painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMax(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMax(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2);
                 }
                 if(IsCanOneCornorLink(i,PLine.Start) == -4)
                 {
                     painter.drawLine(qMax(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2,Cont[ PLine.Start ].x + Length/2,Cont[ PLine.Start ].y + Length/2);
                     painter.drawLine(Cont[ i ].x + Length/2,Cont[ i ].y + Length/2,qMax(Cont[ i ].x,Cont[ PLine.Start ].x) + Length/2,qMin(Cont[ i ].y,Cont[ PLine.Start ].y) + Length/2);
                 }
            }
    }
}
int MapClass::IsDownPerson(Point *Cont, Person Man)//方块或者道具是否在人的下面
{
        int i;
        for(i = 0;i<Cont[ 0 ].Total;i ++ )
        {
            if(Cont[ i ].exist)
                if(Man.y + Man.Len == Cont[ i ].y)
                    if(Man.x == Cont[ i ].x) return i;
        }
        return -1;
}
int MapClass::IsUpPerson(Point *Cont, Person Man)
{
        int i;
        for(i = 0;i<Cont[ 0 ].Total;i ++ )
        {
            if(Cont[ i ].exist)
                if(Man.y-Man.Len == Cont[ i ].y)
                    if(Man.x == Cont[ i ].x) return i;
        }
        return -1;
}
int MapClass::IsLeftPerson(Point *Cont, Person Man)
{
        int i;
        for(i = 0;i<Cont[ 0 ].Total;i ++ )
        {
            if(Cont[ i ].exist)
                if(Man.x-Man.Len == Cont[ i ].x)
                    if(Man.y == Cont[ i ].y) return i;
        }
        return -1;
}
int MapClass::IsRightPerson(Point *Cont, Person Man)
{
        int i;
        for(i = 0;i<Cont[ 0 ].Total;i ++ )
        {
            if(Cont[ i ].exist)
                if(Man.x + Man.Len == Cont[ i ].x)
                    if(Man.y == Cont[ i ].y) return i;
        }
        return -1;
}
int MapClass::IsCanStraightLink(const int a, const int b)//直线连接
{
    //-9 means false
    if(a == b) return -9;
    if(Xline(a) == Xline(b))
    {
        int y1 = Yline(a),y2 = Yline(b);
        if(y1>y2) std::swap(y1,y2);
        y1 ++ ;
        for(;y1<y2;y1 ++ ){
            if(Cont[ y1*Height + Xline(a) ].exist) return -9;
        }
        return 10007;
        // 10007 means got it
    }
    if(Yline(a) == Yline(b))
    {
        int x1 = a,x2 = b;
        if(x1>x2) std::swap(x1,x2);
        x1 ++ ;
        for(;x1<x2;x1 ++ ){
            if(Cont[ x1 ].exist) return -9;
        }
        return 10007;
    }
    return -9;
}
int MapClass::IsCanOneCornorLink(const int a, const int b)//单折线连接
{
    //左上角   means -1
   int x1 = qMin(Xline(a),Xline(b)),y1 = qMin(Yline(a),Yline(b));
   if(IsCanStraightLink(y1*Height + x1,a) == 10007&&(IsCanStraightLink(y1*Height + x1,b) == 10007)&&(!Cont[ y1*Height + x1 ].exist)) return -1;
   //左下角   means -2
   y1 = qMax(Yline(a),Yline(b));
   if(IsCanStraightLink(y1*Height + x1,a) == 10007&&(IsCanStraightLink(y1*Height + x1,b) == 10007)&&(!Cont[ y1*Height + x1 ].exist)) return -2;
    //右下角   means -3
   x1 = qMax(Xline(a),Xline(b));
   if(IsCanStraightLink(y1*Height + x1,a) == 10007&&(IsCanStraightLink(y1*Height + x1,b) == 10007)&&(!Cont[ y1*Height + x1 ].exist)) return -3;
   //右上角   means -4
   y1 = qMin(Yline(a),Yline(b));
   if(IsCanStraightLink(y1*Height + x1,a) == 10007&&(IsCanStraightLink(y1*Height + x1,b) == 10007)&&(!Cont[ y1*Height + x1 ].exist)) return -4;

   return -9;

}
int  MapClass::IsCanByLink(const int a, const int b)//边界双折线连接
{
    bool Flag = true;
    //向下是空 means -5
    int i = a,j = b;
    i += Height;j += Height;
    while(i<Height*Width) {
        if(Cont[ i ].exist) Flag = false;
        i += Height;
    }
    while(j<Height*Width)
    {
        if(Cont[ j ].exist) Flag = false;
        j += Height;
    }
    if(Flag) return -5;
    Flag = true;
    //向上是空   means -6
        i = a,j = b;
        i-= Height;j-= Height;
        while(i>= 0) {
            if(Cont[ i ].exist) Flag = false;
            i-= Height;
        }
        while(j>= 0)
        {
            if(Cont[ j ].exist) Flag = false;
            j-= Height;
        }
        if(Flag) return -6;
        Flag = true;
        //向左是空   means -7
        i = a,j = b;

        if(i>0)
        {        i--;
            while(Xline(i)<(Height-1)&&i>= 0) {
                if(Cont[ i ].exist) Flag = false;
                i--;
            }
        }
       if(j>0)
       {      j--;
           while(Xline(j)<(Height-1)&&j>= 0)
           {
               if(Cont[ j ].exist) Flag = false;
               j--;
           }
       }

        if(Flag) return -7;
        Flag = true;
        //向右是空   means -8
        i = a,j = b;


        if(Xline(i)!= (Height-1))
        {
             i ++ ;
            while(Xline(i)<(Height-1)) {
                if(Cont[ i ].exist) Flag = false;
                i ++ ;
            }
            if(Cont[ i ].exist) Flag = false;
        }
        if(Xline(j)!= (Height-1))
        {    j ++ ;
            while(Xline(j)<(Height-1))
            {
                if(Cont[ j ].exist) Flag = false;
                j ++ ;
            }
             if(Cont[ j ].exist) Flag = false;
        }

        if(Flag) return -8;
        Flag = true;

        return -9;
}
int MapClass::IsCanTwoCornorLink(const int a, const int b)//双折线连接
{
    //特例，两者都在边缘
    int Judge = IsCanByLink(a,b);
    //printf("%d \n",Judge);
    if(Judge!= -9) return Judge;
    for(int i  =  0;i<Height*Width&&(i!= a)&&(i!= b);i ++ )
    {
            if(IsCanStraightLink(i,a)!= -9&&(IsCanOneCornorLink(i,b)!= -9)) return (i|(0x1000));
            if(IsCanStraightLink(i,b)!= -9&&(IsCanOneCornorLink(i,a)!= -9)) return i;
    }

    return -9;
}
int MapClass::IsCanLink(const int a, const int b)
{
    if(a == b) return -9;
    if(Cont[ a ].Color!= Cont[ b ].Color) return -9;
    if(IsCanStraightLink(a,b) == 10007) return 10007;
    if(IsCanOneCornorLink(a,b)!= -9) return IsCanOneCornorLink(a,b);
    if(IsCanTwoCornorLink(a,b)!= -9) return IsCanTwoCornorLink(a,b);
    //10007是直线，单折线：-1是左上角，-2是左下角，-3是右下角，-4是右上角；边线：-5是向下，-6是向上，-7是向左，-8是向右；
    //双折线：Judge&0x1000，正则先直后折，0则先折后直，Judge&0xFFF得到点的坐标。
    return -9;
}
void MapClass::PaintLine(const int a, const int b, const int Judge)//记录连接线信息
{
    PLine.Start = a;
    PLine.End = b;
    PLine.Judge = Judge;
    Cont[ a ].exist = false;
    Cont[ b ].exist = false;
}
void MapClass::keyPressEvent(QKeyEvent *event)
{
    if(event -> key() == Qt::Key_U&&IsOrigin)//U为单人模式
    {
        ClearPLine();
        IsOrigin = false;
        IsDoubleMode=false;
        BeginLabel1 -> close();//关闭主界面
        BeginLabel2 -> close();
        BeginLabel3 -> close();
        BeginLabel4 -> close();
        ResetMap();
        Srand();
        ShowLabel();//开启倒计时
        LeftTime = 360;
        LeftTimer -> start(1000);
        PropTime -> start(10000);
    }
    if(event -> key() == Qt::Key_M)//M为保存地图信息
    {
        ClearPLine();
        SaveData();
    }
    if(event -> key() == Qt::Key_Y&&IsOrigin)//Y为双人模式
    {
        ClearPLine();
        IsDoubleMode = true; //标注为双人模式
        ResetMap();
        Srand();
        ShowLabel();
        LeftTime = 360;
        LeftTimer -> start(1000);
        PropTime -> start(10000);
        BeginLabel1 -> close();
        BeginLabel2 -> close();
        BeginLabel3 -> close();
        BeginLabel4 -> close();
        IsOrigin = false;
        return ;
    }
    if(event -> key() == Qt::Key_T&&IsOrigin)//T为载入模式
    {
        ClearPLine();
        IsOrigin = false;
        LoadData();
        ShowLabel();
        LeftTimer -> start(1000);
        PropTime -> start(10000);
        BeginLabel1 -> close();
        BeginLabel2 -> close();
        BeginLabel3 -> close();
        BeginLabel4 -> close();
        return;
    }
    if(event -> key() == Qt::Key_Q)//Q为退出游戏
    {
        ClearPLine();
        BeginLabel1 -> close();
        BeginLabel2 -> close();
        BeginLabel3 -> close();
        BeginLabel4 -> close();
        this -> close();
        return ;
    }
    if(event -> key() == Qt::Key_Escape&&(!IsOrigin))//Esc为推出游戏界面返回主界面
    {
        ClearPLine();
        IsOrigin = true;
        ClearMap();//清空游戏界面
        ShowBeginLabel();//返回主界面
        LeftTimer -> stop();//停止刷新与倒计时
        PropTime -> stop();
    }
   if(!TimerFlag)
   {
       if(event -> key() == Qt::Key_S)//WSAD为第一位玩家的操作按钮
    {
        ClearPLine();
       int pnt = IsDownPerson(Cont,Man);
        if(pnt>= 0)//有与方块相碰
        {
            if(First<0)//是否已经选定第一个方块
            {
                Cont[ pnt ].Touch = 1;
                First = pnt;
            }

            else {
                if(IsCanLink(pnt,First)!= -9)
                {
                    PaintLine(pnt,First,IsCanLink(pnt,First));//画出连接线
                    First = -1;
                    if(Cont[ pnt ].Color == 0)
                    Score1 += 10;//方块颜色不同，积分不同
                    if(Cont[ pnt ].Color == 1)
                        Score1 += 5;
                    if(Cont[ pnt ].Color == 2)
                        Score1 += 2;
                }
                else {
                    Cont[ First ].Touch = 0;
                    First = -1;
                }
            }
            return;
        }
        pnt = IsDownPerson(Prop,Man);//对道具的判定
        if(pnt>= 0)
        {
            Prop[ pnt ].exist = false;
            if(Prop[ pnt ].Color == 3) Srand();//道具颜色不同，效果不同
            if(Prop[ pnt ].Color == 4) Hint();
            if(Prop[ pnt ].Color == 5) AddLeftTime(30);

        }
         Man.y += Man.Len;
    }
    if(event -> key() == Qt::Key_W)
    {
        ClearPLine();
        int pnt = IsUpPerson(Cont,Man);
         if(pnt>= 0)
         {
             if(First<0)
             {
                 Cont[ pnt ].Touch = 1;
                 First = pnt;
             }

             else {
                 if(IsCanLink(pnt,First)!= -9)
                 {
                     PaintLine(pnt,First,IsCanLink(pnt,First));
                     First = -1;
                     if(Cont[ pnt ].Color == 0)
                     Score1 += 10;
                     if(Cont[ pnt ].Color == 1)
                         Score1 += 5;
                     if(Cont[ pnt ].Color == 2)
                         Score1 += 2;
                 }
                 else {
                     Cont[ First ].Touch = 0;
                     First = -1;
                 }
             }
             return ;
         }
         pnt = IsUpPerson(Prop,Man);
         if(pnt>= 0)
         {
             Prop[ pnt ].exist = false;
             if(Prop[ pnt ].Color == 3) Srand();
             if(Prop[ pnt ].Color == 4) Hint();
             if(Prop[ pnt ].Color == 5) AddLeftTime(30);

         }

           Man.y-= Man.Len;
    }
    if(event -> key() == Qt::Key_A)
    {
        ClearPLine();
        int pnt = IsLeftPerson(Cont,Man);
         if(pnt>= 0)
         {
             if(First<0)
             {
                 Cont[ pnt ].Touch = 1;
                 First = pnt;
             }

             else {
                 if(IsCanLink(pnt,First)!= -9)
                 {
                     PaintLine(pnt,First,IsCanLink(pnt,First));
                     First = -1;
                     if(Cont[ pnt ].Color == 0)
                     Score1 += 10;
                     if(Cont[ pnt ].Color == 1)
                         Score1 += 5;
                     if(Cont[ pnt ].Color == 2)
                         Score1 += 2;
                 }
                 else {
                     Cont[ First ].Touch = 0;
                     First = -1;
                 }

             }
             return ;
         }
         pnt = IsLeftPerson(Prop,Man);
         if(pnt>= 0)
         {
             Prop[ pnt ].exist = false;
             if(Prop[ pnt ].Color == 3) Srand();
             if(Prop[ pnt ].Color == 4) Hint();
             if(Prop[ pnt ].Color == 5) AddLeftTime(30);

         }
         Man.x-= Man.Len;
    }
    if(event -> key() == Qt::Key_D)
    {
        ClearPLine();
        int pnt = IsRightPerson(Cont,Man);
         if(pnt>= 0)
         {
             if(First<0)
             {
                 Cont[ pnt ].Touch = 1;
                 First = pnt;
             }

             else {
                 if(IsCanLink(pnt,First)!= -9)
                 {
                     PaintLine(pnt,First,IsCanLink(pnt,First));
                     First = -1;
                     if(Cont[ pnt ].Color == 0)
                     Score1 += 10;
                     if(Cont[ pnt ].Color == 1)
                         Score1 += 5;
                     if(Cont[ pnt ].Color == 2)
                         Score1 += 2;
                 }
                 else {
                     Cont[ First ].Touch = 0;
                     First = -1;
                 }
             }
             return ;
         }
         pnt = IsRightPerson(Prop,Man);
         if(pnt>= 0)
         {
             Prop[ pnt ].exist = false;
             if(Prop[ pnt ].Color == 3) Srand();
             if(Prop[ pnt ].Color == 4) Hint();
             if(Prop[ pnt ].Color == 5) AddLeftTime(30);

         }
          Man.x += Man.Len;
    }
    if(event -> key() == Qt::Key_K)//IJKL为第二位玩家的操作按键，效果与第一位玩家的相同，不多赘述
    {
        ClearPLine();
       int pnt = IsDownPerson(Cont,WoMan);
        if(pnt>= 0)
        {
            if(First<0)
            {
                Cont[ pnt ].Touch = 1;
                First = pnt;
            }

            else {
                if(IsCanLink(pnt,First)!= -9)
                {
                    PaintLine(pnt,First,IsCanLink(pnt,First));
                    First = -1;
                    if(Cont[ pnt ].Color == 0)
                    Score2 += 10;
                    if(Cont[ pnt ].Color == 1)
                        Score2 += 5;
                    if(Cont[ pnt ].Color == 2)
                        Score2 += 2;
                }
                else {
                    Cont[ First ].Touch = 0;
                    First = -1;
                }
            }
            return;
        }
        pnt = IsDownPerson(Prop,WoMan);
        if(pnt>= 0)
        {
            Prop[ pnt ].exist = false;
            if(Prop[ pnt ].Color == 3) Srand();
            if(Prop[ pnt ].Color == 4) Hint();
            if(Prop[ pnt ].Color == 5) AddLeftTime(30);

        }
         WoMan.y += WoMan.Len;
    }
    if(event -> key() == Qt::Key_I)
    {
        ClearPLine();
        int pnt = IsUpPerson(Cont,WoMan);
         if(pnt>= 0)
         {
             if(First<0)
             {
                 Cont[ pnt ].Touch = 1;
                 First = pnt;
             }

             else {
                 if(IsCanLink(pnt,First)!= -9)
                 {
                     PaintLine(pnt,First,IsCanLink(pnt,First));
                     First = -1;
                     if(Cont[ pnt ].Color == 0)
                     Score2 += 10;
                     if(Cont[ pnt ].Color == 1)
                         Score2 += 5;
                     if(Cont[ pnt ].Color == 2)
                         Score2 += 2;
                 }
                 else {
                     Cont[ First ].Touch = 0;
                     First = -1;
                 }
             }
             return ;
         }
         pnt = IsUpPerson(Prop,WoMan);
         if(pnt>= 0)
         {
             Prop[ pnt ].exist = false;
             if(Prop[ pnt ].Color == 3) Srand();
             if(Prop[ pnt ].Color == 4) Hint();
             if(Prop[ pnt ].Color == 5) AddLeftTime(30);

         }

           WoMan.y-= WoMan.Len;
    }
    if(event -> key() == Qt::Key_J)
    {
        ClearPLine();
        int pnt = IsLeftPerson(Cont,WoMan);
         if(pnt>= 0)
         {
             if(First<0)
             {
                 Cont[ pnt ].Touch = 1;
                 First = pnt;
             }

             else {
                 if(IsCanLink(pnt,First)!= -9)
                 {
                     PaintLine(pnt,First,IsCanLink(pnt,First));
                     First = -1;
                     if(Cont[ pnt ].Color == 0)
                     Score2 += 10;
                     if(Cont[ pnt ].Color == 1)
                         Score2 += 5;
                     if(Cont[ pnt ].Color == 2)
                         Score2 += 2;
                 }
                 else {
                     Cont[ First ].Touch = 0;
                     First = -1;
                 }

             }
             return ;
         }
         pnt = IsLeftPerson(Prop,WoMan);
         if(pnt>= 0)
         {
             Prop[ pnt ].exist = false;
             if(Prop[ pnt ].Color == 3) Srand();
             if(Prop[ pnt ].Color == 4) Hint();
             if(Prop[ pnt ].Color == 5) AddLeftTime(30);

         }
         WoMan.x-= WoMan.Len;
    }
    if(event -> key() == Qt::Key_L)
    {
        ClearPLine();
        int pnt = IsRightPerson(Cont,WoMan);
         if(pnt>= 0)
         {
             if(First<0)
             {
                 Cont[ pnt ].Touch = 1;
                 First = pnt;
             }

             else {
                 if(IsCanLink(pnt,First)!= -9)
                 {
                     PaintLine(pnt,First,IsCanLink(pnt,First));
                     First = -1;
                     if(Cont[ pnt ].Color == 0)
                     Score2 += 10;
                     if(Cont[ pnt ].Color == 1)
                         Score2 += 5;
                     if(Cont[ pnt ].Color == 2)
                         Score2 += 2;
                 }
                 else {
                     Cont[ First ].Touch = 0;
                     First = -1;
                 }
             }
             return ;
         }
         pnt = IsRightPerson(Prop,WoMan);
         if(pnt>= 0)
         {
             Prop[ pnt ].exist = false;
             if(Prop[ pnt ].Color == 3) Srand();
             if(Prop[ pnt ].Color == 4) Hint();
             if(Prop[ pnt ].Color == 5) AddLeftTime(30);

         }
          WoMan.x += WoMan.Len;
    }
   }
    if(event -> key() == Qt::Key_P)//P表示游戏暂停，终止一切活动
    {
        ClearPLine();
        if(!TimerFlag)
        {
            LeftTimer -> stop();
            PropTime -> stop();
            TimerFlag = true;
            PauseLabel -> setGeometry(From,75,200,20);
            PauseLabel -> setText("Paused!!");
            PauseLabel -> show();
        }
        else
        {
            LeftTimer -> start(1000);
            PropTime  ->  start(10000);
            TimerFlag = false;
            PauseLabel -> close();
        }

    }
}
void MapClass::ClearMap()//用于归零化地图
{
    int i;
    for( i  =  0; i < Height*Width ; i ++  ){

            Cont [ i ].x  =  -200;
            Cont [ i ].y  = -200;
           // Map[ i ][ j ] = 1;
    }
   /* for( i  =  0; i< (Height*Width)/2 ; i ++ )
    {
        Cont[ i<<1 ].Color = Cont[ i*2 + 1 ].Color = rand()%3;
    }*/
    Man.x = Man.y = -200;
    WoMan.x  = WoMan.y  = -200;
    for( i  =  0;i<Height;i ++ )
        Prop[ i ].exist = false;
    TimeLabel -> close();
}
void MapClass::ResetMap()//用于初始化地图
{
    int i;
    for( i  =  0; i < Height*Width ; i ++  ){

            Cont [  i ].x  =  From +  Xline(i)* Cont [ i ].Len;//赋予坐标初始值
            Cont [ i ].y  =  From  +  Yline(i)* Cont [ i ].Len;
            Cont [ i ].exist = true;
            Cont [ i ].Touch = false;
           // Map[ i ][ j ] = 1;
    }
    for( i  =  0; i< (Height*Width)/2 ; i ++ )
    {
        Cont[ i<<1 ].Color = Cont[ i*2 + 1 ].Color = rand()%3;//两块方块一对，保证颜色可以消去，之后再用srand（）打乱，方块使用ColorHex中的前3种颜色
    }
    Man.x = Man.y = From-2*Length;
    WoMan.x  = WoMan.y  = From - 3*Length;
    for( i  =  0;i<Height;i ++ )
        Prop[ i ].exist = false;
    Score1 = Score2 = 0;
}
void MapClass::Srand()//用于打乱方块的位置
{
    srand(time(NULL));
    //用时间作rand种子，保证每时每刻的随机数不同
    int i , j ;
    for( i  =  0; i < Height*Width ; i ++  )
    {

            j = rand()%(Height*Width);
            std::swap(Cont[ i ].Color,Cont[ j ].Color);
            std::swap(Cont[ i ].exist,Cont[ j ].exist);
            std::swap(Cont[ i ].Touch,Cont[ j ].Touch);
    }
}
int MapClass::Xline(int i)
{
    return i%Height;
}
int MapClass::Yline(int i)
{
    return i/Height;
}
void MapClass::ClearPLine()//删除连接线
{
    PLine.Start = -1;
    PLine.End = -1;
    PLine.Judge = -9;
}
void MapClass::Hint()//用于寻找匹配的两个方块
{

    bool HintFlag = false;
    int i,j;
    for(i = 0;i<Height*Width;i ++ )
    {
        if(Cont[ i ].exist)   {
            for(j = i + 1;j<Height*Width; j ++ )
            {
                if(Cont[ j ].exist)
                {
                    if(IsCanLink(i,j)!= -9) {
                        HintFlag = true;
                        break;
                    }
                }
            }
            if(HintFlag) break;
        }
    }
    if(HintFlag){
        Cont[ i ].Touch = Cont[ j ].Touch = true;
        HintTimer -> start(10000);
    }

    return ;
}
void MapClass::ShowBeginLabel()//用于展示开始界面
{

    BeginLabel1 -> setGeometry(From,50,200,20);//用于定位Label的坐标
    BeginLabel1 -> setText("Press 'U' for SingalGame");
    BeginLabel2 -> setGeometry(From,100,200,20);
    BeginLabel2 -> setText("Press 'Y' for DoubleGame");
    BeginLabel3 -> setGeometry(From,150,200,20);
    BeginLabel3 -> setText("Press 'T' for LoadGame");
    BeginLabel4 -> setGeometry(From,200,200,20);
    BeginLabel4 -> setText("Press 'Q' for Quit");
    BeginLabel1 -> show();
    BeginLabel2 -> show();
    BeginLabel3 -> show();
    BeginLabel4 -> show();
    //BeginLabel4 -> close();
}
void MapClass::SaveData()//用于存储地图信息到save.txt中，依次存对局模式，倒计时，分数，方块的颜色及位置，人物的位置，道具的颜色及位置
{
    QFile file("save.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out (&file);
    if(IsDoubleMode) out<<1<<" ";
    else out<<0<<" ";
    out<<LeftTime<<" ";
    if(IsDoubleMode) out<<Score1<<" "<<Score2<<" ";
    else out<<Score1<<" ";
    out<<"\n";
    for(int i = 0;i<Height*Width;i ++ )
    {
        out<<Cont[ i ].Color<<" ";
        if(Cont[ i ].exist) out<<1<<" ";
        else out<<0<<" ";
    }
    out<<"\n";
    for(int i = 0;i<Height;i ++ )
    {
        out<<Prop[ i ].x<<" "<<Prop[ i ].y<<" "<<Prop[ i ].Color<<" ";
        if(Prop[ i ].exist) out<<1<<" ";
        else out<<0<<" ";
    }
    if(IsDoubleMode)
    {
        out<<"\n"<<Man.x<<" "<<Man.y<<" "<<WoMan.x<<" "<<WoMan.y<<" ";
    }
    else {
        out<<"\n"<<Man.x<<" "<<Man.y<<" ";
    }
    QMessageBox::information(this,"save","Save Success!!");
}
void MapClass::LoadData()//加载地图信息
{
    QFile file("save.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in (&file);
    int i,j,k,l;
    in>>i;
    if(i>0)
    {
        IsDoubleMode = true;
        in>>j>>k>>l;
        LeftTime = j;
        Score1 = k;
        Score2 = l;
        for(i = 0;i<Height*Width;i ++ )
        {
            in>>j>>k;
            Cont[ i ].Color = j;
            if(k>0) Cont[ i ].exist = true;
            else Cont[ i ].exist = false;
        }
        for(i = 0;i<Height;i ++ )
        {
            in>>j>>k>>l;
            Prop[ i ].x = j;Prop[ i ].y = k;Prop[ i ].Color = l;
            in>>j;
            if(j>0) Prop[ i ].exist = true;
            else Prop[ i ].exist = false;
        }
         in>>j>>k;
         Man.x = j;Man.y = k;
         in>>j>>k;
         WoMan.x = j;
         WoMan.y = k;
         Man.Color = 6;
         WoMan.Color = 7;
         for(i = 0;i<Height*Width;i ++ )
         {
             Cont [  i  ].x  =  From +  Xline(i)* Cont [  i  ].Len;
             Cont [  i  ].y  =  From  +  Yline(i)* Cont [  i  ].Len;
         }
        }
        else
    {
        in>>j>>k;
        LeftTime = j;
        Score1 = k;
        for(i = 0;i<Height*Width;i ++ )
        {
            in>>j>>k;
            Cont[ i ].Color = j;
            if(k>0) Cont[ i ].exist = true;
            else Cont[ i ].exist = false;
        }
        for(i = 0;i<Height;i ++ )
        {
            in>>j>>k>>l;
            Prop[ i ].x = j;Prop[ i ].y = k;Prop[ i ].Color = l;
            in>>j;
            if(j>0) Prop[ i ].exist = true;
            else Prop[ i ].exist = false;
        }
        for(i = 0;i<Height*Width;i ++ )
        {
            Cont [  i  ].x  =  From +  Xline(i)* Cont [  i  ].Len;
            Cont [  i  ].y  =  From  +  Yline(i)* Cont [  i  ].Len;
        }
         in>>j>>k;
         Man.x = j;Man.y = k;
        Man.Color = 6;
    }
}
