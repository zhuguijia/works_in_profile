#include<stdio.h>
#include<time.h>
#include<windows.h>
#include"base.h"
#include"egg.h"
extern struct Lift_State Lift;

extern int dest[26];
extern int in_ask[10];
extern int out_up_ask[9];
extern int out_down_ask[10]; 

extern char strategy;

extern HANDLE Mutex;

extern HEGG keys,moving_lift;

extern int GO;

int i;

void print_message()
{    
     while(1)
     {       
             SetActiveEgg(keys);
                                                                                                                                                   
             MovePen(455,650-390);//输出电梯当前状态 
             switch(Lift.state)
             {
                    case FREE:                         
                         DrawString("电梯状态：空闲");
                         break;
                    case STOP:
                         DrawString("电梯状态：停靠");
                         break;
                    case UP:
                         DrawString("电梯状态：上行");
                         break;
                    case DOWN: 
                         DrawString("电梯状态：下行");
                         break;
             }              
             
             switch(Lift.door)//输出电梯停靠的信息  
             {
                    case OPEN:
                         MovePen(430,650-410);
                         DrawString("开门  ");
                         switch(Lift.OpenTime)
                         {
                                case 4:
                                     DrawString("距电梯关门还有4秒");
                                     break;   
                                case 3:
                                     DrawString("距电梯关门还有3秒");
                                     break;  
                                case 2:
                                     DrawString("距电梯关门还有2秒");
                                     break;  
                                case 1:
                                     DrawString("距电梯关门还有1秒");
                                     break;             
                         }
                         break;
                    case CLOSE:
                         MovePen(430,650-410);
                         DrawString("          关门                       ");
                         break; 
             }                                     
             
             if( Lift.state == STOP )//在响应完请求后将相应的按钮变黑  
             {
                 if( strategy == 'Z' )
                 {                                          
                      switch(Lift.floor)
                      {
                             case 1:
                                  MovePen(100,650-619);
                                  DrawBitmap("5.bmp");  
                                  MovePen(199,650-499);
                                  DrawBitmap("15.bmp");  
                                  break;
                             case 2:
                                  MovePen(100,650-555);
                                  DrawBitmap("5.bmp");    
                                  MovePen(120-1,650-555);
                                  DrawBitmap("3.bmp");
                                  MovePen(199,650-450);
                                  DrawBitmap("16.bmp"); 
                                  break;
                             case 3:
                                  MovePen(99,650-495);
                                  DrawBitmap("5.bmp");
                                  MovePen(119,650-495);
                                  DrawBitmap("3.bmp");   
                                  MovePen(199,650-399);
                                  DrawBitmap("17.bmp"); 
                                  break;
                             case 4:
                                  MovePen(99,650-432);
                                  DrawBitmap("5.bmp");                      
                                  MovePen(119,650-432);
                                  DrawBitmap("3.bmp"); 
                                  MovePen(199,650-350);
                                  DrawBitmap("18.bmp");
                                  break;
                             case 5:
                                  MovePen(98,650-372);
                                  DrawBitmap("5.bmp");  
                                  MovePen(118,650-372);
                                  DrawBitmap("3.bmp");   
                                  MovePen(199,650-306);
                                  DrawBitmap("19.bmp"); 
                                  break;
                             case 6:
                                  MovePen(98,650-311);
                                  DrawBitmap("5.bmp");
                                  MovePen(118,650-311);
                                  DrawBitmap("3.bmp");         
                                  MovePen(238,650-450);
                                  DrawBitmap("20.bmp");   
                                  break;
                             case 7:
                                  MovePen(98,650-246);
                                  DrawBitmap("5.bmp");  
                                  MovePen(118,650-246);
                                  DrawBitmap("3.bmp");
                                  MovePen(238,650-399);
                                  DrawBitmap("21.bmp");
                                  break;
                             case 8:
                                  MovePen(98,650-185);
                                  DrawBitmap("5.bmp");
                                  MovePen(118,650-185);
                                  DrawBitmap("3.bmp");
                                  MovePen(238,650-350);
                                  DrawBitmap("22.bmp");
                                  break;
                             case 9:
                                  MovePen(118,650-122);
                                  DrawBitmap("3.bmp");
                                  MovePen(238,650-306);
                                  DrawBitmap("23.bmp");
                                  break;                                          
                      }                     
                 }
                 if( strategy == 'X' )
                 {
                     SetActiveEgg(keys);
                     
                     if( Lift.BeforeState == UP )
                     {
                         switch(Lift.floor)
                          {
                                 case 1:
                                      MovePen(100,650-619);
                                      DrawBitmap("5.bmp");  
                                      MovePen(199,650-499);
                                      DrawBitmap("15.bmp");  
                                      break;
                                 case 2:
                                      MovePen(100,650-555);
                                      DrawBitmap("5.bmp");
                                      MovePen(199,650-450);
                                      DrawBitmap("16.bmp"); 
                                      break;
                                 case 3:
                                      MovePen(99,650-495);
                                      DrawBitmap("5.bmp");  
                                      MovePen(199,650-399);
                                      DrawBitmap("17.bmp"); 
                                      break;
                                 case 4:
                                      MovePen(99,650-432);
                                      DrawBitmap("5.bmp");
                                      MovePen(199,650-350);
                                      DrawBitmap("18.bmp");
                                      break;
                                 case 5:
                                      MovePen(98,650-372);
                                      DrawBitmap("5.bmp");  
                                      MovePen(199,650-306);
                                      DrawBitmap("19.bmp"); 
                                      break;
                                 case 6:
                                      MovePen(98,650-311);
                                      DrawBitmap("5.bmp");        
                                      MovePen(238,650-450);
                                      DrawBitmap("20.bmp");   
                                      break;
                                 case 7:
                                      MovePen(98,650-246);
                                      DrawBitmap("5.bmp");
                                      MovePen(238,650-399);
                                      DrawBitmap("21.bmp");
                                      break;
                                 case 8:
                                      MovePen(98,650-185);
                                      DrawBitmap("5.bmp");
                                      MovePen(238,650-350);
                                      DrawBitmap("22.bmp");
                                      break;
                                 case 9:
                                      MovePen(238,650-306);
                                      DrawBitmap("23.bmp");
                                      break;                                          
                          }
                     }
                     else if( Lift.BeforeState == DOWN )
                     {
                          switch(Lift.floor)
                          {
                                 case 1:  
                                      MovePen(199,650-499);
                                      DrawBitmap("15.bmp");  
                                      break;
                                 case 2:    
                                      MovePen(120-1,650-555);
                                      DrawBitmap("3.bmp");
                                      MovePen(199,650-450);
                                      DrawBitmap("16.bmp"); 
                                      break;
                                 case 3:
                                      MovePen(119,650-495);
                                      DrawBitmap("3.bmp");   
                                      MovePen(199,650-399);
                                      DrawBitmap("17.bmp"); 
                                      break;
                                 case 4:                    
                                      MovePen(119,650-432);
                                      DrawBitmap("3.bmp"); 
                                      MovePen(199,650-350);
                                      DrawBitmap("18.bmp");
                                      break;
                                 case 5:
                                      MovePen(118,650-372);
                                      DrawBitmap("3.bmp");   
                                      MovePen(199,650-306);
                                      DrawBitmap("19.bmp"); 
                                      break;
                                 case 6:
                                      MovePen(118,650-311);
                                      DrawBitmap("3.bmp");         
                                      MovePen(238,650-450);
                                      DrawBitmap("20.bmp");   
                                      break;
                                 case 7:
                                      MovePen(118,650-246);
                                      DrawBitmap("3.bmp");
                                      MovePen(238,650-399);
                                      DrawBitmap("21.bmp");
                                      break;
                                 case 8:
                                      MovePen(118,650-185);
                                      DrawBitmap("3.bmp");
                                      MovePen(238,650-350);
                                      DrawBitmap("22.bmp");
                                      break;
                                 case 9:
                                      MovePen(118,650-122);
                                      DrawBitmap("3.bmp");
                                      MovePen(238,650-306);
                                      DrawBitmap("23.bmp");
                                      break;                                          
                          }
                     }
                     else if( Lift.BeforeState == FREE )
                     {
                          switch(Lift.floor)
                          {
                                 case 1:
                                      MovePen(100,650-619);
                                      DrawBitmap("5.bmp");  
                                      MovePen(199,650-499);
                                      DrawBitmap("15.bmp");  
                                      break;
                                 case 2:
                                      MovePen(100,650-555);
                                      DrawBitmap("5.bmp");    
                                      MovePen(120-1,650-555);
                                      DrawBitmap("3.bmp");
                                      MovePen(199,650-450);
                                      DrawBitmap("16.bmp"); 
                                      break;
                                 case 3:
                                      MovePen(99,650-495);
                                      DrawBitmap("5.bmp");
                                      MovePen(119,650-495);
                                      DrawBitmap("3.bmp");   
                                      MovePen(199,650-399);
                                      DrawBitmap("17.bmp"); 
                                      break;
                                 case 4:
                                      MovePen(99,650-432);
                                      DrawBitmap("5.bmp");                      
                                      MovePen(119,650-432);
                                      DrawBitmap("3.bmp"); 
                                      MovePen(199,650-350);
                                      DrawBitmap("18.bmp");
                                      break;
                                 case 5:
                                      MovePen(98,650-372);
                                      DrawBitmap("5.bmp");  
                                      MovePen(118,650-372);
                                      DrawBitmap("3.bmp");   
                                      MovePen(199,650-306);
                                      DrawBitmap("19.bmp"); 
                                      break;
                                 case 6:
                                      MovePen(98,650-311);
                                      DrawBitmap("5.bmp");
                                      MovePen(118,650-311);
                                      DrawBitmap("3.bmp");         
                                      MovePen(238,650-450);
                                      DrawBitmap("20.bmp");   
                                      break;
                                 case 7:
                                      MovePen(98,650-246);
                                      DrawBitmap("5.bmp");  
                                      MovePen(118,650-246);
                                      DrawBitmap("3.bmp");
                                      MovePen(238,650-399);
                                      DrawBitmap("21.bmp");
                                      break;
                                 case 8:
                                      MovePen(98,650-185);
                                      DrawBitmap("5.bmp");
                                      MovePen(118,650-185);
                                      DrawBitmap("3.bmp");
                                      MovePen(238,650-350);
                                      DrawBitmap("22.bmp");
                                      break;
                                 case 9:
                                      MovePen(118,650-122);
                                      DrawBitmap("3.bmp");
                                      MovePen(238,650-306);
                                      DrawBitmap("23.bmp");
                                      break;                                          
                          }
                     }
                 }
             }  
             MovePen(238,650-499);
             if( GO == 1 )
             {                                  
                 DrawBitmap("14.bmp");                                     
                 
             }    
             else if( GO == 0 )
             {
                  DrawBitmap("24.bmp");  
             }                    
             
             SetActiveEgg(moving_lift);//根据所在的楼层移动电梯  
             switch(Lift.floor)
             {
                     case 1:
                          MoveEgg(45,45);
                          break;
                     case 2:
                          MoveEgg(45,650-550);
                          break;
                     case 3:
                          MoveEgg(45,650-485);
                          break;
                     case 4:
                          MoveEgg(45,650-425);
                          break;
                     case 5:
                          MoveEgg(45,650-360);
                          break;
                     case 6:
                          MoveEgg(45,650-300);
                          break;
                     case 7:
                          MoveEgg(45,650-240);
                          break;
                     case 8:
                          MoveEgg(45,650-175);
                          break;
                     case 9:
                          MoveEgg(45,650-115);
                          break;
             }
     }
  
     Sleep(1000);
}



