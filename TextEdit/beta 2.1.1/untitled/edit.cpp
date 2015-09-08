#include "dialog.h"


/***********************************************************************
* 			全局变量                                                    *
***********************************************************************/
int *next1;
string oldString;



/***********************************************************************
* 			测试时间                                                    *
***********************************************************************/
/*inline unsigned long long GetNTime()
{
       __asm ("RDTSC");
}


double  duration;

LARGE_INTEGER BegainTime;
LARGE_INTEGER EndTime;
LARGE_INTEGER Frequency;
*/
/*
************************************************************************
* 函数名称: enterSTR			  					    			       *
* 描   述: 在某一个位置插入回车符                                          *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void enterSTR(int row,int col)
{
    storeCopy();
    STR *nowPtr=S->headPtr,*newPtr=NULL;
    int i,j;
    int tempNum;
    int numberOf80;

    while(row>0)
    {
        nowPtr=nowPtr->nextPtr;
        row--;
    }

    tempNum=nowPtr->number-col;
    numberOf80=tempNum/80+1;


    //申请内存
    newPtr=(STR*)malloc(sizeof(STR));
    newPtr->data=(char*)malloc((numberOf80*80)*sizeof(char));
    //行链接
    newPtr->nextPtr=nowPtr->nextPtr;
    nowPtr->nextPtr=newPtr;
    newPtr->number=tempNum-1;
    for(i=col+1,j=0;i<=nowPtr->number;i++,j++)
    {
        newPtr->data[j]=nowPtr->data[i];
    }
    nowPtr->number=col+2;
    nowPtr->data=(char*)realloc(nowPtr->data,nowPtr->number*sizeof(char));
    nowPtr->data=(char*)realloc(nowPtr->data,(nowPtr->number/80+1)*80*sizeof(char));
    nowPtr->data[nowPtr->number-1]='\n';
}



/*
************************************************************************
* 函数名称: insertSTR			  					    			       *
* 描   述: 在指定位置插入一个字符                                          *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void insertSTR(int row,int col)
{
    storeCopy();
    STR *nowPtr;
    int i;
    if(S->headPtr==NULL){
        S->headPtr=(STR*)malloc(sizeof(STR));
        S->headPtr->number=0;
        S->headPtr->data=(char*)malloc(sizeof(char)*80);
        S->headPtr->nextPtr=NULL;
    }
    nowPtr=S->headPtr;
    while(row>0)
    {
        nowPtr=nowPtr->nextPtr;
        row--;
    }

    if(nowPtr->number%80==0)//要申请内存
    {
        nowPtr->data=(char*)realloc(nowPtr->data,(nowPtr->number+80)*sizeof(char));
    }

    for(i=nowPtr->number;i>=col;i--)
    {
        nowPtr->data[i+1]=nowPtr->data[i];
    }

    nowPtr->data[col]=S->insertChar;
    nowPtr->number+=1;
}

/*
************************************************************************
* 函数名称: deleteSTR			  					    			       *
* 描   述: 删除某一位置的单个字符                                          *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void deleteSTR(int row,int col)
{
    storeCopy();
    STR *nowPtr=S->headPtr,*prePtr=NULL;
    int i,j;
    if(col==-1 && row!=0)
    {
        while(row>0)
        {
            prePtr=nowPtr;
            nowPtr=nowPtr->nextPtr;
            row--;
        }

        prePtr->data=(char*)realloc(prePtr->data,((prePtr->number+nowPtr->number)/80+1)*80*sizeof(char));
        //cout<<prePtr->data[prePtr->number]<<endl;
        for(i=prePtr->number-1,j=0;i<=prePtr->number+nowPtr->number;i++,j++)
        {
            prePtr->data[i]=nowPtr->data[j];
        }
        S->signal_x=(prePtr->number-1)*distance_x+pos_x_left-3;
        prePtr->number+=nowPtr->number-1;
        prePtr->nextPtr=nowPtr->nextPtr;
        free(nowPtr);
    }
    else if(col==-1 && row==0)
    {
        //无操作
    }
    else
    {
        while(row>0)
        {
            nowPtr=nowPtr->nextPtr;
            row--;
        }

        for(i=col;i<=nowPtr->number;i++)
        {
            nowPtr->data[i]=nowPtr->data[i+1];
        }
        nowPtr->number--;
        //cout<<nowPtr->data;
    }
}

/*
************************************************************************
* 函数名称: blockCopy				  								       *
* 描   述: 对一块内存进行拷贝                                             *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void blockCopy(int start_row,int start_col,int end_row,int end_col)
{
    ofstream file("storeCopy.txt",ios_base::trunc);

    STR *startPtr=S->headPtr,*endPtr=S->headPtr,*tempPtr=NULL;
    int i,j;

    if(start_row>end_row)
       cout<<"ERROR"<<endl;
    else if(start_row==end_row)
    {
        while(start_row>0)
        {
            startPtr=startPtr->nextPtr;
            start_row--;
        }

        for(i=start_col;i<=end_col;i++)
        {
            file<<startPtr->data[i];
        }
    }
    else
    {
        while(start_row>0)
        {
            startPtr=startPtr->nextPtr;
            start_row--;
        }

        while(end_row>0)
        {
            endPtr=endPtr->nextPtr;
            end_row--;
        }

        for(i=start_col;i<startPtr->number;i++)
        {
            file<<startPtr->data[i];
        }
        //file<<'\n';
        while(startPtr->nextPtr!=endPtr)
        {
            startPtr=startPtr->nextPtr;
            for(i=0;i<startPtr->number;i++)
            {
                file<<startPtr->data[i];
            }
            //file<<'\n';
        }
        startPtr=startPtr->nextPtr;
        for(i=0;i<=end_col;i++)
        {
            file<<startPtr->data[i];
        }
    }

    file.close();

}

/*
************************************************************************
* 函数名称: blockStick			  								       *
* 描   述: 在指定位置粘贴之前拷贝的内容                                     *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void blockStick(int row,int col)
{
    storeCopy();
    ifstream file("storeCopy.txt");

    STR *nowPtr=S->headPtr,*tempPtr=NULL;
    int i,j;
    char * restData;
    char tempData;
    int * tempNumber;
    int tempLine=0;
    int restDataNumber=0;

    while(row>0)
    {
        nowPtr=nowPtr->nextPtr;
        row--;
    }

    restData=(char*)malloc((nowPtr->number-col+1)*sizeof(char));
    for(i=col,j=0;i<nowPtr->number;i++,j++)
    {
        restData[j]=nowPtr->data[i];
        restDataNumber++;
    }

    tempNumber=(int*)malloc(sizeof(int));
    tempNumber[0]=0;

    if(file)
    {
        //遍历一遍，计算有多少行，每一行有多少数
        while(!file.eof())
        {
            tempData=file.get();

            if(tempData!='\n' && tempData!=-1)
            {
                tempNumber[tempLine]++;
            }
            else if(tempData=='\n')
            {
                tempLine++;
                tempNumber=(int*)realloc(tempNumber,(tempLine+1)*sizeof(int));
                tempNumber[tempLine]=0;
            }
        }
    }

    file.clear();
    file.seekg(0,ios_base::beg);
        if(tempLine==0)
        {
            nowPtr->number+=(tempNumber[tempLine]);
            nowPtr->data=(char*)realloc(nowPtr->data,(nowPtr->number/80+1)*80*sizeof(char));

            i=col;
            while(i<=col+tempNumber[tempLine]-1)
            {
                tempData=file.get();
                nowPtr->data[i]=tempData;
                i++;
            }

            j=0;
            while(i<nowPtr->number)
            {
                nowPtr->data[i]=restData[j];
                i++;
                j++;
            }
            nowPtr->data[nowPtr->number-1]='\0';

        }//if end
        else if(tempLine>0)
        {
            nowPtr->number+=(tempNumber[0]-restDataNumber+1);
            nowPtr->data=(char*)realloc(nowPtr->data,(nowPtr->number/80+1)*80*sizeof(char));
            i=col;
            while(i<=col+tempNumber[0])
            {
                tempData=file.get();
                if(tempData!='\n')nowPtr->data[i]=tempData;
                else nowPtr->data[i]='\0';
                i++;
            }

            for(i=1;i<=tempLine;i++)
            {
                tempPtr=(STR*)malloc(sizeof(STR));
                if(i!=tempLine)
                    tempPtr->number=tempNumber[i]+1;
                else
                    tempPtr->number=tempNumber[i]+restDataNumber;

                tempPtr->data=(char*)malloc((tempPtr->number/80+1)*80*sizeof(char));

                tempPtr->nextPtr=nowPtr->nextPtr;
                nowPtr->nextPtr=tempPtr;
                nowPtr=tempPtr;
                if(i==tempLine)
                {
                    for(j=0;j<tempNumber[i];j++)
                    {
                        tempData=file.get();
                        nowPtr->data[j]=tempData;
                    }

                    for(int k=0;k<restDataNumber;k++,j++)
                    {
                        nowPtr->data[j]=restData[k];
                    }
                    nowPtr->data[j]='\0';
                }
                else
                {
                    for(j=0;j<=nowPtr->number-1;j++)
                    {
                        tempData=file.get();
                        if(tempData!='\n' && tempData!=-1)nowPtr->data[j]=tempData;
                        else nowPtr->data[j]='\0';
                    }
                }
            }
        }

        //赋值
    file.close();

}

/*
************************************************************************
* 函数名称: searchSTR				  								       *
* 描   述: 在内存中搜索某一串字符串                                        *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void searchSTR(int row,int col)
{


    string searchString;

    int stringLength;
    int destinationLength;
    int firstPosition;
    int nextStart=0;

    STR *nowPtr=S->headPtr;
    int i,j=0,k;
    int isOK=0;
    bool isok;
    QString text = QInputDialog::getText(NULL, "Search",
                                                       "Please input your String",
                                                       QLineEdit::Normal,
                                                       "your comment",
                                                       &isok);
    searchString = text.toStdString();

    /*QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&BegainTime);*/

    while(row>0)
    {
        nowPtr=nowPtr->nextPtr;
        row--;
    }
    stringLength=searchString.size();

    while(nowPtr!=NULL)
    {
        if(nowPtr->number==1)
        {
            nowPtr=nowPtr->nextPtr;
            if(nowPtr!=NULL) S->signal_y+=distance_y;
            col=0;
        }
        else if(nowPtr->number==0)
        {
            break;
        }
        else
        {
            destinationLength=nowPtr->number;

            if(searchString==oldString && S->isBlock==1)
                nextStart=col+stringLength;
            else nextStart=col;

            next1=new int[destinationLength-1]();

            firstPosition=kmp(nowPtr->data,destinationLength-1,searchString,stringLength,nextStart);

            delete [] next1;

            if(firstPosition==-1)
            {
                nowPtr=nowPtr->nextPtr;
                if(nowPtr!=NULL) S->signal_y+=distance_y;
                col=0;
            }
            else
            {
                isOK=1;
                S->isBlock=1;
                S->signal_x=firstPosition*distance_x+pos_x_left-3;
                S->signal_y1=S->signal_y;
                S->signal_x1=(firstPosition+stringLength)*distance_x+pos_x_left-3;
                oldString = searchString;
                break;
            }
        }
    }
    if(isOK==1)
    {

    }
    else
    {
        QMessageBox::information(NULL, "Information",
                                            "None!",
                                            QMessageBox::Yes | QMessageBox::No,
                                            QMessageBox::Yes);
    }

    /*QueryPerformanceCounter(&EndTime);
            //cout<<(double)(EndTime.QuadPart - BegainTime.QuadPart)/Frequency.QuadPart<<endl;
              duration = (double)(EndTime.QuadPart - BegainTime.QuadPart)/Frequency.QuadPart;
            printResult(duration);*/
}

