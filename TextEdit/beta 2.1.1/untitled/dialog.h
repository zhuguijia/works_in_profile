#ifndef DIALOG_H
#define DIALOG_H
#include<iostream>
#include<fstream>
#include <QDialog>
#include <QApplication>
#include<windows.h>
#include <malloc.h>
#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<QFileDialog>
#include<QMessageBox>
#include<QInputDialog>
#include <QPixmap>
#include <Qpainter>
#include <QtGui>
#include <QString>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <iomanip>
#include <time.h>
#include <qdebug.h>
using namespace std;

#define distance_x 6
#define distance_y 20
#define pos_y_above 100
#define pos_x_left 100
#define num_per_line 160
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * e);
    explicit Dialog(QWidget *parent = 0);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    ~Dialog();







private slots:
    void on_textEdit_textChanged();

    void on_horizontalScrollBar_sliderMoved(int position);

    void on_verticalScrollBar_sliderMoved(int position);

private:
    Ui::Dialog *ui;
    QPixmap pix,pix1,pix2,pix3,pix31,pix51,pix5,pix4,pix6,pix8,pix10,pix7,pix9,pix11,pix12;
};
typedef struct STR{
    char *data;
    int number;
    struct STR*nextPtr;
}STR;
typedef struct V{
    int xpos,ypos;
    int signal_x,signal_y,signal_x1,signal_y1;
    int num_of_row,num_of_col;
    STR *headPtr;
    char insertChar;
    char *temp;
    bool isMousePress;
    bool isBlock;
    bool ifOpenPress;
    bool ifSavePress;
    bool ifCopyPress;
    bool ifStickPress;
    bool ifCutPress;
    bool ifFilePress;
    bool ifEditorPress;
    bool isSaveasPress;
    int counter; 
    int max_length;//加
    int max_height;//加
    int current_xbar_pos;//jia
    int current_ybar_pos;//jia
    //QString color;
}Parameter;
extern Parameter*S;
//ifstream infile;
//ofstream outfile;
extern void Read();
extern void searchSTR(int row,int col);
extern void Next(char [],int len);
extern int  kmp(char [], int, std::string, int, int);
extern void changeSTR(int,int);
extern void enterSTR(int,int);
extern void insertSTR(int,int);
extern void deleteSTR(int,int);
extern void blockDelete(int,int,int,int);
extern void blockStick(int,int);
extern void blockCopy(int,int,int,int);
extern void Save();
extern void Modify();
extern void selectAll();
extern void New();
extern void ifBetweenChineseMid(int ,int ,int);
extern int ifBetweenChineseMid1(int row,int col);
extern void printResult(double);
extern void goBack();
extern void storeCopy();
extern ifstream infile;
extern ofstream outfile;
extern STR*currentPtr;
extern STR*lastPtr;

#endif // DIALOG_H
