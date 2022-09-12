#ifndef TMMODEL_H
#define TMMODEL_H
#include<QList>
#include<tmdrawablecomponent.h>
#include<QMap>
class TMModel
{
public:
    TMModel();
    QList<QList<TMDrawableComponent *> *> componentsList;
    QList<QList<TMDrawableComponent *> *> groupedComponents;
    QMap<int, QList<QList<TMDrawableComponent *> *> *> groupedComponentsMap;
    QList<TMDrawableComponent *> cutCopyComponents;
    void draw(int pageNumber,QPainter *painter);
    int processClick(int x,int y,int pageNumber);
    void clear();
    void clearPage(int);
    TMModel * clone();
};

#endif // TMMODEL_H
