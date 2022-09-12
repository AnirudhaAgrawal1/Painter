#include "tmrectangle.h"
#include<QDebug>
TMRectangle::TMRectangle()
{

}

TMRectangle::TMRectangle(TMDrawableComponent *drawableComponent)
{
    this->setStartX(drawableComponent->getStartX());
    this->setStartY(drawableComponent->getStartY());
    this->setEndX(drawableComponent->getEndX());
    this->setEndY(drawableComponent->getEndY());
    this->setThickness(drawableComponent->getThickness());
    this->setBorderColor(drawableComponent->getBorderColor());
    this->setFillColor(drawableComponent->getFillColor());
    this->setIsFill(drawableComponent->getIsFill());
    this->setWidth(drawableComponent->getWidth());
    this->setHeight(drawableComponent->getHeight());
}

QString TMRectangle::toString()
{
    return QString("Rectangle");
}

void TMRectangle::draw(QPainter *painter)
{
    QPen pen;
    pen.setWidth(this->getThickness());
    pen.setColor(this->getBorderColor());
    painter->setPen(pen);
    QBrush brush(this->getFillColor());
   if(this->getIsFill()==true)
    {
    painter->setBrush(brush);
    }
   painter->drawRect(this->getStartX(),this->getStartY(),this->getWidth(),this->getHeight());
   painter->setPen(QPen());
   painter->setBrush(QBrush());
}

bool TMRectangle::isOwned(int x, int y)
{
    int x1=this->getStartX();
    int y1=this->getStartY();
    int x2=this->getEndX();
    int y2=this->getEndY();
    if(x1<x2 && y1<y2)
    {
       if(x>=x1 && x<=x2 && y>=y1 && y<=y2)
       {
           return true;
       }
    }
    if(x1>x2 && y1<y2)
    {
        if(x>=x2 && x<=x1 && y>=y1 && y<=y2)
        {
            return true;
        }
    }
    if(x1<x2 && y1>y2)
    {
        if(x>=x1 && x<=x2 && y<=y1 && y>=y2)
        {
            return true;
        }
    }
    if(x1>x2 && y1>y2)
    {
        if(x>=x2 && x<=x1 && y>=y2 && y<=y1)
        {
            return true;
        }
    }
    return false;

}

void TMRectangle::select(QPainter *painter)
{
    QBrush brush(QColor(Qt::blue));
    painter->setBrush(brush);
    painter->setPen(QPen());
    painter->drawRect(this->getStartX()-1-4,this->getStartY()-4,8,8);
    painter->drawRect(this->getEndX()-1-4,this->getEndY()-4,8,8);
    painter->drawRect(this->getEndX()-1-4,this->getStartY()-4,8,8);
    painter->drawRect(this->getStartX()-1-4,this->getEndY()-4,8,8);
    painter->setBrush(QBrush());
}
