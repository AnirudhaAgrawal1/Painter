#ifndef TMFREEHAND_H
#define TMFREEHAND_H
#include<tmdrawablecomponent.h>

class TMFreeHand:public TMDrawableComponent
{
public:
    TMFreeHand();
    TMFreeHand(TMDrawableComponent *);
    QString toString();
    void draw(QPainter *painter);
    bool isOwned(int x,int y);
    void select(QPainter *painter);
};

#endif // TMFREEHAND_H
