#include "dialog.h"
#include "ui_dialog.h"
#include<QDebug>
using namespace std;
Dialog::Dialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    pix1.load("signal.png");
    pix.load("background.jpg");
    pix2.load("OpenMenu.png");
    pix4.load("SaveMenu.png");
    pix11.load("SaveAsMenu.png");
    pix12.load("NewMenu.png");
    pix6.load("CopyMenu.png");
    pix8.load("StickMenu.png");
    pix10.load("CutMenu.png");
    pix7.load("SearchMenu.png");
    pix9.load("ChangeMenu.png");
    pix3.load("FilePress.png");
    pix31.load("FileRelease.png");
    pix5.load("EditorPress.png");
    pix51.load("EditorRelease.png");
    this->resize(1155,650);
}

/*
************************************************************************
* 函数名称: paintEvent	  		        						       *
* 描   述: 贴图函数                                                      *
* 版   本：beta 2.1                                                     *
* 新版本更新内容：beta 1.9 更新贴图，解决卡顿bug,增加中文识别                 *
*               beta 2.1 更改蓝条宽度                                    *
* 备   注：                                                             *
************************************************************************
*/
void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),pix);
    ui->horizontalScrollBar->setMaximum(S->max_length);//jia
    ui->verticalScrollBar->setMaximum(S->max_height);//jia
    ui->horizontalScrollBar->setSliderPosition(S->num_of_col);
    ui->verticalScrollBar->setSliderPosition(S->num_of_row);
        if(S->ifFilePress)
            painter.drawPixmap(10,10,80,70,pix3);
        else
            painter.drawPixmap(10,10,80,70,pix31);
        if(S->ifEditorPress)
            painter.drawPixmap(100,10,80,70,pix5);
        else
            painter.drawPixmap(100,10,80,70,pix51);
        if(S->ifFilePress){
            painter.drawPixmap(200,10,70,60,pix2);
            painter.drawPixmap(280,10,70,60,pix4);
            painter.drawPixmap(360,10,70,60,pix11);
            painter.drawPixmap(440,10,70,60,pix12);
        }
        else if(S->ifEditorPress){
            painter.drawPixmap(200,10,70,60,pix6);
            painter.drawPixmap(280,10,70,60,pix8);
            painter.drawPixmap(360,10,70,60,pix10);
            painter.drawPixmap(440,10,70,60,pix7);
            painter.drawPixmap(520,10,70,60,pix9);
        }


    if(S->isBlock){
        if(S->signal_y==S->signal_y1)
        painter.drawPixmap(S->signal_x+3,S->signal_y-12,S->signal_x1-S->signal_x,15,pix1);
        else if(S->signal_y1>S->signal_y){
            STR* locPtr=S->headPtr;
            for(int i=0;i<((S->signal_y-pos_y_above)/distance_y)+S->num_of_row;i++){
                if(locPtr==NULL) break;
                else locPtr=locPtr->nextPtr;
            }
            if(locPtr->number-S->num_of_col<num_per_line&&locPtr->number-S->num_of_col>0)
                painter.drawPixmap(S->signal_x+3,S->signal_y-12,(locPtr->number-S->num_of_col)*distance_x,15,pix1);
            else if(locPtr->number-S->num_of_col>0)
                painter.drawPixmap(S->signal_x+3,S->signal_y-12,(num_per_line)*distance_x,15,pix1);
            locPtr=locPtr->nextPtr;
            for(int i=((S->signal_y-pos_y_above)/distance_y);i<((S->signal_y1-pos_y_above)/distance_y)-1;i++){
                if(locPtr==NULL) break;
                else{
                    if(locPtr->number-S->num_of_col<num_per_line&&locPtr->number-S->num_of_col>0)
                        painter.drawPixmap(pos_x_left,((i+1)*distance_y+pos_y_above)-12,(locPtr->number-S->num_of_col)*distance_x,15,pix1);
                    else if(locPtr->number-S->num_of_col>0)
                        painter.drawPixmap(pos_x_left,((i+1)*distance_y+pos_y_above)-12,num_per_line*distance_x,15,pix1);
                    locPtr=locPtr->nextPtr;
                }
            }
            if(locPtr!=NULL){
                painter.drawPixmap(pos_x_left,S->signal_y1-12,S->signal_x1-pos_x_left-S->num_of_col,15,pix1);
            }
        }
    }
    STR* notePtr=NULL,*signPtr=NULL;
    notePtr=S->headPtr;
    for(int i=1;i<=S->num_of_row;i++){
        notePtr=notePtr->nextPtr;
    }
    signPtr=notePtr;
    S->ypos=pos_y_above;
    int row=0;
    while(notePtr!=NULL&&row<=20){
        row++;
        notePtr->data[notePtr->number]='\0';
        if(notePtr->number>S->num_of_col){
            for(int i=S->num_of_col;i<=num_per_line+S->num_of_col;i++){
                if(i==S->num_of_col){
                    if(ifBetweenChineseMid1(row+S->num_of_row-1,i)){
                        painter.drawText(S->xpos,S->ypos," ");
                        i++;
                        S->xpos+=distance_x;
                    }
                }
                if(notePtr->data[i]=='\0'){
                    painter.drawText(S->xpos,S->ypos,QString(QString::fromLocal8Bit(notePtr->data+i,1)));
                    S->xpos+=distance_x;
                    break;
                }
                else{
                    if(notePtr->data[i]>=0){
                        painter.drawText(S->xpos,S->ypos,QString(QString::fromLocal8Bit(notePtr->data+i,1)));
                        S->xpos+=distance_x;
                    }
                    else{
                        painter.drawText(S->xpos,S->ypos,QString(QString::fromLocal8Bit(notePtr->data+i,2)));
                        S->xpos+=2*distance_x;
                        i++;
                    }
                }
            }
        }
        S->ypos+=distance_y;
        S->xpos=pos_x_left;
        notePtr=notePtr->nextPtr;
    }
    if(S->signal_y>(pos_y_above+(distance_y)*20)){
        if(row==21){
        S->num_of_row++;
        S->signal_y-=distance_y;
        }
        else S->signal_y-=distance_y;
    }
    else if(S->signal_y<pos_y_above){
        if(S->num_of_row>0){
            S->num_of_row--;
            S->signal_y+=distance_y;
        }
        else S->signal_y+=distance_y;
    }
    else if((S->signal_y-pos_y_above)/distance_y+S->num_of_row>S->max_height){
        while((S->signal_y-pos_y_above)/distance_y+S->num_of_row>S->max_height){
            S->signal_y-=distance_y;
        }
    }
    if(S->signal_y1>(pos_y_above+(distance_y)*20)){
        if(row==21){
        S->num_of_row++;
        S->signal_y1-=distance_y;
        }
        else S->signal_y1-=distance_y;
    }
    else if(S->signal_y1<pos_y_above){
        if(S->num_of_row>0){
            S->num_of_row--;
            S->signal_y1+=distance_y;
        }
        else S->signal_y1+=distance_y;
    }
    else if((S->signal_y1-pos_y_above)/distance_y+S->num_of_row>S->max_height){
        while((S->signal_y1-pos_y_above)/distance_y+S->num_of_row>S->max_height){
            S->signal_y1-=distance_y;
        }
    }
    int sign=1;
    while(signPtr!=NULL&&sign<=(S->signal_y-pos_y_above)/distance_y){
        signPtr=signPtr->nextPtr;
        sign++;
    }
    if(S->signal_x>(pos_x_left-3+(distance_x)*num_per_line)){
        if(signPtr->number-S->num_of_col>num_per_line){
            S->num_of_col++;
            S->signal_x-=distance_x;
        }
        else
            S->signal_x-=distance_x;
    }
    else if(S->signal_x<pos_x_left-3){
        if(S->num_of_col>0){
            S->num_of_col--;
            S->signal_x+=distance_x;
        }
        else
            S->signal_x+=distance_x;
    }
    if(S->signal_x1>(pos_x_left-3+(distance_x)*num_per_line)){
        if(signPtr->number-S->num_of_col>num_per_line){
            S->num_of_col++;
            S->signal_x1-=distance_x;
        }
        else
            S->signal_x1-=distance_x;
    }
    else if(S->signal_x1<pos_x_left-3){
        if(S->num_of_col>0){
            S->num_of_col--;
            S->signal_x1+=distance_x;
        }
        else
            S->signal_x1+=distance_x;
    }
    S->counter=(S->counter+1)%(1000/50);
    if(S->counter<=0.5*(1000/50)){
        painter.setPen(QColor("red"));
        painter.drawText(S->signal_x,S->signal_y,"|");
        //painter.setPen(QColor(S->color));
    }
    Modify();
}



