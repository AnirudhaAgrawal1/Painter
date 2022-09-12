#include "tmtext.h"
#include<QFontMetrics>
#include<iostream>
TMText::TMText()
{

}

TMText::TMText(TMDrawableComponent *drawableComponent)
{
    this->setStartX(drawableComponent->getStartX());
    this->setStartY(drawableComponent->getStartY());
    this->setEndX(drawableComponent->getEndX());
    this->setEndY(drawableComponent->getEndY());
    this->setBorderColor(drawableComponent->getBorderColor());
    this->setWidth(drawableComponent->getWidth());
    this->setHeight(drawableComponent->getHeight());
    this->setText(drawableComponent->getText());
    this->setFont(drawableComponent->getFont());
}

void TMText::draw(QPainter *painter)
{
    QPen pen;
    pen.setColor(this->getBorderColor());
    painter->setPen(pen);
    painter->setFont(this->getFont());
    QRect br=painter->boundingRect(0, 0, 150, 30, 0, this->getText());
    this->setWidth(br.width());
    this->setHeight(br.height());
    this->setEndY(this->getStartY()+this->getHeight());
    this->setEndX(this->getStartX()+this->getWidth());
    QRect rect(this->getStartX(),this->getStartY(),this->getWidth(),this->getHeight());
    painter->drawText(rect,Qt::AlignHCenter|Qt::AlignBottom,this->getText());
    painter->setPen(QPen());
    painter->setFont(QFont());
}

bool TMText::isOwned(int x, int y)
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

void TMText::select(QPainter *painter)
{
    QBrush brush(QColor(Qt::blue));
    painter->setBrush(brush);
    painter->setPen(QPen());
    painter->drawRect(this->getStartX()-1-4,this->getStartY()-4,8,8);
    painter->drawRect(this->getEndX()-1-4,this->getEndY(),8,8);
    painter->drawRect(this->getEndX()-1-4,this->getStartY()-4,8,8);
    painter->drawRect(this->getStartX()-1-4,this->getEndY(),8,8);
    painter->setBrush(QBrush());
}

QString TMText::toString()
{
    return QString("Text");
}
