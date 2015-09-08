#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"base.h"
#include"main.h"
#include"egg.h"
struct Lift_State Lift={FREE,FREE,1,CLOSE,0};//定义初始化一部电梯   

int dest[26],in_ask[10],out_up_ask[9],out_down_ask[10];//dest[1]为电梯的目标楼层,ask数组用于记录请求 

char strategy;

HANDLE Mutex;

int GO=0;

EVENT_TYPE ev;//捕捉鼠标按下事件  

HEGG keys,moving_lift;//keys为请求按钮所在的egg，moving_lift为电梯所在的egg  

int main(int argc, char *argv[])
{
  double x,y; 
    
  EggStart(650,650);  
  DrawBitmap("lift.bmp");//设置背景 
  
  MovePen(445,650-390);//读入运行策略  
  DrawString("请先选择电梯运行策略");
  while( (ev = WaitForEvent()) != EXIT )
  {
          if( ev == KEYDOWN )
            {
                x=GetMouseX();
                y=GetMouseY();
    
                if( x >= 438.0 && x <= 610.0 && y <= (650.0-570.0) && y >= (650.0-600.0) )
                {
                    strategy='Z';
                    MovePen(438,(650-600));
                    DrawLine(610-438, 0);
                    break;
                }
                else if( x >= 438.0 && x <= 610.0 && y <= (650.0-613.0) && y >= (650.0-648.0) )
                {
                     strategy='X';
                     MovePen(438,(650-640));
                     DrawLine(610-438, 0);
                     break;
                }
            }
  }
  MovePen(445,650-390);
  DrawString("                                        ");
  
  keys=LayEgg();//egg初始化  
  moving_lift=LayEgg();
  
  SetActiveEgg(moving_lift);//初始化电梯位置  
  MovePen(0,650);
  DrawBitmap("1.bmp");
  MoveEgg(45,45);

  //初始化请求数组 
  int i;
  for(  i=0 ; i <= 9 ; i++ )
  {
        out_down_ask[i]=0;
        in_ask[i]=0;
  }
  for(  i=0 ; i <= 25 ; i++ )
  {
        dest[i]=0;
  }
  for(  i=0 ; i <= 8 ; i++ )
  {
        out_up_ask[i]=0;
  }
  
  Mutex=CreateMutex(NULL,FALSE,NULL);
  
  HANDLE ThRead1,ThRead2,ThRead3;
  
  ThRead1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GetInput,NULL,0,NULL);
    
  ThRead2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)State,NULL,0,NULL);
    
  ThRead3=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)print_message,NULL,0,NULL);
    
  while(1)
  {
  }

  system("PAUSE");	
  return 0;
}
