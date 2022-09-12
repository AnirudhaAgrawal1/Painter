#ifndef TMLINE_H
#define TMLINE_H
#include<tmdrawablecomponent.h>

class TMLine:public TMDrawableComponent
{
public:
    TMLine();
    QString toString();
    TMLine(TMDrawableComponent *);
    void draw(QPainter *painter);
    bool isOwned(int x,int y);
    void select(QPainter *painter);
};

#endif // TMLINE_H
