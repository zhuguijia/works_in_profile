#include "dialog.h"

/***********************************************************************
* 			全局变量                                                    *
***********************************************************************/
ifstream infile;
ofstream outfile;
STR*currentPtr=NULL,*lastPtr=NULL;
QByteArray ba;

/*
************************************************************************
* 函数名称: Modify		  	    				    			       *
* 描   述: 光标处理                                                      *
* 版   本：beta 2.1                                                    *
* 新版本更新内容：1.10 新添调用ifBetweenChineseMid                         *
*               1.11 解决部分空白点击崩溃bug                              *
*               2.1 取消调用，解决了右翻页持续的bug                        *
* 备   注：                                                             *
************************************************************************
*/
void Modify(){
    int i;
    STR* hahaPtr=S->headPtr;
    STR* previousPtr=NULL;
    //cout<<"1y="<<S->signal_y<<endl;
    for(i=0;i<((S->signal_y-pos_y_above)/distance_y)+S->num_of_row;i++){
        if(hahaPtr==NULL || hahaPtr->nextPtr==NULL)
        {   //cout<<"1"<<endl;
            if(previousPtr!=NULL)
            {
                cout<<"1"<<endl;
                S->signal_y=pos_y_above+i*distance_y;
            }
            if(hahaPtr==NULL)
            {
                cout<<"2"<<endl;
                S->signal_y=pos_y_above;
                S->signal_x=pos_x_left-3;
            }
            else if(hahaPtr->nextPtr==NULL)
            {
                cout<<"3"<<endl;
                S->signal_y=pos_y_above+i*distance_y;
            }
            break;
        }
        previousPtr=hahaPtr;
        hahaPtr=hahaPtr->nextPtr;
    }
    if(hahaPtr!=NULL&&hahaPtr->number<(S->signal_x-(pos_x_left-3))/distance_x){
        //cout<<hahaPtr->number<<endl;
            S->signal_x=hahaPtr->number*distance_x+pos_x_left-3;
    }
    else if(hahaPtr==NULL)
    {
        S->signal_x=pos_x_left-3;
    }
    hahaPtr=S->headPtr;
    for(i=0;i<((S->signal_y1-pos_y_above)/distance_y)+S->num_of_row;i++){
        cout<<"4"<<endl;
        if(hahaPtr==NULL || hahaPtr->nextPtr==NULL)
        {
            cout<<"1"<<endl;
            if(previousPtr!=NULL)
            {
                S->signal_y1=pos_y_above+i*distance_y;
            }
            if(hahaPtr==NULL)
            {
                S->signal_y1=pos_y_above;
                S->signal_x1=pos_x_left-3;
            }
            break;
        }
         previousPtr=hahaPtr;
         hahaPtr=hahaPtr->nextPtr;
        }
    if(hahaPtr!=NULL&&hahaPtr->number<(S->signal_x1-(pos_x_left-3))/distance_x){
        cout<<"2"<<endl;
           S->signal_x1=hahaPtr->number*distance_x+(pos_x_left-3);
       }
    else if(hahaPtr==NULL)
    {
        S->signal_x1=pos_x_left-3;
    }
    if(S->signal_x<pos_x_left-3){
        S->signal_x=pos_x_left-3;
    }
    if(S->signal_x1<pos_x_left-3){
         cout<<"3"<<endl;
        S->signal_x1=pos_x_left-3;
    }

    ifBetweenChineseMid((S->signal_y-pos_y_above)/distance_y+S->num_of_row,(S->signal_x-(pos_x_left-3))/distance_x+S->num_of_col,0);
}


