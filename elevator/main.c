#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"base.h"
#include"main.h"
#include"egg.h"
struct Lift_State Lift={FREE,FREE,1,CLOSE,0};//�����ʼ��һ������   

int dest[26],in_ask[10],out_up_ask[9],out_down_ask[10];//dest[1]Ϊ���ݵ�Ŀ��¥��,ask�������ڼ�¼���� 

char strategy;

HANDLE Mutex;

int GO=0;

EVENT_TYPE ev;//��׽��갴���¼�  

HEGG keys,moving_lift;//keysΪ����ť���ڵ�egg��moving_liftΪ�������ڵ�egg  

int main(int argc, char *argv[])
{
  double x,y; 
    
  EggStart(650,650);  
  DrawBitmap("lift.bmp");//���ñ��� 
  
  MovePen(445,650-390);//�������в���  
  DrawString("����ѡ��������в���");
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
  
  keys=LayEgg();//egg��ʼ��  
  moving_lift=LayEgg();
  
  SetActiveEgg(moving_lift);//��ʼ������λ��  
  MovePen(0,650);
  DrawBitmap("1.bmp");
  MoveEgg(45,45);

  //��ʼ���������� 
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
