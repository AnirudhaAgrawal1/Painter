#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QKeyEvent>
#include<tmmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void updateComponentTable();
    void clearStack(QStack<TMModel *> *);
    void updateButtonColor();
private slots:
    void on_Line_Button_clicked();

    void on_FreeHand_Button_clicked();

    void on_Ellipse_Button_clicked();

    void on_Rectangle_Button_clicked();

    void on_Width_Slider_valueChanged(int value);

    void on_Color_Button_clicked();

    void on_Clear_Button_clicked();

    void on_Select_Button_clicked();

    void on_Group_Button_clicked();

    void on_UnGroup_Button_clicked();

    void on_New_Page_Button_clicked();

    void on_Bucket_Button_clicked();

    void on_Cut_Button_clicked();

    void on_Copy_Button_clicked();

    void on_Paste_Button_clicked();


    void on_Save_Button_clicked();

    void on_Open_Button_clicked();

    void on_delete_button_clicked();

    void on_Page_1_clicked();

    void on_Page_2_clicked();

    void on_Page_3_clicked();

    void on_Page_4_clicked();

    void on_Page_5_clicked();

    void on_Page_6_clicked();

    void on_Page_7_clicked();

    void on_Page_8_clicked();

    void on_Page_9_clicked();

    void on_Page_10_clicked();

    void on_Page_11_clicked();

    void on_Page_12_clicked();

    void on_Page_13_clicked();

    void on_Page_14_clicked();

    void on_Page_15_clicked();

    void on_Page_16_clicked();

    void on_Page_17_clicked();

    void on_Page_18_clicked();

    void on_Page_19_clicked();

    void on_Page_20_clicked();


    void on_Undo_Button_clicked();

    void on_Redo_Button_clicked();

    void on_Components_Table_cellClicked(int row, int column);

    void on_Text_Button_clicked();

    void on_Font_Family_Combo_Box_currentTextChanged(const QString &arg1);

  //  void on_Font_Size_Combo_Box_currentIndexChanged(const QString &arg1);

    void on_Font_Size_Combo_Box_currentTextChanged(const QString &arg1);

    void on_Bold_Button_clicked(bool checked);

    void on_Italic_Button_clicked(bool checked);

    void on_Underline_Button_clicked(bool checked);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