/*
************************************************************************
* 函数名称: Next          		  								       *
* 描   述: next数组的计算                                                *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void Next(char str[],int len)
{
    next1[0] = -1;
    for(int j = 1 ; j < len ; j++)
    {
        int i = next1[j-1];
        while(str[j] != str[i+1] && i >= 0)//迭代的过程
        {
            i = next1[i];
        }
        if(str[j] == str[i+1])
        {
            next1[j] = i+1;
        }
        else
        {
            next1[j] = -1;
        }
    }
}

/*
************************************************************************
* 函数名称: kmp			  		        						       *
* 描   述: 字符串的模式匹配算法                                            *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
int kmp(char des[], int len1, string pat, int len2, int nextStart)
{
    Next(des,len1);
    int p=0,s=nextStart;
    while(p < len2  && s < len1)
    {
        if(pat[p] == des[s])
        {
            p++;s++;
        }
        else
        {
            if(p==0)
            {
                s++;//若第一个字符就匹配失败，则从des的下一个字符开始
            }
            else
            {
                p = next1[p-1]+1;//用失败函数确定pat应回溯到的字符
            }
        }
    }
    if(p < len2)//整个过程匹配失败
    {
        return -1;
    }
    return s-len2;
}

/*
************************************************************************
* 函数名称: changeSTR			  					    			       *
* 描   述: 在内存中搜索某一串字符串，并替换成其他字符串                       *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void changeSTR(int row,int col)
{
    storeCopy();
    string searchString;
    string changeString;
    int stringLength;
    int changeLength;
    int isChange=0;
    int destinationLength;
    int firstPosition;
    int nextStart=0;

    STR *nowPtr=S->headPtr;
    int i,j=0,k,m,n;
    int isOK=0;
    int temp_row,temp_col;
    int X1,Y1;
    bool isok;
    QString text = QInputDialog::getText(NULL, "Search",
                                                       "Please input your String",
                                                       QLineEdit::Normal,
                                                       "your comment",
                                                       &isok);

    searchString = text.toStdString();
    QString text1 = QInputDialog::getText(NULL, "Change",
                                                       "Please input your String",
                                                       QLineEdit::Normal,
                                                       "your comment",
                                                       &isok);
    changeString = text1.toStdString();


    while(row>0)
    {
        nowPtr=nowPtr->nextPtr;
        row--;
    }
    stringLength=searchString.size();
    changeLength=changeString.size();

    while(nowPtr!=NULL)
    {
        if(nowPtr->number==1)
        {
            nowPtr=nowPtr->nextPtr;
            if(nowPtr!=NULL) S->signal_y+=distance_y;
            col=0;
        }
        else if(nowPtr->number==0)
        {
            break;
        }
        else
        {
            destinationLength=nowPtr->number;

            if(searchString==oldString && S->isBlock==1)
                nextStart=col+stringLength;
            else nextStart=col;

            next1=new int[destinationLength-1]();

            firstPosition=kmp(nowPtr->data,destinationLength-1,searchString,stringLength,nextStart);

            delete [] next1;

            if(firstPosition==-1)
            {
                nowPtr=nowPtr->nextPtr;
                if(nowPtr!=NULL) S->signal_y+=distance_y;
                col=0;
            }
            else
            {
                isOK=1;
                //S->isBlock=1;
                S->signal_x=firstPosition*distance_x+pos_x_left-3;
                oldString = searchString;
                break;
            }
        }
    }

    if(isOK==1)
    {
        isChange=1;
        if(isChange==1)
        {
            temp_row=S->signal_y;
            temp_col=firstPosition;
            if(changeLength<=stringLength)
            {
                for(m=0;m<changeLength;m++,temp_col++)
                {
                    nowPtr->data[temp_col]=changeString[m];
                }
                for(m=temp_col;m<= nowPtr->number-(stringLength-changeLength);m++)
                {
                    nowPtr->data[m]=nowPtr->data[m+stringLength-changeLength];
                }
                nowPtr->number-=(stringLength-changeLength);
            }
            else if(changeLength>stringLength)
            {
                if(nowPtr->number%80==0)//要申请内存
                {
                    nowPtr->data=(char*)realloc(nowPtr->data,(nowPtr->number+80)*sizeof(char));
                }
                for(m=nowPtr->number+(changeLength-stringLength);m>=temp_col+stringLength;m--)
                {
                    nowPtr->data[m+(changeLength-stringLength)]=nowPtr->data[m];
                }
                for(m=0;m<changeLength;m++,temp_col++)
                {
                    nowPtr->data[temp_col]=changeString[m];
                }
                nowPtr->number+=(-stringLength+changeLength);
            }

        }

        isOK=0;
    }
    else
    {
        QMessageBox::information(NULL, "Information",
                                            "None!",
                                            QMessageBox::Yes | QMessageBox::No,
                                            QMessageBox::Yes);

    }

}

/*
************************************************************************
* 函数名称: blockDelete		  					    			       *
* 描   述: 把一块内存删除掉                                               *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：                                                             *
************************************************************************
*/
void blockDelete(int start_row,int start_col,int end_row,int end_col)
{
    storeCopy();
    STR *startPtr=S->headPtr,*endPtr=S->headPtr,*tempPtr=NULL;
    int i,j;
    if(start_row>end_row)
       cout<<"ERROR"<<endl;
    else if(start_row==end_row)
    {
        while(start_row>0)
        {
            startPtr=startPtr->nextPtr;
            start_row--;
        }

        for(i=start_col;i<=startPtr->number;i++)
        {
            startPtr->data[i]=startPtr->data[i+(end_col-start_col)+1];
        }
        startPtr->number-=end_col-start_col+1;

    }
    else
    {
        while(start_row>0)
        {
            startPtr=startPtr->nextPtr;
            start_row--;
        }

        while(end_row>0)
        {
            endPtr=endPtr->nextPtr;
            end_row--;
        }

        tempPtr=startPtr->nextPtr;
        while(tempPtr!=endPtr)
        {
            startPtr->nextPtr=tempPtr->nextPtr;
            free(tempPtr);
            tempPtr=startPtr->nextPtr;
        }

        int restStartNumber=0,restEndNumber;
        restEndNumber=endPtr->number-end_col-1;
        restStartNumber=start_col;
        startPtr->number=restEndNumber+restStartNumber;
        startPtr->data=(char*)realloc(startPtr->data,(startPtr->number/80+1)*80*sizeof(char));
        for(i=start_col,j=end_col+1;i<=startPtr->number;i++,j++)
        {
            startPtr->data[i]=endPtr->data[j];
        }
        startPtr->nextPtr=endPtr->nextPtr;
        free(endPtr);
    }
}