/*
************************************************************************
* 函数名称: Read			  	    				    			       *
* 描   述: 读取一个文件                                                   *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                        *
* 备   注：                                                             *
************************************************************************
*/
void Read(){
    S->max_length=0;//改
    S->max_height=0;//gai
    QString file = QFileDialog::getOpenFileName(
                NULL,
                "Open Document",
                QDir::currentPath(),
                "Document files (*.doc *.rtf);;All files(*.*)");
    if (!file.isNull()) { //用户选择了文件
               // 处理文件
               QMessageBox::information(NULL, "Document", "Has document", QMessageBox::Ok | QMessageBox::Cancel);
    } else // 用户取消选择
               QMessageBox::information(NULL, "Document", "No document", QMessageBox::Ok | QMessageBox::Cancel);
    ba = file.toLocal8Bit();
    S->temp = ba.data();
    cout<<S->temp;
    S->headPtr=(STR*)malloc(sizeof(STR));
    currentPtr=S->headPtr;
    lastPtr=S->headPtr;
    S->headPtr->data=NULL;
    S->headPtr->number=0;
    S->headPtr->nextPtr=NULL;
    fflush(stdin);
    infile.open(S->temp,ios::in);
    cout<<S->temp;
    if(infile==NULL) {cout<<"Failed"<<endl;free(S->temp);
        S->temp=NULL;}
    int num=1;
    int flag=num;
    char a;
    //array* pNew=NULL;
    while(!infile.eof()){
        currentPtr->data=(char*)realloc(currentPtr->data,(num*80)*sizeof(char));
        for(int i=0;i<=79;i++){
            a=infile.get();
            if(a!=EOF){
                currentPtr->data[(num-1)*80+i]=a;
                currentPtr->number++;
                if(currentPtr->number>S->max_length) S->max_length=currentPtr->number;
            }
            if(a==EOF||a=='\n'||a=='\0') break;
        }
        if(a!=EOF&&a!='\n'&&a!='\0'){
            flag=num;
            num++;
        }
        else if(a==EOF) {
        flag=num;
        break;
        }
        if(a=='\n'){
            if(a)
            num=1;
            S->max_height++;//加
            currentPtr=(STR*)malloc(sizeof(STR));
            currentPtr->data=NULL;
            currentPtr->number=0;
            lastPtr->nextPtr=currentPtr;
            lastPtr=currentPtr;
            lastPtr->nextPtr=NULL;
            flag=num;
        }
    }
    infile.close();
}

/*
************************************************************************
* 函数名称: Save			  	    				    			       *
* 描   述: 保存文件和另存文件                                              *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                        *
* 备   注：                                                             *
************************************************************************
*/
void Save(){
    if(S->temp==NULL||S->isSaveasPress==1){
    QString fileName = QFileDialog::getSaveFileName(NULL,
            "Open Config",
             "new",
            " (*.txt)");
    ba = fileName.toLocal8Bit();
    S->temp=NULL;
    S->temp = ba.data();
    }
    outfile.open(S->temp,ios::trunc);
    if(outfile==NULL) {
        QMessageBox::information(NULL, "Document", "open failed!!", QMessageBox::Ok | QMessageBox::Cancel);
        if(S->temp!=NULL)
        free(S->temp);
        S->temp=NULL;
        return;
    }
    STR* notePtr=NULL;
    notePtr=S->headPtr;
    while(notePtr!=NULL){
        for(int i=0;i<=notePtr->number-1;i++){
        outfile<<notePtr->data[i];
        //cout<<notePtr->data[i];
       }
        notePtr=notePtr->nextPtr;
    }
    outfile.close();
}

/*
************************************************************************
* 函数名称: New			  	    				    			       *
* 描   述: 新建文件                                                      *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void New()
{
   STR* notePtr=S->headPtr;
    while(notePtr!=NULL)
    {
        free(notePtr->data);
        notePtr=notePtr->nextPtr;
        free(S->headPtr);
        S->headPtr=notePtr;
    }
    S->headPtr=NULL;
    S->temp=NULL;
    S->signal_x=pos_x_left-3;
    S->signal_y=pos_y_above;
    S->max_height=0;
    S->max_length=0;
    S->signal_x1=pos_x_left-3;
    S->signal_y1=pos_y_above;
}
