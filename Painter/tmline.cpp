#include "tmline.h"

TMLine::TMLine()
{

}

TMLine::TMLine(TMDrawableComponent *drawableComponent)
{
    this->setStartX(drawableComponent->getStartX());
    this->setStartY(drawableComponent->getStartY());
    this->setEndX(drawableComponent->getEndX());
    this->setEndY(drawableComponent->getEndY());
    this->setThickness(drawableComponent->getThickness());
    this->setBorderColor(drawableComponent->getBorderColor());
}

QString TMLine::toString()
{
    return QString("Line");
}

void TMLine::draw(QPainter *painter)
{
    QPen pen;
    pen.setWidth(this->getThickness());
    pen.setColor(this->getBorderColor());
    painter->setPen(pen);;
    painter->drawLine(this->getStartX(),this->getStartY(),this->getEndX(),this->getEndY());
    painter->setPen(QPen());
}

bool TMLine::isOwned(int x, int y)
{
    int x1=this->getStartX();
    int x2=this->getEndX();
    int y1=this->getStartY();
    int y2=this->getEndY();
    int AB;
    int AC;
    int BC;
    int xDifference;
    int yDifference;
    int addition;
    xDifference=x-x1;
    yDifference=y-y1;
    xDifference=(xDifference*xDifference);
    yDifference=(yDifference*yDifference);
    addition=(xDifference+yDifference);
    AB=sqrt(addition);
    xDifference=x-x2;
    yDifference=y-y2;
    xDifference=(xDifference*xDifference);
    yDifference=(yDifference*yDifference);
    addition=(xDifference+yDifference);
    BC=sqrt(addition);
    xDifference=x1-x2;
    yDifference=y1-y2;
    xDifference=(xDifference*xDifference);
    yDifference=(yDifference*yDifference);
    addition=(xDifference+yDifference);
    AC=sqrt(addition);
    if(AC==(AB+BC))
    {
        return true;
    }
    return false;

}

void TMLine::select(QPainter *painter)
{
    painter->restore();
    painter->setPen(QPen());
    QBrush brush(QColor(Qt::blue));
    painter->setBrush(brush);
    painter->drawRect(this->getStartX()-4,this->getStartY()-4,8,8);
    painter->drawRect(this->getEndX()-4,this->getEndY()-4,8,8);
    painter->setBrush(QBrush());
    painter->restore();
}
