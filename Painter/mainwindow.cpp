#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPropertyAnimation>
#include<QPainter>
#include<QString>
#include<tmdrawablecomponent.h>
#include<tmellipse.h>
#include<tmfreehand.h>
#include<tmline.h>
#include<tmrectangle.h>
#include<tmmodel.h>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QColorDialog>
#include<QRadioButton>
#include<QFileDialog>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QStack>
#include<QShortcut>
#include<QObject>
#include<tmtext.h>
#include<QFontDatabase>
#include<QPixmap>
bool abc=false;
TMModel *model;
QStack<TMModel *> *undoStack;
QStack<TMModel *> *redoStack;
bool isChanged=false;
QString component;
int oldX,oldY;
bool isCut=false;
int draggableComponentIndex;
int xOnDoubleClick,yOnDoubleClick;
bool mouseReleased=true;
TMDrawableComponent *drawableComponent;
int thickness;
QPointF qPointF;
QColor color;
QColor fillColor=QColor(Qt::white);
bool isSelectButtonClicked=false;
TMDrawableComponent *temp;
bool ctrlKeyPressed;
bool isComponentSelected=false;
int pageNumber=0;
int totalNumberOfPages=1;
bool bucketButtonClicked=false;
bool ctrlVPressed=false;
QCursor *openHandCursor;
QCursor *arrowCursor;
QList<TMDrawableComponent *> *list;
QList<QRadioButton *> radioButtonsList;
bool textButtonClicked=false;
bool pushedInUndoStack=false;
QPainter *painter;
QStringList fontFamiliesList;
TMRectangle boardBorder;
QString lastChangedStyleSheetComponent;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new TMModel();
    undoStack=new QStack<TMModel *>();
    redoStack=new QStack<TMModel *>();
    this->ui->Components_Table->verticalHeader()->setVisible(false);
    this->ui->Components_Table->horizontalHeader()->setVisible(false);
    this->ui->Components_Table->setColumnCount(1);
    this->ui->Components_Table->setColumnWidth(0,165);
    this->ui->Components_Table->setRowCount(0);
    this->ui->color_button_background_Frame->setStyleSheet(QString("background-color: rgb(255, 255, 255)"));
    this->ui->Color_Button->setStyleSheet(QString("background-color: rgb(0, 0, 0)"));
    QFont font("Times New Roman",12);
    this->ui->Components_Table->setFont(font);
    this->ui->Components_Table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    this->ui->Components_Table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    radioButtonsList.push_back(this->ui->Page_1);
    radioButtonsList.push_back(this->ui->Page_2);
    radioButtonsList.push_back(this->ui->Page_3);
    radioButtonsList.push_back(this->ui->Page_4);
    radioButtonsList.push_back(this->ui->Page_5);
    radioButtonsList.push_back(this->ui->Page_6);
    radioButtonsList.push_back(this->ui->Page_7);
    radioButtonsList.push_back(this->ui->Page_8);
    radioButtonsList.push_back(this->ui->Page_9);
    radioButtonsList.push_back(this->ui->Page_10);
    radioButtonsList.push_back(this->ui->Page_11);
    radioButtonsList.push_back(this->ui->Page_12);
    radioButtonsList.push_back(this->ui->Page_13);
    radioButtonsList.push_back(this->ui->Page_14);
    radioButtonsList.push_back(this->ui->Page_15);
    radioButtonsList.push_back(this->ui->Page_16);
    radioButtonsList.push_back(this->ui->Page_17);
    radioButtonsList.push_back(this->ui->Page_18);
    radioButtonsList.push_back(this->ui->Page_19);
    radioButtonsList.push_back(this->ui->Page_20);
    for(int i=0;i<radioButtonsList.size();i++) radioButtonsList[i]->setVisible(false);
    openHandCursor=new QCursor(Qt::CursorShape::OpenHandCursor);
    arrowCursor=new QCursor(Qt::CursorShape::ArrowCursor);
    this->ui->Undo_Button->setDisabled(true);
    this->ui->Redo_Button->setDisabled(true);
    QShortcut *ctrlSShortcut=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_S),this);
    QObject::connect(ctrlSShortcut,SIGNAL(activated()),this,SLOT(on_Save_Button_clicked()));
    QShortcut *ctrlZShortcut=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z),this);
    QObject::connect(ctrlZShortcut,SIGNAL(activated()),this,SLOT(on_Undo_Button_clicked()));
    QShortcut *ctrlVShortcut=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_V),this);
    QObject::connect(ctrlVShortcut,SIGNAL(activated()),this,SLOT(on_Paste_Button_clicked()));
    QShortcut *ctrlXShortcut=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_X),this);
    QObject::connect(ctrlXShortcut,SIGNAL(activated()),this,SLOT(on_Cut_Button_clicked()));
    QShortcut *ctrlCShortcut=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_C),this);
    QObject::connect(ctrlCShortcut,SIGNAL(activated()),this,SLOT(on_Copy_Button_clicked()));
    this->ui->textEdit->setVisible(false);
    QFontDatabase db;
    fontFamiliesList=db.families();
    fontFamiliesList.removeAt(0);
    this->ui->Font_Family_Combo_Box->addItems(fontFamiliesList);
    boardBorder.setStartX(119);
    boardBorder.setStartY(119);
    boardBorder.setWidth(1200);
    boardBorder.setHeight(640);
    this->ui->Text_Tool_Frame->setVisible(false);
}
MainWindow::~MainWindow()
{
 while(model->componentsList.size()!=0)
 {
     while(model->componentsList.at(0)->size()!=0)
     {
         if(model->componentsList.at(0)->at(0)->toString()=="Free Hand")
         {
             while(model->componentsList.at(0)->at(0)->freeHandComponentDS.size())
             {
                 delete model->componentsList.at(0)->at(0)->freeHandComponentDS.at(0);
                 model->componentsList.at(0)->at(0)->freeHandComponentDS.pop_front();
             }
         }
         delete model->componentsList.at(0)->at(0);
         model->componentsList.at(0)->pop_front();
     }
     delete model->componentsList.at(0);
     model->componentsList.pop_front();

 }
    while(model->groupedComponents.size()!=0)
    {
        while(model->groupedComponents[0]->size()!=0)
        {
            delete model->groupedComponents[0]->at(0);
            model->groupedComponents[0]->pop_front();
        }
        delete model->groupedComponents[0];
        model->groupedComponents.pop_front();
    }
    clearStack(undoStack);
    clearStack(redoStack);
    delete model;
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    painter=new QPainter(this);
    painter->setBrush(QBrush(QColor(255,255,255)));
    boardBorder.draw(painter);
    painter->setBrush(QBrush());
    model->draw(pageNumber,painter);
    if(undoStack->size()) this->ui->Undo_Button->setEnabled(true);
    painter->end();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x=event->position().x();
    int y=event->position().y();
    int rowNumber;
    QList<TMDrawableComponent *> *tempList;
    if(event->button()==Qt::LeftButton)
    {
    if(x>199 && x<1283 && y>119 && y<759)
    {
        oldX=x;
        oldY=y;
        rowNumber=model->processClick(x,y,pageNumber);
        if((isSelectButtonClicked==false && isComponentSelected==true) || ctrlKeyPressed==false)
        {
            for(int i=0;i<model->componentsList.at(pageNumber)->size();i++) model->componentsList.at(pageNumber)->at(i)->setIsSelectable(false);
            isComponentSelected=false;
        }

        if(bucketButtonClicked==true && rowNumber!=-1)
        {
            undoStack->push(model->clone());
            clearStack(redoStack);
            this->ui->Redo_Button->setEnabled(false);
            model->componentsList.at(pageNumber)->at(rowNumber)->setFillColor(fillColor);
            model->componentsList.at(pageNumber)->at(rowNumber)->setIsFill(true);
            update();
            return;

        }
        if(bucketButtonClicked==true && rowNumber==-1)
        {
            boardBorder.setFillColor(fillColor);
            boardBorder.setIsFill(true);
        }
        if(rowNumber==-1 && ctrlKeyPressed==false)
        {
            for(int i=0;i<model->componentsList.at(pageNumber)->size();i++) model->componentsList.at(pageNumber)->at(i)->setIsSelectable(false);
        }

        if(rowNumber!=-1) isComponentSelected=true;
        if(isSelectButtonClicked==true && rowNumber!=-1)
        {
            if(model->groupedComponents.size()>0)
            {
                for(int i=0;i<model->groupedComponents.size();i++)
                {
                    tempList=model->groupedComponents.at(i);
                    if(tempList->contains(model->componentsList.at(pageNumber)->at(rowNumber)))
                    {
                        for(int j=0;j<tempList->size();j++) tempList->at(j)->setIsSelectable(true);
                        update();
                        return;
                    }

                }
            }

               if(rowNumber!=-1 && ctrlKeyPressed==false)
               {
                   for(int i=0;i<model->componentsList.at(pageNumber)->size();i++) model->componentsList.at(pageNumber)->at(i)->setIsSelectable(false);
                   model->componentsList.at(pageNumber)->at(rowNumber)->setIsSelectable(true);
               }
           update();
        }
        if(component=="Text" && this->ui->textEdit->toPlainText().length()!=0)
        {
            QString text=this->ui->textEdit->toPlainText();
            drawableComponent=new TMText();
            drawableComponent->setText(text);
            drawableComponent->setStartX(this->ui->textEdit->geometry().x());
            drawableComponent->setStartY(this->ui->textEdit->geometry().y());
            drawableComponent->setFont(this->ui->textEdit->font());
            drawableComponent->setBorderColor(color);
            this->ui->textEdit->setVisible(false);
            this->ui->textEdit->setText("");
            model->componentsList.at(pageNumber)->push_back(drawableComponent);
            update();
            updateComponentTable();
            return;
        }
        if(component.length()!=0)
        {
            undoStack->push(model->clone());
            clearStack(redoStack);
            this->ui->Redo_Button->setEnabled(false);
        }
        if(component=="Text" && this->ui->textEdit->toPlainText().length()==0)
        {
            this->ui->textEdit->setGeometry(x,y,251,91);
            this->ui->textEdit->setVisible(true);
        }
    }
    }
    else
    {
        if(x>199 && x<1283 && y>119 && y<759)
        {
            if(component=="Text")
            {
                this->ui->textEdit->setVisible(false);
                this->ui->textEdit->setText("");
                this->ui->Text_Tool_Frame->setVisible(false);
            }
        }
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouseReleased=true;
    draggableComponentIndex=-1;
    pushedInUndoStack=false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x=event->position().x();
    int y=event->position().y();    
    QLabel *label;
    bool found=false;
    int size;
    QList<TMDrawableComponent *> *tempList;
    if(isSelectButtonClicked==true)
    {
        if(draggableComponentIndex!=-1)
        {
            drawableComponent=model->componentsList.at(pageNumber)->at(draggableComponentIndex);
            isChanged=true;
            if(pushedInUndoStack==false)
            {
                pushedInUndoStack=true;
                undoStack->push(model->clone());
                clearStack(redoStack);
                this->ui->Redo_Button->setEnabled(false);
            }
            if(model->groupedComponents.size()>0)
            {
                for(int i=0;i<model->groupedComponents.size();i++)
                {
                    if(model->groupedComponents.at(i)->contains(drawableComponent))
                    {
                        found=true;
                        tempList=model->groupedComponents.at(i);
                        for(int j=0;j<tempList->size();j++)
                        {
                            drawableComponent=tempList->at(j);
                            drawableComponent->setStartX(drawableComponent->getStartX()+(x-xOnDoubleClick));
                            drawableComponent->setStartY(drawableComponent->getStartY()+(y-yOnDoubleClick));
                            drawableComponent->setEndX(drawableComponent->getEndX()+(x-xOnDoubleClick));
                            drawableComponent->setEndY(drawableComponent->getEndY()+(y-yOnDoubleClick));
                        }
                        xOnDoubleClick=x;
                        yOnDoubleClick=y;
                        update();
                        return;

                    }
                }
            }
            if(found==false)
            {
            drawableComponent->setStartX(drawableComponent->getStartX()+(x-xOnDoubleClick));
            drawableComponent->setStartY(drawableComponent->getStartY()+(y-yOnDoubleClick));
            drawableComponent->setEndX(drawableComponent->getEndX()+(x-xOnDoubleClick));
            drawableComponent->setEndY(drawableComponent->getEndY()+(y-yOnDoubleClick));
            xOnDoubleClick=x;
            yOnDoubleClick=y;
            update();
            return;
            }

        }
    }
    if(component=="Rectangle")
    {
        if(mouseReleased==true)
        {
            drawableComponent=new TMRectangle();
            mouseReleased=false;
            model->componentsList.at(pageNumber)->append(drawableComponent);
            updateComponentTable();
        }
        drawableComponent->setStartX(oldX);
        drawableComponent->setStartY(oldY);
        drawableComponent->setEndX(x);
        drawableComponent->setEndY(y);
        drawableComponent->setHeight(y-oldY);
        drawableComponent->setWidth(x-oldX);
        drawableComponent->setThickness(thickness);
        drawableComponent->setBorderColor(color);
        update();        
    }
    if(component=="Line")
    {
        if(mouseReleased==true)
        {
            drawableComponent=new TMLine();
            mouseReleased=false;
            model->componentsList.at(pageNumber)->append(drawableComponent);
            updateComponentTable();
        }
        drawableComponent->setStartX(oldX);
        drawableComponent->setStartY(oldY);
        drawableComponent->setEndX(x);
        drawableComponent->setEndY(y);
        drawableComponent->setThickness(thickness);
        drawableComponent->setBorderColor(color);
        update();
    }
    if(component=="Ellipse")
    {
        if(mouseReleased==true)
        {
            drawableComponent=new TMEllipse();
            mouseReleased=false;
            model->componentsList.at(pageNumber)->append(drawableComponent);
            updateComponentTable();
        }
        drawableComponent->setStartX(oldX);
        drawableComponent->setStartY(oldY);
        drawableComponent->setWidth(x-oldX);
        drawableComponent->setHeight(y-oldY);
        drawableComponent->setThickness(thickness);
        drawableComponent->setBorderColor(color);
        update();
    }
    if(component=="Free Hand")
    {
        if(mouseReleased==true)
        {
            drawableComponent=new TMFreeHand();
            mouseReleased=false;
            model->componentsList.at(pageNumber)->append(drawableComponent);
            drawableComponent->setThickness(thickness);
            drawableComponent->setBorderColor(color);
            updateComponentTable();
        }
            temp=new TMFreeHand();
            drawableComponent->freeHandComponentDS.push_back(temp);
            temp->setStartX(oldX);
            temp->setStartY(oldY);
            temp->setEndX(x);
            temp->setEndY(y);
            oldX=x;
            oldY=y;
            update();
    }    

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
    if(key==16777249)
    {
    ctrlKeyPressed=true;
    }
    if(key==16777223) on_delete_button_clicked();
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==16777249)
    {
        ctrlKeyPressed=false;
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    xOnDoubleClick=event->x();
    yOnDoubleClick=event->y();
    int rowNumber=model->processClick(xOnDoubleClick,yOnDoubleClick,pageNumber);
    draggableComponentIndex=rowNumber;
}

void MainWindow::updateComponentTable()
{
    this->ui->Components_Table->clearContents();
    this->ui->Components_Table->setRowCount(0);
    QLabel *label;
    for(int i=0;i<model->componentsList.at(pageNumber)->size();i++)
    {
        this->ui->Components_Table->setRowCount(i+1);
        label=new QLabel(model->componentsList.at(pageNumber)->at(i)->toString());
        label->setAlignment(Qt::AlignCenter);
        this->ui->Components_Table->setCellWidget(i,0,label);
    }
}

void MainWindow::clearStack(QStack<TMModel *> *stack)
{
    TMModel *tmpModel;
    while(stack->size())
    {
        tmpModel=stack->pop();
        while(tmpModel->componentsList.size()!=0)
        {
            while(tmpModel->componentsList.at(0)->size()!=0)
            {
                if(tmpModel->componentsList.at(0)->at(0)->toString()=="Free Hand")
                {
                    while(tmpModel->componentsList.at(0)->at(0)->freeHandComponentDS.size())
                    {
                        delete tmpModel->componentsList.at(0)->at(0)->freeHandComponentDS.at(0);
                        tmpModel->componentsList.at(0)->at(0)->freeHandComponentDS.pop_front();
                    }
                }
                delete tmpModel->componentsList.at(0)->at(0);
                tmpModel->componentsList.at(0)->removeAt(0);
            }
            delete tmpModel->componentsList.at(0);
            tmpModel->componentsList.removeAt(0);
        }
        delete tmpModel;
    }
}

void MainWindow::updateButtonColor()
{
    if(lastChangedStyleSheetComponent=="Rectangle") this->ui->Rectangle_Button->setStyleSheet(QString("image: url(:/images/Rectangle-icon.png);"));
    if(lastChangedStyleSheetComponent=="Line") this->ui->Line_Button->setStyleSheet(QString("image: url(:/images/Line-icon.png);"));
    if(lastChangedStyleSheetComponent=="Ellipse") this->ui->Ellipse_Button->setStyleSheet(QString("image: url(:/images/Ellipse-icon.png);"));
    if(lastChangedStyleSheetComponent=="Free Hand") this->ui->FreeHand_Button->setStyleSheet(QString("image: url(:/images/edit-icon.png);"));
    if(lastChangedStyleSheetComponent=="Select") this->ui->Select_Button->setStyleSheet(QString("image: url(:/images/Select-icon.png);"));
    if(lastChangedStyleSheetComponent=="Bucket") this->ui->Bucket_Button->setStyleSheet(QString("image: url(:/images/bucket-icon.png);"));

    if(component=="Rectangle")
    {
        this->ui->Rectangle_Button->setStyleSheet(QString("image: url(:/images/Rectangle-icon.png);background-color: rgb(168, 216, 244)"));
        lastChangedStyleSheetComponent="Rectangle";
    }
    if(component=="Ellipse")
    {
        this->ui->Ellipse_Button->setStyleSheet(QString("image: url(:/images/Ellipse-icon.png);background-color: rgb(168, 216, 244)"));
        lastChangedStyleSheetComponent="Ellipse";
    }
    if(component=="Line")
    {
        this->ui->Line_Button->setStyleSheet(QString("image: url(:/images/Line-icon.png);background-color: rgb(168, 216, 244)"));
        lastChangedStyleSheetComponent="Line";
    }
    if(component=="Free Hand")
    {
        this->ui->FreeHand_Button->setStyleSheet(QString("image: url(:/images/edit-icon.png);background-color: rgb(168, 216, 244)"));
        lastChangedStyleSheetComponent="Free Hand";
    }
    if(component=="Select")
    {
        this->ui->Select_Button->setStyleSheet(QString("image: url(:/images/Select-icon.png);background-color: rgb(168, 216, 244)"));
        lastChangedStyleSheetComponent="Select";
    }
    if(component=="Bucket")
    {
        this->ui->Bucket_Button->setStyleSheet(QString("image: url(:/images/bucket-icon.png);background-color: rgb(168, 216, 244)"));
        lastChangedStyleSheetComponent="Bucket";
    }

}

void MainWindow::on_Line_Button_clicked()
{
    component=QString("Line");
    isSelectButtonClicked=false;
    bucketButtonClicked=false;
    updateButtonColor();
}


void MainWindow::on_FreeHand_Button_clicked()
{
    component=QString("Free Hand");
    isSelectButtonClicked=false;
    bucketButtonClicked=false;
    updateButtonColor();
}


void MainWindow::on_Ellipse_Button_clicked()
{
    component=QString("Ellipse");
    isSelectButtonClicked=false;
    bucketButtonClicked=false;
    updateButtonColor();
}


void MainWindow::on_Rectangle_Button_clicked()
{
    component=QString("Rectangle");
    isSelectButtonClicked=false;
    bucketButtonClicked=false;
    updateButtonColor();
}


void MainWindow::on_Width_Slider_valueChanged(int value)
{
    thickness=(value/4<1)?1:value/4;
}


void MainWindow::on_Color_Button_clicked()
{
    if(bucketButtonClicked==true)
    {
        fillColor=QColorDialog::getColor();
        QString s=QString("background-color: rgb(")+QString::number(fillColor.red())+QString(",")+QString::number(fillColor.green())+QString(",")+QString::number(fillColor.blue())+QString(")");
        this->ui->color_button_background_Frame->setStyleSheet(s);
    }
    else
    {
        color=QColorDialog::getColor();
        QString s=QString("background-color: rgb(")+QString::number(color.red())+QString(",")+QString::number(color.green())+QString(",")+QString::number(color.blue())+QString(")");
        this->ui->Color_Button->setStyleSheet(s);
    }
    component="";
}


void MainWindow::on_Clear_Button_clicked()
{
    model->clearPage(pageNumber);
    update();
    updateComponentTable();
    isSelectButtonClicked=false;
    component="";
    bucketButtonClicked=false;
}


void MainWindow::on_Select_Button_clicked()
{
    isSelectButtonClicked=true;
    component="Select";
    drawableComponent=model->componentsList.at(pageNumber)->at(0);
    bucketButtonClicked=false;
    updateButtonColor();
}


void MainWindow::on_Group_Button_clicked()
{
    component="";
    bucketButtonClicked=false;
    if(isSelectButtonClicked==false) return;
    QList<TMDrawableComponent *> *list=new QList<TMDrawableComponent *>();
     QList<TMDrawableComponent *> *tempList;
     bool found=false;
    if(model->componentsList.at(pageNumber)->size()<=1) return;
    for(int i=0;i<model->componentsList.at(pageNumber)->size();i++)
    {
        drawableComponent=model->componentsList.at(pageNumber)->at(i);
        if(drawableComponent->getIsSelectable()==true) list->push_back(drawableComponent);
    }
    if(model->groupedComponents.size()>0)
    {
        for(int i=0;i<model->groupedComponents.size();i++)
        {
            tempList=model->groupedComponents.at(i);
            for(int j=0;j<tempList->size();j++)
            {
                if(list->contains(tempList->at(j)))
                {
                    for(int k=0;k<list->size();k++)
                    {
                        if(tempList->contains(list->at(k))==false) tempList->push_back(list->at(k));
                    }
                    return;
                }
            }
        }
    }
        model->groupedComponents.push_back(list);
}


void MainWindow::on_UnGroup_Button_clicked()
{
    component="";
    QList<TMDrawableComponent *> *tmpList;
    for(int i=0;i<model->groupedComponents.size();i++)
    {
        tmpList=model->groupedComponents.at(i);
        if(tmpList->first()->getIsSelectable())
        {
            tmpList->clear();
            delete tmpList;
            model->groupedComponents.remove(i);
        }
    }
    bucketButtonClicked=false;
}


void MainWindow::on_New_Page_Button_clicked()
{
    component="";
    if(totalNumberOfPages==20)
    {
        return;
    }
    totalNumberOfPages++;
    pageNumber=totalNumberOfPages-1;
    if(totalNumberOfPages==2)
    {
        this->ui->Page_1->setVisible(true);
        this->ui->Page_2->setVisible(true);
        this->ui->Page_2->setChecked(true);
    }
    else
    {
        for(int i=0;i<pageNumber;i++) radioButtonsList[i]->setChecked(false);
        radioButtonsList[pageNumber]->setVisible(true);
        radioButtonsList[pageNumber]->setChecked(true);
    }
    list=new QList<TMDrawableComponent *>();
    model->componentsList.push_back(list);
    bucketButtonClicked=false;
    update();
    updateComponentTable();
}


void MainWindow::on_Bucket_Button_clicked()
{
    component="Bucket";
    bucketButtonClicked=true;
    updateButtonColor();
}


void MainWindow::on_Cut_Button_clicked()
{
    component="";
    isSelectButtonClicked=false;
        for(int i=0;i<model->cutCopyComponents.size();i++)
        {
            delete model->cutCopyComponents[i];
        }
    model->cutCopyComponents.clear();
    for(int i=0;i<model->componentsList.at(pageNumber)->size();i++)
    {
        drawableComponent=model->componentsList.at(pageNumber)->at(i);
        if(drawableComponent->getIsSelectable()==true)
        {
            model->cutCopyComponents.push_back(drawableComponent);
            model->componentsList.at(pageNumber)->remove(i);
            i--;
        }
    }
    isCut=true;
    update();
    updateComponentTable();
}


void MainWindow::on_Copy_Button_clicked()
{
    component="";
    TMDrawableComponent *comp;
    isSelectButtonClicked=false;
        for(int i=0;i<model->cutCopyComponents.size();i++)
        {
            delete model->cutCopyComponents[i];
        }
    model->cutCopyComponents.clear();
    for(int i=0;i<model->componentsList.at(pageNumber)->size();i++)
    {
        drawableComponent=model->componentsList.at(pageNumber)->at(i);
        if(drawableComponent->getIsSelectable()==true)
        {
            if(drawableComponent->toString()=="Rectangle") comp=new TMRectangle(drawableComponent);
            if(drawableComponent->toString()=="Line") comp=new TMLine(drawableComponent);
            if(drawableComponent->toString()=="Ellipse") comp=new TMEllipse(drawableComponent);
            if(drawableComponent->toString()=="Free Hand") comp=new TMFreeHand(drawableComponent);
            if(drawableComponent->toString()=="Text") comp=new TMText(drawableComponent);
            model->cutCopyComponents.push_back(comp);
        }
    }
    isCut=false;
}


void MainWindow::on_Paste_Button_clicked()
{
    component="";
    isSelectButtonClicked=false;
    int x,y;
    TMDrawableComponent *tmp;
    for(int i=0;i<model->cutCopyComponents.size();i++)
    {
        drawableComponent=model->cutCopyComponents[i];
            if(drawableComponent->toString()=="Rectangle")
            {
                tmp=new TMRectangle(drawableComponent);
                tmp->setStartX(drawableComponent->getStartX()+5);
                tmp->setStartY(drawableComponent->getStartY()+5);
                tmp->setEndX(drawableComponent->getEndX()+5);
                tmp->setEndY(drawableComponent->getEndY()+5);
                model->componentsList.at(pageNumber)->push_back(tmp);
            }
            if(drawableComponent->toString()=="Ellipse")
            {
                tmp=new TMEllipse(drawableComponent);
                tmp->setStartX(drawableComponent->getStartX()+5);
                tmp->setStartY(drawableComponent->getStartY()+5);
                model->componentsList.at(pageNumber)->push_back(tmp);
            }
            if(drawableComponent->toString()=="Line")
            {
                tmp=new TMLine(drawableComponent);
                tmp->setStartX(drawableComponent->getStartX()+5);
                tmp->setStartY(drawableComponent->getStartY()+5);
                tmp->setEndX(drawableComponent->getEndX()+5);
                tmp->setEndY(drawableComponent->getEndY()+5);
                model->componentsList.at(pageNumber)->push_back(tmp);

            }
            if(drawableComponent->toString()=="Free Hand")
            {
                tmp=new TMFreeHand(drawableComponent);

                model->componentsList.at(pageNumber)->push_back(tmp);
            }
            if(drawableComponent->toString()=="Text")
            {
                tmp=new TMText(drawableComponent);
                tmp->setStartX(drawableComponent->getStartX()+10);
                tmp->setStartY(drawableComponent->getStartY()+10);
                tmp->setEndX(drawableComponent->getEndX()+10);
                tmp->setEndY(drawableComponent->getEndY()+10);
                model->componentsList.at(pageNumber)->push_back(tmp);
            }
    }
    update();
    updateComponentTable();
}

void MainWindow::on_Save_Button_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Save File","c://","All files(*.tm)");
    if(fileName.length()==0) return;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    if(file.isOpen()==false) return;
    QJsonDocument jsonDocument;
    QJsonArray jsonArray;
    QJsonArray arr;
    TMDrawableComponent *comp;
    for(int j=0;j<model->componentsList.size();j++)
    {
    for(int i=0;i<model->componentsList.at(j)->size();i++)
    {
        drawableComponent=model->componentsList.at(j)->at(i);
        if(drawableComponent->toString()=="Free Hand")
        {
            for(int k=0;k<drawableComponent->freeHandComponentDS.size();k++)
            {
                comp=drawableComponent->freeHandComponentDS[k];
                QJsonObject jsonObject
                {
                    {"startX",comp->getStartX()},
                    {"startY",comp->getStartY()},
                    {"endX",comp->getEndX()},
                    {"endY",comp->getEndY()},
                    {"width",comp->getWidth()},
                    {"height",comp->getHeight()},
                    {"name",comp->toString()},
                    {"thickness",comp->getThickness()},
                    {"isFill",comp->getIsFill()},
                    {"RBorderColor",comp->getBorderColor().red()},
                    {"BBorderColor",comp->getBorderColor().blue()},
                    {"GBorderColor",comp->getBorderColor().green()},
                    {"RFillColor",comp->getFillColor().red()},
                    {"BFillColor",comp->getFillColor().blue()},
                    {"GFillColor",drawableComponent->getFillColor().green()},
                    {"PageNumber",j},
                    {"freeHandDS",""},
                    {"Text",drawableComponent->getText()},
                    {"FontFamily",drawableComponent->getFont().family()},
                    {"FontSize",drawableComponent->getFont().pointSize()}
                };
                arr.append(jsonObject);

            }
            QJsonObject jsonObject
            {
                {"startX",drawableComponent->getStartX()},
                {"startY",drawableComponent->getStartY()},
                {"endX",drawableComponent->getEndX()},
                {"endY",drawableComponent->getEndY()},
                {"width",drawableComponent->getWidth()},
                {"height",drawableComponent->getHeight()},
                {"name",drawableComponent->toString()},
                {"thickness",drawableComponent->getThickness()},
                {"isFill",drawableComponent->getIsFill()},
                {"RBorderColor",drawableComponent->getBorderColor().red()},
                {"BBorderColor",drawableComponent->getBorderColor().blue()},
                {"GBorderColor",drawableComponent->getBorderColor().green()},
                {"RFillColor",drawableComponent->getFillColor().red()},
                {"BFillColor",drawableComponent->getFillColor().blue()},
                {"GFillColor",drawableComponent->getFillColor().green()},
                {"PageNumber",j},
                {"freeHandDS",arr},
                {"Text",drawableComponent->getText()},
                {"FontFamily",drawableComponent->getFont().family()},
                {"FontSize",drawableComponent->getFont().pointSize()}
            };
            jsonArray.append(jsonObject);


        }
        else
        {
            QJsonObject jsonObject
            {
                {"startX",drawableComponent->getStartX()},
                {"startY",drawableComponent->getStartY()},
                {"endX",drawableComponent->getEndX()},
                {"endY",drawableComponent->getEndY()},
                {"width",drawableComponent->getWidth()},
                {"height",drawableComponent->getHeight()},
                {"name",drawableComponent->toString()},
                {"thickness",drawableComponent->getThickness()},
                {"isFill",drawableComponent->getIsFill()},
                {"RBorderColor",drawableComponent->getBorderColor().red()},
                {"BBorderColor",drawableComponent->getBorderColor().blue()},
                {"GBorderColor",drawableComponent->getBorderColor().green()},
                {"RFillColor",drawableComponent->getFillColor().red()},
                {"BFillColor",drawableComponent->getFillColor().blue()},
                {"GFillColor",drawableComponent->getFillColor().green()},
                {"pageNumber",j},
                {"freeHandDS",""},
                {"Text",drawableComponent->getText()},
                {"FontFamily",drawableComponent->getFont().family()},
                {"FontSize",drawableComponent->getFont().pointSize()}

            };
            jsonArray.append(jsonObject);
        }
    }
    }
    jsonDocument.setArray(jsonArray);
    file.write(jsonDocument.toJson());
    file.close();
}


