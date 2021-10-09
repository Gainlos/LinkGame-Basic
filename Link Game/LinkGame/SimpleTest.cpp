#include "SimpleTest.h"
#include "LinkGame.h"

SimpleTest::SimpleTest()
{
    Map = new MapClass;

}

void SimpleTest::case1_testcase(){

       int i,j;
       QFile file("Map2.txt");//加载地图2
       file.open(QIODevice::ReadOnly);
       QTextStream in (&file);
       for(i=0;i<Map->Height*Map->Width;i++)
       {
           in>>j;
           if(j) Map->Cont[i].exist=1;
           else Map->Cont[i].exist=0;
           Map->Cont [ i ].x =Map-> From+ Map->Xline(i)* Map->Cont [ i ].Len;
           Map->Cont [ i ].y = Map->From + Map->Yline(i)* Map->Cont [ i ].Len;
       }
       /*Map
        *  0 1 1 1 1 0
        *  1 0 0 0 0 1
        *  1 0 1 1 0 1
        *  1 0 1 1 0 1
        *  1 0 0 0 0 1
        *  1 1 1 1 1 1
        * */
        QVERIFY(Map->IsCanStraightLink(1,31)==10007);
        QVERIFY(Map->IsCanStraightLink(6,11)==10007);
        QVERIFY(Map->IsCanStraightLink(6,17)==-9);
        QVERIFY(Map->IsCanStraightLink(6,24)==-9);
        QVERIFY(Map->IsCanOneCornorLink(6,34)==-4);
        QVERIFY(Map->IsCanOneCornorLink(14,11)==-1);
        QVERIFY(Map->IsCanByLink(6,24)==-7);
        QVERIFY(Map->IsCanTwoCornorLink(1,4)==-6);
        QVERIFY(Map->IsCanTwoCornorLink(32,23)==-9);
        QVERIFY(Map->IsCanTwoCornorLink(11,24)==0x1007);
}
void SimpleTest::case2_testcase(){

}

//QTEST_MAIN(SimpleTest)
