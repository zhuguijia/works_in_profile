#include "dialog.h"
using namespace std;

/***********************************************************************
* 			全局变量                                                    *
***********************************************************************/
Dialog*w;
Parameter*S;

/***********************************************************************
* 			线程                                                       *
***********************************************************************/
DWORD WINAPI Print(LPVOID lpParamter){
    while(1){
        w->update();
        Sleep(50);
    }
}

/***********************************************************************
* 			主函数                                                      *
***********************************************************************/
int main(int argc, char *argv[])
{
    S=(Parameter*)malloc(sizeof(Parameter));
    S->num_of_row=0;
    S->num_of_col=0;
    S->isBlock=0;
    S->headPtr=NULL;
    S->signal_x=pos_x_left-3;
    S->signal_y=pos_y_above;
    S->signal_x1=pos_x_left-3;
    S->signal_y1=pos_y_above;
    S->ifOpenPress=0;
    S->ifSavePress=0;
    S->ifCopyPress=0;
    S->ifStickPress=0;
    S->ifCutPress=0;
    S->counter=0;
    S->headPtr=NULL;
    S->ifEditorPress=0;
    S->ifFilePress=0;
    S->isSaveasPress=0;
    S->temp=NULL;
    //S->color="black";
    S->max_length=0;//加
    S->max_height=0;//jia
    S->current_xbar_pos=0;//加
    S->current_ybar_pos=0;//加
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QApplication a(argc, argv);
    Dialog w_temp;
    w=&w_temp;
    w->show();
    DWORD WINAPI ChangeCursor(LPVOID lpParamter);
    HANDLE hThread2;
    hThread2=CreateThread(NULL,0,Print,NULL,0,NULL);
    CloseHandle(hThread2);
    return a.exec();
}
