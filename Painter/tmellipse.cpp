#include "tmellipse.h"

TMEllipse::TMEllipse()
{

}

TMEllipse::TMEllipse(TMDrawableComponent *drawableComponent)
{
    this->setStartX(drawableComponent->getStartX());
    this->setStartY(drawableComponent->getStartY());
    this->setThickness(drawableComponent->getThickness());
    this->setBorderColor(drawableComponent->getBorderColor());
    this->setFillColor(drawableComponent->getFillColor());
    this->setIsFill(drawableComponent->getIsFill());
    this->setWidth(drawableComponent->getWidth());
    this->setHeight(drawableComponent->getHeight());
}

QString TMEllipse::toString()
{
    return QString("Ellipse");
}

void TMEllipse::draw(QPainter *painter)
{
    QPointF centerPoint;
    centerPoint.setX(this->getStartX());
    centerPoint.setY(this->getStartY());
    QPen pen;
    pen.setWidth(this->getThickness());
    pen.setColor(this->getBorderColor());
    painter->setPen(pen);
    QBrush brush(this->getFillColor());
    if(this->getIsFill()==true)
        {
        painter->setBrush(brush);
        }
    painter->drawEllipse(centerPoint,this->getWidth(),this->getHeight());
    painter->setPen(QPen());
}

bool TMEllipse::isOwned(int x, int y)
{
    int x1=this->getStartX();
    int y1=this->getStartY();
    int width=this->getWidth();
    int height=this->getHeight();
    if(height>0 && width>0)
    {
        if((y>=y1-height) && (y<=y1+height) && (x<=x1+width) && (x>=x1-width))
        {
            return true;
        }
    }
    if(height<0 && width>0)
    {
        if((y<=y1-height) && (y>=y1+height) && (x<=x1+width) && (x>=x1-width))
        {
            return true;
        }
    }
    if(height<0 && width<0)
    {
        if((y<=y1-height) && (y>=y1+height) && (x>=x1+width) && (x<=x1-width))
        {
            return true;
        }
    }
    if(height>0 && width<0)
    {
        if((y>=y1-height) && (y<=y1+height) && (x>=x1+width) && (x<=x1-width))
        {
            return true;
        }
    }
    return false;

}

void TMEllipse::select(QPainter *painter)
{
    int x=this->getStartX();
    int y=this->getStartY();
    painter->setPen(QPen());
    QBrush brush(QColor(Qt::blue));
    painter->setBrush(brush);
    painter->drawRect(x+this->getWidth()-4,y-4,8,8);
    painter->drawRect(x-this->getWidth()-4,y-4,8,8);
    painter->drawRect(x-4,y+this->getHeight()-4,8,8);
    painter->drawRect(x-4,y-this->getHeight()-4,8,8);
    painter->setBrush(QBrush());
    painter->restore();

}
