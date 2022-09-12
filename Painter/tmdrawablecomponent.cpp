#include "tmdrawablecomponent.h"

int TMDrawableComponent::getStartX() const
{
    return startX;
}

void TMDrawableComponent::setStartX(int newStartX)
{
    startX = newStartX;
}

int TMDrawableComponent::getStartY() const
{
    return startY;
}

void TMDrawableComponent::setStartY(int newStartY)
{
    startY = newStartY;
}

int TMDrawableComponent::getHeight() const
{
    return height;
}

void TMDrawableComponent::setHeight(int newHeight)
{
    height = newHeight;
}

int TMDrawableComponent::getWidth() const
{
    return width;
}

void TMDrawableComponent::setWidth(int newWidth)
{
    width = newWidth;
}

int TMDrawableComponent::getEndX() const
{
    return endX;
}

void TMDrawableComponent::setEndX(int newEndX)
{
    endX = newEndX;
}

int TMDrawableComponent::getEndY() const
{
    return endY;
}

void TMDrawableComponent::setEndY(int newEndY)
{
    endY = newEndY;
}

QPointF TMDrawableComponent::getPointf() const
{
    return pointf;
}

void TMDrawableComponent::setPointf(QPointF newPointf)
{
    pointf = newPointf;
}

bool TMDrawableComponent::getIsFill() const
{
    return isFill;
}

void TMDrawableComponent::setIsFill(bool newIsFill)
{
    isFill = newIsFill;
}

const QColor &TMDrawableComponent::getFillColor() const
{
    return fillColor;
}

void TMDrawableComponent::setFillColor(const QColor &newFillColor)
{
    fillColor = newFillColor;
}

const QColor &TMDrawableComponent::getBorderColor() const
{
    return borderColor;
}

void TMDrawableComponent::setBorderColor(const QColor &newBorderColor)
{
    borderColor = newBorderColor;
}

int TMDrawableComponent::getThickness() const
{
    return thickness;
}

void TMDrawableComponent::setThickness(int newThickness)
{
    thickness = newThickness;
}

bool TMDrawableComponent::getIsSelectable() const
{
    return isSelectable;
}

void TMDrawableComponent::setIsSelectable(bool newIsSelectable)
{
    isSelectable = newIsSelectable;
}

const QString &TMDrawableComponent::getText() const
{
    return text;
}

void TMDrawableComponent::setText(const QString &newText)
{
    text = newText;
}

const QFont &TMDrawableComponent::getFont() const
{
    return font;
}

void TMDrawableComponent::setFont(const QFont &newFont)
{
    font = newFont;
}

const QString &TMDrawableComponent::getImageFileName() const
{
    return imageFileName;
}

void TMDrawableComponent::setImageFileName(const QString &newImageFileName)
{
    imageFileName = newImageFileName;
}

TMDrawableComponent::TMDrawableComponent()
{

}
