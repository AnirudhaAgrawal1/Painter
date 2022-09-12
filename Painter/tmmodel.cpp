#include "tmmodel.h"
#include<mainwindow.h>
#include<tmline.h>
#include<tmfreehand.h>
#include<tmrectangle.h>
#include<tmellipse.h>
TMModel::TMModel()
{
    QList<TMDrawableComponent *> *list=new QList<TMDrawableComponent *>();
    this->componentsList.push_back(list);
}

void TMModel::draw(int pageNumber,QPainter *painter)
{
    TMDrawableComponent *component;
    for(int i=0;i<this->componentsList[pageNumber]->size();i++)
    {
        component=this->componentsList[pageNumber]->at(i);
        component->draw(painter);
        if(component->getIsSelectable()) component->select(painter);
    }
}

int TMModel::processClick(int x, int y,int pageNumber)
{
    bool found=false;
    TMDrawableComponent *component;
    for(int i=0;i<this->componentsList[pageNumber]->size();i++)
    {
        component=this->componentsList[pageNumber]->at(i);
        found=component->isOwned(x,y);
        if(found==true)
        {
            component->setIsSelectable(true);
            return i;
        }
    }
    return -1;
}

void TMModel::clearPage(int pageNumber)
{
    for(int i=0;i<this->componentsList[pageNumber]->size();i++)
    {
        delete this->componentsList[pageNumber]->at(i);
    }
    this->componentsList[pageNumber]->clear();
}

TMModel * TMModel::clone()
{
    TMModel *model=new TMModel();
    TMDrawableComponent *component,*comp;
    model->componentsList.clear();
    QString name;
    for(int i=0;i<this->componentsList.size();i++)
    {
        model->componentsList.push_back(new QList<TMDrawableComponent *>());
        for(int j=0;j<this->componentsList.at(i)->size();j++)
        {
            component=this->componentsList.at(i)->at(j);
            name=component->toString();
            if(name=="Rectangle") comp=new TMRectangle(component);
            if(name=="Line") comp=new TMLine(component);
            if(name=="Ellipse") comp=new TMEllipse(component);
            if(name=="Free Hand") comp=new TMFreeHand(component);
            model->componentsList.at(i)->push_back(comp);
        }
    }
    return model;
}