void MainWindow::on_Open_Button_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File"),"c://","All files(*.tm)");
    if(fileName.length()==0) return;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen()) return;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonArray jsonArray=jsonDocument.array();
    QJsonObject jsonObject;
    QJsonArray tmpArray;
    TMDrawableComponent *comp;
    int pgNumber;
    for(int i=0;i<jsonArray.size();i++)
    {
        jsonObject=jsonArray[i].toObject();
        QString name=jsonObject.value("name").toString();
        if(name=="Rectangle") drawableComponent=new TMRectangle();
        if(name=="Line") drawableComponent=new TMLine();
        if(name=="Ellipse") drawableComponent=new TMEllipse();
        if(name=="Free Hand") drawableComponent=new TMFreeHand();
        if(name=="Text") drawableComponent=new TMText();
        drawableComponent->setStartX(jsonObject.value("startX").toInt());
        drawableComponent->setStartY(jsonObject.value("startY").toInt());
        drawableComponent->setEndX(jsonObject.value("endX").toInt());
        drawableComponent->setEndY(jsonObject.value("endY").toInt());
        drawableComponent->setWidth(jsonObject.value("width").toInt());
        drawableComponent->setHeight(jsonObject.value("height").toInt());
        drawableComponent->setBorderColor(QColor(jsonObject.value("RBorderColor").toInt(),jsonObject.value("GBorderColor").toInt(),jsonObject.value("BBorderColor").toInt()));
        drawableComponent->setFillColor(QColor(jsonObject.value("RFillColor").toInt(),jsonObject.value("GFillColor").toInt(),jsonObject.value("BFillColor").toInt()));
        drawableComponent->setIsFill(jsonObject.value("isFill").toBool());
        drawableComponent->setThickness(jsonObject.value("thickness").toInt());
        drawableComponent->setFont(QFont(jsonObject.value("FontFamily").toString(),jsonObject.value("FontSize").toInt()));
        drawableComponent->setText(jsonObject.value("Text").toString());
        pgNumber=jsonObject.value("pageNumber").toInt();
        if(name=="Free Hand")
        {
            tmpArray=jsonObject.value("freeHandDS").toArray();
            for(int j=0;j<tmpArray.size();j++)
            {
                comp=new TMFreeHand();
                jsonObject=tmpArray[j].toObject();
                comp->setStartX(jsonObject.value("startX").toInt());
                comp->setStartY(jsonObject.value("startY").toInt());
                comp->setEndX(jsonObject.value("endX").toInt());
                comp->setEndY(jsonObject.value("endY").toInt());
                drawableComponent->freeHandComponentDS.push_back(comp);
            }
        }
        if(model->componentsList.size()<=pgNumber) model->componentsList.push_back(new QList<TMDrawableComponent *>());
        model->componentsList.at(pgNumber)->push_back(drawableComponent);
    }
    pageNumber=0;
    totalNumberOfPages=model->componentsList.size();
    update();
    updateComponentTable();
    for(int i=0;i<radioButtonsList.size();i++)
    {
        radioButtonsList.at(i)->setVisible(false);
        radioButtonsList.at(i)->setChecked(false);
    }
    for(int i=0;i<model->componentsList.size();i++)
    {
        radioButtonsList.at(i)->setVisible(true);
    }
    this->ui->Page_1->setChecked(true);
}


