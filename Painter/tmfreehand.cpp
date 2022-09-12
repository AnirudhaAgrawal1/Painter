#include "tmfreehand.h"
#include<tmdrawablecomponent.h>
#include<QDebug>
TMFreeHand::TMFreeHand()
{

}

TMFreeHand::TMFreeHand(TMDrawableComponent *component)
{
    TMDrawableComponent *comp,*temp;
    this->setThickness(component->getThickness());
    this->setBorderColor(component->getBorderColor());
    for(int i=0;i<component->freeHandComponentDS.size();i++)
    {
        comp=new TMFreeHand();
        temp=component->freeHandComponentDS.at(i);
        comp->setStartX(temp->getStartX());
        comp->setStartY(temp->getStartY());
        comp->setEndX(temp->getEndX());
        comp->setEndY(temp->getEndY());
        this->freeHandComponentDS.push_back(comp);
    }
}

QString TMFreeHand::toString()
{
    return QString("Free Hand");
}

void TMFreeHand::draw(QPainter *painter)
{
    QPen pen;
    TMDrawableComponent *component;
    pen.setWidth(this->getThickness());
    pen.setColor(this->getBorderColor());
    painter->setPen(pen);
    for(int i=0;i<this->freeHandComponentDS.size();i++)
    {
        component=this->freeHandComponentDS.at(i);
        painter->drawLine(component->getStartX(),component->getStartY(),component->getEndX(),component->getEndY());
    }
    }

bool TMFreeHand::isOwned(int x, int y)
{
    TMDrawableComponent *component;
    bool found=false;
    for(int i=0;i<this->freeHandComponentDS.size();i++)
    {
        component=this->freeHandComponentDS[i];
        if(component->getStartX()==x && component->getStartY()==y)
        {
            found=true;
            break;
        }
    }
    return found;
}

void TMFreeHand::select(QPainter *painter)
{

    TMDrawableComponent *component;
    QBrush brush(QColor(Qt::blue));
    painter->setBrush(brush);
    painter->setPen(QPen());
    for(int i=0;i<this->freeHandComponentDS.size();i+=25)
    {
        component=this->freeHandComponentDS[i];
        painter->drawRect(component->getStartX()-4,component->getStartY()-4,8,8);
    }
    component=this->freeHandComponentDS[this->freeHandComponentDS.size()-1];
    painter->drawRect(component->getStartX()-4,component->getStartY()-4,8,8);
    painter->setBrush(QBrush());
    painter->restore();

}
