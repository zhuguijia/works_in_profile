#include"base.h"
#include<time.h>
#include"Control.h"
#include<windows.h>
extern struct Lift_State Lift;

extern int dest[26];
extern int in_ask[10];
extern int out_up_ask[9];
extern int out_down_ask[10]; 

extern char strategy;

extern HANDLE Mutex;

extern int GO;

void State()
{
     int i;
     while(1)
     {
             switch( Lift.state )
             {
                     case FREE:
                          {             
                               WaitForSingleObject(Mutex,INFINITE);         
                               Control();//更新电梯目标  
                               ReleaseMutex(Mutex);
                                                  
                               if( dest[1] != 0 )
                               {
                                   Lift.BeforeState=Lift.state;
                                   
                                   if( dest[1] > Lift.floor )
                                   {
                                       Lift.state=UP;
                                   }
                                   else if( dest[1] < Lift.floor )
                                   {
                                       Lift.state=DOWN;
                                   }
                                   else
                                   {
                                       Lift.state=STOP;
                                   }
                               }
                               break;
                          }
        
                          
                     case STOP:
                          {
                               WaitForSingleObject(Mutex,INFINITE);
                               
                               for( i=0 ; dest[i+1] != 0 ; i++ )//删除已经响应的请求    
                               {
                                    dest[i]=dest[i+1];
                               }
                               dest[i]=0;     
                               in_ask[Lift.floor]=0;
                               if( (Lift.BeforeState == UP && Lift.floor>1 && Lift.floor<9) 
                                   || Lift.floor==1 )
                               {
                                   out_up_ask[Lift.floor]=0;
                               } 
                               if( (Lift.BeforeState == DOWN && Lift.floor>1 && Lift.floor<9) 
                                   || Lift.floor==9 )
                               {
                                   out_down_ask[Lift.floor]=0;
                               }                                                    
                               
                               ReleaseMutex(Mutex);
                               
                               Sleep(1000);//开门关门 
                               
                               Lift.door=OPEN;
                               
                               for( Lift.OpenTime=4 ; Lift.OpenTime > 0 ; Lift.OpenTime-- )
                               {
                                    if( GO == 1 )
                                    {
                                        Lift.OpenTime=0;
                                    }
                                    
                                    Sleep(1000);
                               }
                               
                               Lift.door=CLOSE;
                               
                               GO=0;
                               
                               if( strategy == 'X' )//更新电梯目标  
                               {
                                   WaitForSingleObject(Mutex,INFINITE);         
                                   Control();//更新电梯目标  
                                   ReleaseMutex(Mutex);
                               }
                               
                               if( dest[1] == 0 )
                               {
                                   Lift.BeforeState=Lift.state;
                                   
                                   Lift.state=FREE;
                               }
                               else
                               {
                                   Lift.BeforeState=Lift.state;
                                   
                                   if( dest[1] > Lift.floor )
                                   {
                                       Lift.state=UP;
                                   }
                                   else
                                   {
                                       Lift.state=DOWN;
                                   }
                               }
                               break;
                          }
        
                          
                     case UP:
                          {
                                if( Lift.floor != dest[1] )
                                {
                                    for( ; Lift.floor < dest[1] ; Lift.floor++ )
                                    {
                                         if( strategy == 'X' )//更新电梯目标  
                                         {
                                             WaitForSingleObject(Mutex,INFINITE);         
                                             Control();//更新电梯目标  
                                             ReleaseMutex(Mutex);
                                         }
                                         
                                         Sleep(5000);                                                                                    
                                    }
                                }
                                else
                                {
                                    Lift.BeforeState=Lift.state;
                                   
                                    Lift.state=STOP; 
                                }
                                break;
                          }
        
                          
                     case DOWN:
                          {
                                if( Lift.floor != dest[1] )
                                {
                                    for( ; Lift.floor > dest[1] ; Lift.floor-- )
                                    {
                                         if( strategy == 'X' )//更新电梯目标  
                                         {
                                             WaitForSingleObject(Mutex,INFINITE);         
                                             Control();//更新电梯目标  
                                             ReleaseMutex(Mutex);
                                         }
                                         
                                         Sleep(5000);  
                                    }
                                }
                                else
                                {
                                    Lift.BeforeState=Lift.state;
                                   
                                    Lift.state=STOP; 
                                }
                                break;
                          }
             }
     }
}
