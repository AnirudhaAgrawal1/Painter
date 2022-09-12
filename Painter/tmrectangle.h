#ifndef TMRECTANGLE_H
#define TMRECTANGLE_H
#include<tmdrawablecomponent.h>
#include<QPainter>
#include<QBrush>
#include<QColor>
#include<QPen>
class TMRectangle:public TMDrawableComponent
{
public:
    TMRectangle();
    TMRectangle(TMDrawableComponent *drawableComponent);
    QString toString();
    void draw(QPainter *painter);
    bool isOwned(int x,int y);
    void select(QPainter *painter);

};

#endif // TMRECTANGLE_H