void MainWindow::on_delete_button_clicked()
{
    for(int i=0;i<model->componentsList.at(pageNumber)->size();i++)
    {
        if(model->componentsList.at(pageNumber)->at(i)->getIsSelectable())
        {
            delete model->componentsList.at(pageNumber)->at(i);
            model->componentsList.at(pageNumber)->remove(i);
            updateComponentTable();
            i--;
        }

    }
    update();
    component="";
}

void MainWindow::on_Page_1_clicked()
{
    pageNumber=0;
    update();
    updateComponentTable();
}

void MainWindow::on_Page_2_clicked()
{
    pageNumber=1;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_3_clicked()
{
    pageNumber=2;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_4_clicked()
{
    pageNumber=3;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_5_clicked()
{
    pageNumber=4;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_6_clicked()
{
    pageNumber=5;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_7_clicked()
{
    pageNumber=6;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_8_clicked()
{
    pageNumber=7;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_9_clicked()
{
    pageNumber=8;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_10_clicked()
{
    pageNumber=9;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_11_clicked()
{
    pageNumber=10;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_12_clicked()
{
    pageNumber=11;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_13_clicked()
{
    pageNumber=12;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_14_clicked()
{
    pageNumber=13;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_15_clicked()
{
    pageNumber=14;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_16_clicked()
{
    pageNumber=15;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_17_clicked()
{
    pageNumber=16;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_18_clicked()
{
    pageNumber=17;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_19_clicked()
{
    pageNumber=18;
    update();
    updateComponentTable();
}
void MainWindow::on_Page_20_clicked()
{
    pageNumber=19;
    update();
    updateComponentTable();
}

void MainWindow::on_Undo_Button_clicked()
{
    redoStack->push(model);
    model=(TMModel *)undoStack->pop();
    if(undoStack->size()==0) this->ui->Undo_Button->setEnabled(false);
    this->ui->Redo_Button->setEnabled(true);
    update();
    updateComponentTable();
    component="";
}

void MainWindow::on_Redo_Button_clicked()
{
    undoStack->push(model);
    model=(TMModel *)redoStack->pop();
    if(redoStack->size()==0) this->ui->Redo_Button->setEnabled(false);
    this->ui->Undo_Button->setEnabled(true);
    update();
    updateComponentTable();
    component="";
}

void MainWindow::on_Components_Table_cellClicked(int row, int column)
{
    model->componentsList.at(pageNumber)->at(row)->setIsSelectable(true);
    isSelectButtonClicked=true;
    component="";
    update();
}

void MainWindow::on_Text_Button_clicked()
{
    component="Text";
    this->ui->Text_Tool_Frame->setVisible(true);
}


void MainWindow::on_Font_Family_Combo_Box_currentTextChanged(const QString &arg1)
{
    QFont font(this->ui->textEdit->font());
    font.setFamily(arg1);
    this->ui->textEdit->setFont(font);
}

/*
void MainWindow::on_Font_Size_Combo_Box_currentIndexChanged(const QString &arg1)
{
}
*/
void MainWindow::on_Font_Size_Combo_Box_currentTextChanged(const QString &arg1)
{
    QFont font(this->ui->textEdit->font());
    font.setPointSize(arg1.toInt());
    this->ui->textEdit->setFont(font);
}


void MainWindow::on_Bold_Button_clicked(bool checked)
{
    QFont font(this->ui->textEdit->font());
    if(font.bold()==false) font.setBold(true);
    else font.setBold(false);
    this->ui->textEdit->setFont(font);
}

void MainWindow::on_Italic_Button_clicked(bool checked)
{
    QFont font(this->ui->textEdit->font());
    if(font.italic()==false) font.setItalic(true);
    else font.setItalic(false);
    this->ui->textEdit->setFont(font);
}
void MainWindow::on_Underline_Button_clicked(bool checked)
{
    QFont font(this->ui->textEdit->font());
    if(font.underline()==false) font.setUnderline(true);
    else font.setUnderline(false);
    this->ui->textEdit->setFont(font);
}
