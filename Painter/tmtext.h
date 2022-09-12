#ifndef TMTEXT_H
#define TMTEXT_H
#include<tmdrawablecomponent.h>

class TMText:public TMDrawableComponent
{
public:
    TMText();
    TMText(TMDrawableComponent *);
    QString toString();
    void draw(QPainter *painter);
    bool isOwned(int x,int y);
    void select(QPainter *painter);

};

#endif // TMTEXT_H
