#ifndef TMELLIPSE_H
#define TMELLIPSE_H
#include<tmdrawablecomponent.h>

class TMEllipse:public TMDrawableComponent
{
public:
    TMEllipse();
    TMEllipse(TMDrawableComponent *);
    QString toString();
    void draw(QPainter *painter);
    bool isOwned(int x,int y);
    void select(QPainter *painter);
};

#endif // TMELLIPSE_H
