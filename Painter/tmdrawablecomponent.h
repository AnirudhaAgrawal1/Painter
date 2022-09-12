#ifndef TMDRAWABLECOMPONENT_H
#define TMDRAWABLECOMPONENT_H
#include<QPointF>
#include<QColor>
#include<QPainter>
#include<QString>
#include<QList>
class TMDrawableComponent
{
private:
    int startX=0;
    int startY=0;
    int height=0;
    int width=0;
    int endX=0;
    int endY=0;
    QPointF pointf;
    bool isFill=false;
    QColor fillColor;
    QColor borderColor;
    int thickness=0;
    bool isSelectable=false;
    QString text="";
    QFont font;
    QString imageFileName;



public:
    TMDrawableComponent();
    QList<TMDrawableComponent *> freeHandComponentDS;
    int getStartX() const;
    void setStartX(int newStartX);
    int getStartY() const;
    void setStartY(int newStartY);
    int getHeight() const;
    void setHeight(int newHeight);
    int getWidth() const;
    void setWidth(int newWidth);
    int getEndX() const;
    void setEndX(int newEndX);
    int getEndY() const;
    void setEndY(int newEndY);
    QPointF getPointf() const;
    void setPointf(QPointF newPointf);
    bool getIsFill() const;
    void setIsFill(bool newIsFill);
    const QColor &getFillColor() const;
    void setFillColor(const QColor &newFillColor);
    const QColor &getBorderColor() const;
    void setBorderColor(const QColor &newBorderColor);
    int getThickness() const;
    void setThickness(int newThickness);
    virtual void draw(QPainter *)=0;
    virtual QString toString()=0;
    virtual bool isOwned(int,int)=0;
    virtual void select(QPainter *)=0;
    bool getIsSelectable() const;
    void setIsSelectable(bool newIsSelectable);
    const QString &getText() const;
    void setText(const QString &newText);
    const QFont &getFont() const;
    void setFont(const QFont &newFont);
    const QString &getImageFileName() const;
    void setImageFileName(const QString &newImageFileName);
};

#endif // TMDRAWABLECOMPONENT_H
