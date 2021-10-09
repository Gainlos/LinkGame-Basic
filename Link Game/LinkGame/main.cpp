#include <QApplication>

#include "LinkGame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TimeKeeper Timer;
    MapClass Map;
    Map.Connect(&Timer);
    Map.ConnectLabelAndTime();
    Map.ShowBeginLabel();
    Map.show();
    return app.exec();
}