/*
************************************************************************
* 函数名称: selectAll			  					    			       *
* 描   述: 全选内存的内容                                                 *
* 版   本：beta 1.7                                                     *
* 新版本更新内容：                                                       *
* 备   注：尚存在bug                                                     *
************************************************************************
*/
void selectAll()
{
    STR *nowPtr=S->headPtr;

    S->signal_x=pos_x_left-3;
    S->signal_y=pos_y_above;
    S->signal_y1=S->signal_y;
    while(nowPtr!=NULL && nowPtr->number!=0)
    {
         S->signal_y1+=distance_y;
         if(nowPtr->nextPtr==NULL)
            S->signal_x1=(nowPtr->number)*distance_x+pos_x_left-3;
         else S->signal_x1=(nowPtr->number-1)*distance_x+pos_x_left-3;
         nowPtr=nowPtr->nextPtr;
    }
    S->signal_y1-=distance_y;
    S->isBlock=1;
}

/*
************************************************************************
* 函数名称: goBack		  					    			           *
* 描   述: 一步撤销                                                      *
* 版   本：beta 2.1                                                     *
* 新版本更新内容：                                                        *
* 备   注：                                                             *
************************************************************************
*/
void goBack()
{

    New();
    char *fileTemp;
    fileTemp="storeGoBack.txt";

    S->headPtr=(STR*)malloc(sizeof(STR));
    currentPtr=S->headPtr;
    lastPtr=S->headPtr;
    S->headPtr->data=NULL;
    S->headPtr->number=0;
    S->headPtr->nextPtr=NULL;
    fflush(stdin);
    infile.open(fileTemp,ios::in);


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
* 函数名称: storeCopy		  					    			           *
* 描   述: 存储编辑操作之前的副本内容                                       *
* 版   本：beta 2.1                                                     *
* 新版本更新内容：                                                        *
* 备   注：                                                             *
************************************************************************
*/
void storeCopy()
{
    ofstream file("storeGoBack.txt",ios_base::trunc);

    STR *startPtr=S->headPtr,*endPtr=S->headPtr,*tempPtr=NULL;
    int i;


    while(startPtr!=NULL)
    {
        for(i=0;i<startPtr->number;i++)
        {
            file<<startPtr->data[i];
        }
        startPtr=startPtr->nextPtr;
    }


    file.close();
}


/*
************************************************************************
* 函数名称: ifBetweenChineseMid  					    			       *
* 描   述: 对光标在中文中间进行处理                                        *
* 版   本：beta 2.1                                                     *
* 新版本更新内容：2.1 解决向下按钮到最后一行崩溃bug                          *
* 备   注：                                                             *
************************************************************************
*/
int ifBetweenChineseMid1(int row,int col)
{
    int mm=0;
    if(col!=0)
    {
        mm=1;
        cout<<row<<" "<<col<<endl;
    }
    STR *nowPtr=S->headPtr;
    int temp_col=0;
    int isChineseBreak=0;

    while(row>0)
    {
        if(nowPtr!=NULL && nowPtr->nextPtr!=NULL)  nowPtr=nowPtr->nextPtr;
        else
        {
            //cout<<"between error"<<endl;
            break;
        }
        row--;
    }

    if(nowPtr!=NULL&&col>0 && nowPtr->data[col-1]<0)
    {
        while(temp_col<col)
        {
            if(nowPtr->data[temp_col]<0)
            {
                temp_col+=2;
            }
            else
            {
                temp_col++;
            }
        }
        if(mm==1) cout<<temp_col<<endl;
        if(temp_col==col)
        {
            isChineseBreak=0;
        }
        else
        {

            isChineseBreak=1;
        }

        if(isChineseBreak==1)
        {
           // cout<<"1"<<endl;
            return 1;

            isChineseBreak=0;
        }

    }
         //cout<<"0"<<endl;
         return 0;

}
void ifBetweenChineseMid(int row,int col,int mode)
{
    //cout<<row<<" "<<col<<endl;
    STR *nowPtr=S->headPtr;
    int temp_col=0;
    int isChineseBreak=0;

    while(row>0)
    {
        if(nowPtr!=NULL && nowPtr->nextPtr!=NULL)  nowPtr=nowPtr->nextPtr;
        else
        {
            cout<<"between error"<<endl;
            break;
        }
        row--;
    }

    if(nowPtr!=NULL&&col>0 && nowPtr->data[col-1]<0)
    {
        while(temp_col<col)
        {
            if(nowPtr->data[temp_col]<0)
            {
                temp_col+=2;
            }
            else
            {
                temp_col++;
            }
        }

        //cout<<temp_col<<" "<<col<<endl;
        if(temp_col==col)
        {
            isChineseBreak=0;
        }
        else
        {
            cout<<"i"<<endl;
            isChineseBreak=1;
        }

        if(isChineseBreak==1)
        {
            switch(mode)
            {

                case 1:
                    cout<<"right"<<endl;
                    S->signal_x+=distance_x;
                    break;
                case -1:
                    cout<<"left"<<endl;
                    S->signal_x-=distance_x;
                    break;
                case 0:
                    cout<<"right"<<endl;
                    S->signal_x+=distance_x;
                    break;
                case 2:
                    S->signal_x1+=distance_x;
                    break;
            }

            isChineseBreak=0;
        }
    }

}


void printResult(double duration)
{
    cout<<"time"<<setiosflags(ios::fixed)<<setprecision(10)<<duration<<"s"<<endl;
}

