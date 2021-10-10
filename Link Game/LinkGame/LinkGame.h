#pragma once
#ifndef LINKGAME_H
#define LINKGAME_H


#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QRectF>
#include <QKeyEvent>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <QLabel>
#include <QFile>
#include <QMessageBox>


class TimeKeeper :public QTimer
{
    Q_OBJECT
public:
    QTimer *timer;
    TimeKeeper();
    void ChangeFps(int Fps);//用于游戏刷新率的计时器，其与paintEvent用connect 绑定

};

class MapClass :public QWidget
{
    Q_OBJECT
public  slots:
    void ClearTouch();//用于清楚接触的高亮判定
    void SrandProp();//用于随机道具的种类和地点（伪随机）
    void ShowLabel();//用于展示倒计时及分数
    void ConnectLabelAndTime();//用于展示文字且用于绑定计时器
    void ChangeLeftTime();//用于-1s
    void IsTimeOver();//用于判定倒计时是否结束
    void IsNotHint();//用于判定游戏是否结束或者无解
public:
    struct Point {
        int x = -100 ,y = -100 ,Len = Length,  Total = 0;
        bool exist = true;
        bool Touch = false;
        int Color = 0;
       // Point(int i, int j):x(i),y(j){};
    };
    static const int Height = 3, Width = 6;// 分别表示行和列
    static const int From = 150;//用于改动方块的初始位置
    static const int Length = 30;

    Point  Cont  [ Height*Width ];//以i%Height表示列，i/Height表示行。
    Point  Prop  [ Height ];//规定道具容量为行数可以保证起数量足够又不至于太多
    struct  Person
    {
        int x = -100,y = -100,Len = Length;
        int Color = 6;
    };
    Person Man;
    Person WoMan;//Man，WoMan即代指Player1,Player2
    struct LineData
    {
        int Start = -1,End = -1 ,Judge = -9;
    };
    LineData PLine;//用于记录和绘制连接线
    void SaveData();
   // int Map [10007][10007];
    void ResetMap() ;//用于初始化地图
    void ClearMap();//用于归零化地图
    QLabel   *TimeLabel;
    QLabel  *BeginLabel1;
    QLabel  *BeginLabel2;
    QLabel  *BeginLabel3;
    QLabel  *BeginLabel4;
    QLabel  *PauseLabel;
    QTimer   *LeftTimer;
    QTimer   *PropTime;
    QTimer   *HintTimer;
    bool TimerFlag=false;//用于游戏暂停的状态符
    int LeftTime = 360;//游戏倒计时
    int Score1 = 0,Score2 = 0;
    bool IsDoubleMode = false;//双人模式状态符
    bool IsOrigin = true;//开始界面状态符
    MapClass(QWidget *parent = nullptr );

    void AddLeftTime(int x);//用于+1s
    void Hint();//用于寻找匹配的两个方块
    void ShowBeginLabel();//用于展示开始界面
    void paintEvent(QPaintEvent *event) override;//用于画图，同时也是本游戏的图像核心
    void Connect (TimeKeeper * Timer);
    void Srand();//用于打乱方块的位置
    void keyPressEvent(QKeyEvent *event) override;//用于按键监测，同时也是本游戏的主要互动函数
    QColor Colorhex[ 8 ]={Qt::gray , Qt::darkBlue , Qt::red , Qt::yellow , Qt::darkYellow , Qt::green , Qt::darkRed , Qt::darkMagenta };
    int IsDownPerson(Point *Cont, Person Man);//方块或者道具是否在人的下面
    int IsUpPerson(Point *Cont, Person Man);
    int IsLeftPerson(Point *Cont, Person Man);
    int IsRightPerson(Point *Cont, Person Man);
    int First = -1;//人是否是第一次接触方块，用于判定是否执行消除操作
    int IsCanStraightLink(const int a,const int b);//直线连接
    int IsCanOneCornorLink(const int a , const int b );//单折线连接
    int IsCanTwoCornorLink(const int a , const int b );//双折线连接
    int IsCanByLink(const int a , const int b);//边界双折线连接
    int IsCanLink(const int a,const int b);//两点是否能够连接
    void PaintLine(const int a,const int b, const int Judge);//记录连接线信息
    int Xline( int i );
    int Yline( int i );
    void ClearPLine();//删除连接线
    void LoadData();//加载地图信息
};

#endif // LINKGAME_H