/*
************************************************************************
* 函数名称: mousePressEvent 		        						       *
* 描   述: 接收鼠标按下事件                                               *
* 版   本：beta 2.1                                                    *
* 新版本更新内容：2.1 加上了判断是否在中间                                                       *
* 备   注：                                                             *
************************************************************************
*/

void Dialog::mousePressEvent(QMouseEvent * event){
    if(event->pos().x()<=90&&event->pos().x()>=10&&event->pos().y()<=80&&event->pos().y()>=10){
        S->ifFilePress=1;
        S->ifEditorPress=0;
        //Read();
    }
    else if(event->pos().y()>pos_y_above-10){
        S->isMousePress=1;
        S->ifFilePress=0;
        S->ifEditorPress=0;
        S->isBlock=0;
        S->signal_x=((event->pos().x()-(pos_x_left-3))/distance_x)*distance_x+pos_x_left-3;
        S->signal_y=((event->pos().y()-pos_y_above+10)/distance_y)*distance_y+pos_y_above;
    }
    else if(event->pos().x()<=180&&event->pos().x()>=100&&event->pos().y()<=80&&event->pos().y()>=10){
        S->ifEditorPress=1;
        S->ifFilePress=0;
        //Save();
    }
    else if(event->pos().x()<=270&&event->pos().x()>=200&&event->pos().y()<=70&&event->pos().y()>=10){
        if(S->ifFilePress){
            S->ifOpenPress=1;
            Read();
        }
        else if(S->ifEditorPress){
            S->ifCopyPress=1;
            blockCopy((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1+S->num_of_col);
        }
        //S->ifStickPress=1;
        //blockStick((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x);
    }
    else if(event->pos().x()<=350&&event->pos().x()>=280&&event->pos().y()<=70&&event->pos().y()>=10){
        if(S->ifFilePress){
            S->ifSavePress=1;
            Save();
        }
        else if(S->ifEditorPress){
            S->ifStickPress=1;
            blockStick((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
        }
        //S->ifCutPress=1;
        //blockCopy((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1);
        //blockDelete((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1);
        //S->isBlock=0;
    }
    else if(event->pos().x()<=430&&event->pos().x()>=360&&event->pos().y()<=70&&event->pos().y()>=10){
        if(S->ifEditorPress){
            S->ifCutPress=1;
            blockCopy((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1+S->num_of_col);
            blockDelete((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1+S->num_of_col);
            S->isBlock=0;
        }
        else if(S->ifFilePress){
            S->isSaveasPress=1;
            Save();
            S->isSaveasPress=0;
        }
        //S->ifCopyPress=1;
        //blockCopy((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1);
    }
    else if(event->pos().x()<=510&&event->pos().x()>=440&&event->pos().y()<=70&&event->pos().y()>=10){
        if(S->ifEditorPress)
        searchSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
        else if(S->ifFilePress){
            New();
        }
    }
    else if(event->pos().x()<=590&&event->pos().x()>=520&&event->pos().y()<=70&&event->pos().y()>=10){
        if(S->ifEditorPress)
            changeSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
    }
    ifBetweenChineseMid((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,0);
}

void Dialog::mouseMoveEvent(QMouseEvent *event){
    S->isBlock=1;
    if(event->pos().y()>=pos_y_above-10&&S->isMousePress==1){
    S->signal_x1=((event->pos().x()-(pos_x_left-3))/distance_x)*distance_x+(pos_x_left-3);
    S->signal_y1=((event->pos().y()-pos_y_above+10)/distance_y)*distance_y+pos_y_above;
    ifBetweenChineseMid((S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x+S->num_of_col,2);
    }
}

/*
************************************************************************
* 函数名称: mouseReleaseEvent		        						       *
* 描   述: 接收鼠标放开事件                                               *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void Dialog::mouseReleaseEvent(QMouseEvent *event){
    S->ifOpenPress=0;
    S->ifSavePress=0;
    S->ifCopyPress=0;
    S->ifStickPress=0;
    S->ifCutPress=0;
    S->isMousePress=0;
    if(S->isBlock&&event->pos().y()>=pos_y_above){
    S->signal_x1=((event->pos().x()-(pos_x_left-3))/distance_x)*distance_x+(pos_x_left-3);
    S->signal_y1=((event->pos().y()-pos_y_above+10)/distance_y)*distance_y+pos_y_above;
    ifBetweenChineseMid((S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x+S->num_of_col,2);
    }
}
void Dialog::wheelEvent(QWheelEvent * e){
    if(e->delta()<0){
        if(S->num_of_row<S->max_height) S->num_of_row++;
    }
    else if(e->delta()>0){
        if(S->num_of_row>0) S->num_of_row--;
    }
}

/*
************************************************************************
* 函数名称: keyPressEvent 		        						       *
* 描   述: 接收键盘按下事件                                               *
* 版   本：beta 1.10                                                    *
* 新版本更新内容：1.10 新添调用ifBetweenChineseMid                         *
* 备   注：                                                             *
************************************************************************
*/
bool Dialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    //cout<<"1_"<<endl;
    //S->ifFilePress=0;
    //S->ifEditorPress=0;
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    //cout<<msg->message<<' '<<VK_UP<<endl;
    if(msg->message==WM_KEYDOWN){
    if(msg->wParam==VK_UP){
        S->isBlock=0;
        S->signal_y-=distance_y;
        ifBetweenChineseMid((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,0);
        return 1;
    }
    else if(msg->wParam==VK_DOWN){
        S->isBlock=0;
        S->signal_y+=distance_y;
        //cout<<"1_"<<endl;
        ifBetweenChineseMid((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,0);
        //cout<<"2_"<<endl;
        return 1;
    }
    else if(msg->wParam==VK_LEFT){
        S->isBlock=0;
        S->signal_x-=distance_x;
        ifBetweenChineseMid((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,-1);
        return 1;
    }
    else if(msg->wParam==VK_RIGHT){
        S->signal_x+=distance_x;
        ifBetweenChineseMid((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,1);
        return 1;
    }
    else if(msg->wParam=='F'&&::GetKeyState(VK_CONTROL) < 0){
        searchSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
        return 1;
    }
    else if(msg->wParam=='R'&&::GetKeyState(VK_CONTROL) < 0){
        changeSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
        return 1;
    }
    else if(msg->wParam=='A'&&::GetKeyState(VK_CONTROL) < 0){
            selectAll();
            return 1;
        }
    else if(msg->wParam==VK_BACK){
        if(S->isBlock==0){
        if(S->signal_x==pos_x_left-3&&S->num_of_col==0){
            deleteSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,-1);
            S->max_height--;
            S->signal_y-=distance_y;
        }
        else{
        deleteSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x-1+S->num_of_col);
        S->signal_x-=distance_x;
        if(ifBetweenChineseMid1((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col)){
            deleteSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x-1+S->num_of_col);
            S->signal_x-=distance_x;
        }
        }
        }
        else{
            blockDelete((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1+S->num_of_col);
            S->isBlock=0;
        }
        return 1;
    }
    else if(msg->wParam=='Z'&&::GetKeyState(VK_CONTROL) < 0){

        goBack();
        return 1;
    }
    else if(msg->wParam=='C'&&::GetKeyState(VK_CONTROL) < 0&&S->isBlock){

        blockCopy((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1+S->num_of_col);
        return 1;
    }
    else if(msg->wParam=='V'&&::GetKeyState(VK_CONTROL) < 0){
        blockStick((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
        return 1;
    }
    else if(msg->wParam=='X'&&::GetKeyState(VK_CONTROL) < 0&&S->isBlock){
        blockCopy((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1+S->num_of_col);
        blockDelete((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,(S->signal_y1-pos_y_above)/distance_y+S->num_of_row,(S->signal_x1-(pos_x_left-3))/distance_x-1+S->num_of_col);
        S->isBlock=0;
        return 1;
    }

    else if(msg->wParam==VK_DELETE){
        deleteSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
        if(ifBetweenChineseMid1((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col+1)){
            deleteSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
            }
        return 1;
    }
    }
    return 0;
}


Dialog::~Dialog()
{
    delete ui;
}
void Dialog::on_textEdit_textChanged()
{
    QString tmp = ui->textEdit->toPlainText();
    QByteArray fa = tmp.toLocal8Bit();
    char* str;
    str=fa.data();
    int k;
    if(str[0]>=0) k=tmp.length();
    else k=2*tmp.length();
    if(str[0]==10){
        enterSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x-1+S->num_of_col);
        S->signal_x=pos_x_left-3;
        S->num_of_col=0;
        S->signal_y+=distance_y;
        S->max_height++;
    }
    else{
    for(int i=1;i<=k;i++){
        S->insertChar=str[i-1];
        insertSTR((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col);
        S->signal_x+=distance_x;
    }
    }
    if(str[0])ui->textEdit->clear();
}
void Dialog::on_horizontalScrollBar_sliderMoved(int position)
{
            S->num_of_col=ui->horizontalScrollBar->sliderPosition();
}
void Dialog::on_verticalScrollBar_sliderMoved(int position)
{
            S->num_of_row=ui->verticalScrollBar->sliderPosition();
}
