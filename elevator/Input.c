#include<stdio.h>
#include"base.h"
#include<windows.h>
#include"egg.h"
void FCFR();//First Come First Respond
void BTWR();//By The Way Respond

extern struct Lift_State Lift;

extern int dest[26];
extern int in_ask[10];
extern int out_up_ask[9];
extern int out_down_ask[10]; 

extern char strategy;

extern HANDLE Mutex;

extern int GO;//输入空格键表示GO，即关门键  

int i;

extern EVENT_TYPE ev;

extern HEGG keys,moving_lift;

void GetInput()//从egg窗口读入请求并将相应的按钮变红  
{          
     while( (ev = WaitForEvent()) != EXIT )
     {
             switch(strategy)
             {
                             case 'Z': FCFR(); break;
                     
                             case 'X': BTWR(); break;
             }
     }
}

void FCFR()//First Come First Respond
{
     double x,y;
     
     if( ev == KEYDOWN )
     {
         x=GetMouseX();
         y=GetMouseY();
                 
         WaitForSingleObject(Mutex,INFINITE);
         
         if( x>100.0 && x<120.0 )
         {
             if( y>(650.0-640.0) && y<(650.0-620.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=1;
                 SetActiveEgg(keys);
                 MovePen(100,650-619);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-576.0) && y<(650.0-556.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=2;
                 SetActiveEgg(keys);
                 MovePen(100,650-555);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-515.0) && y<(650.0-495.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=3;
                 SetActiveEgg(keys);
                 MovePen(99,650-495);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-452.0) && y<(650.0-432.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=4;
                 SetActiveEgg(keys);
                 MovePen(99,650-432);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-392.0) && y<(650.0-372.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=5;
                 SetActiveEgg(keys);
                 MovePen(98,650-372);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-331.0) && y<(650.0-311.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=6;
                 SetActiveEgg(keys);
                 MovePen(98,650-311);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-266.0) && y<(650.0-246.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=7;
                 SetActiveEgg(keys);
                 MovePen(98,650-246);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-205.0) && y<(650.0-185.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=8;
                 SetActiveEgg(keys);
                 MovePen(98,650-185);
                 DrawBitmap("6.bmp");
             }
         }
         if( x>118.0 && x<138.0 )
         {
             if( y>(650.0-576.0) && y<(650.0-556.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=2;
                 SetActiveEgg(keys);
                 MovePen(120,650-555);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-515.0) && y<(650.0-495.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=3;
                 SetActiveEgg(keys);
                 MovePen(119,650-495);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-452.0) && y<(650.0-432.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=4;
                 SetActiveEgg(keys);
                 MovePen(119,650-432);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-392.0) && y<(650.0-372.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=5;
                 SetActiveEgg(keys);
                 MovePen(118,650-372);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-331.0) && y<(650.0-311.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=6;
                 SetActiveEgg(keys);
                 MovePen(118,650-311);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-266.0) && y<(650.0-246.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=7;
                 SetActiveEgg(keys);
                 MovePen(118,650-246);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-205.0) && y<(650.0-185.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=8;
                 SetActiveEgg(keys);
                 MovePen(118,650-185);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-142.0) && y<(650.0-122.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=9;
                 SetActiveEgg(keys);
                 MovePen(118,650-122);
                 DrawBitmap("4.bmp");
             }
         }
         if( x>200.0 && x<220.0 )
         {
             if( y>(650.0-520.0) && y<(650.0-500.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=1;
                 SetActiveEgg(keys);
                 MovePen(199,650-499);
                 DrawBitmap("25.bmp");
             }
             if( y>(650.0-470.0) && y<(650.0-450.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=2;
                 SetActiveEgg(keys);
                 MovePen(199,650-450);
                 DrawBitmap("26.bmp");
             }
             if( y>(650.0-420.0) && y<(650.0-400.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=3;
                 SetActiveEgg(keys);
                 MovePen(199,650-399);
                 DrawBitmap("7.bmp");
             }
             if( y>(650.0-370.0) && y<(650.0-350.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=4;
                 SetActiveEgg(keys);
                 MovePen(199,650-350);
                 DrawBitmap("8.bmp");
             }
             if( y>(650.0-326.0) && y<(650.0-306.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=5;
                 SetActiveEgg(keys);
                 MovePen(199,650-306);
                 DrawBitmap("9.bmp");
             }
         }
         if( x>238.0 && x<258.0 )
         {
             if( Lift.state == STOP )
             {
                 if( y>(650.0-520.0) && y<(650.0-500.0) )
                 {
                     GO=1;
                     SetActiveEgg(keys);
                     MovePen(238,650-499);
                     DrawBitmap("14.bmp");
                 }
             }
             if( y>(650.0-470.0) && y<(650.0-450.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=6;
                 SetActiveEgg(keys);
                 MovePen(238,650-450);
                 DrawBitmap("10.bmp");
             }
             if( y>(650.0-420.0) && y<(650.0-400.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=7;
                 SetActiveEgg(keys);
                 MovePen(238,650-399);
                 DrawBitmap("11.bmp");
             }
             if( y>(650.0-370.0) && y<(650.0-350.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=8;
                 SetActiveEgg(keys);
                 MovePen(238,650-350);
                 DrawBitmap("12.bmp");
             }
             if( y>(650.0-326.0) && y<(650.0-306.0) )
             {
                 for( i=1 ; dest[i]!=0 ; i++ )
                 {                      
                 }
                 dest[i]=9;
                 SetActiveEgg(keys);
                 MovePen(238,650-306);
                 DrawBitmap("13.bmp");
             }
         }
     }
     ReleaseMutex(Mutex);
}

void BTWR()
{
     double x,y;
     
     if( ev == KEYDOWN )
     {
         x=GetMouseX();
         y=GetMouseY();
         
         WaitForSingleObject(Mutex,INFINITE);
                 
         if( x>100.0 && x<120.0 )
         {
             if( y>(650.0-640.0) && y<(650.0-620.0) )
             {
                 out_up_ask[1]=1;
                 SetActiveEgg(keys);
                 MovePen(100,650-619);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-576.0) && y<(650.0-556.0) )
             {
                 out_up_ask[2]=1;
                 SetActiveEgg(keys);
                 MovePen(100,650-555);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-515.0) && y<(650.0-495.0) )
             {
                 out_up_ask[3]=1;
                 SetActiveEgg(keys);
                 MovePen(99,650-495);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-452.0) && y<(650.0-432.0) )
             {
                 out_up_ask[4]=1;
                 SetActiveEgg(keys);
                 MovePen(99,650-432);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-392.0) && y<(650.0-372.0) )
             {
                 out_up_ask[5]=1;
                 SetActiveEgg(keys);
                 MovePen(98,650-372);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-331.0) && y<(650.0-311.0) )
             {
                 out_up_ask[6]=1;
                 SetActiveEgg(keys);
                 MovePen(98,650-311);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-266.0) && y<(650.0-246.0) )
             {
                 out_up_ask[7]=1;
                 SetActiveEgg(keys);
                 MovePen(98,650-246);
                 DrawBitmap("6.bmp");
             }
             if( y>(650.0-205.0) && y<(650.0-185.0) )
             {
                 out_up_ask[8]=1;
                 SetActiveEgg(keys);
                 MovePen(98,650-185);
                 DrawBitmap("6.bmp");
             }
         }
         if( x>118.0 && x<138.0 )
         {
             if( y>(650.0-576.0) && y<(650.0-556.0) )
             {
                 out_down_ask[2]=1;
                 SetActiveEgg(keys);
                 MovePen(120,650-555);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-515.0) && y<(650.0-495.0) )
             {
                 out_down_ask[3]=1;
                 SetActiveEgg(keys);
                 MovePen(119,650-495);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-452.0) && y<(650.0-432.0) )
             {
                 out_down_ask[4]=1;
                 SetActiveEgg(keys);
                 MovePen(119,650-432);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-392.0) && y<(650.0-372.0) )
             {
                 out_down_ask[5]=1;
                 SetActiveEgg(keys);
                 MovePen(118,650-372);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-331.0) && y<(650.0-311.0) )
             {
                 out_down_ask[6]=1;
                 MovePen(118,650-311);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-266.0) && y<(650.0-246.0) )
             {
                 out_down_ask[7]=1;
                 SetActiveEgg(keys);
                 MovePen(118,650-246);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-205.0) && y<(650.0-185.0) )
             {
                 out_down_ask[8]=1;
                 SetActiveEgg(keys);
                 MovePen(118,650-185);
                 DrawBitmap("4.bmp");
             }
             if( y>(650.0-142.0) && y<(650.0-122.0) )
             {
                 out_down_ask[9]=1;
                 SetActiveEgg(keys);
                 MovePen(118,650-122);
                 DrawBitmap("4.bmp");
             }
         }
         if( x>200.0 && x<220.0 )
         {
             if( y>(650.0-520.0) && y<(650.0-500.0) )
             {
                 in_ask[1]=1;
                 SetActiveEgg(keys);
                 MovePen(119,650-499);
                 DrawBitmap("25.bmp");
             }
             if( y>(650.0-470.0) && y<(650.0-450.0) )
             {
                 in_ask[2]=1;
                 SetActiveEgg(keys);
                 MovePen(119,650-450);
                 DrawBitmap("26.bmp");
             }
             if( y>(650.0-420.0) && y<(650.0-400.0) )
             {
                 in_ask[3]=1;
                 SetActiveEgg(keys);
                 MovePen(119,650-399);
                 DrawBitmap("7.bmp");
             }
             if( y>(650.0-370.0) && y<(650.0-350.0) )
             {
                 in_ask[4]=1;
                 SetActiveEgg(keys);
                 MovePen(119,650-350);
                 DrawBitmap("8.bmp");
             }
             if( y>(650.0-326.0) && y<(650.0-306.0) )
             {
                 in_ask[5]=1;
                 SetActiveEgg(keys);
                 MovePen(119,650-306);
                 DrawBitmap("9.bmp");
             }
         }
         if( x>238.0 && x<258.0 )
         {
             if( Lift.state == STOP )
             {
                 if( y>(650.0-520.0) && y<(650.0-500.0) )
                 {
                     GO=1;
                     SetActiveEgg(keys);
                     MovePen(238,650-499);
                     DrawBitmap("14.bmp");
                 }
             }
             if( y>(650.0-470.0) && y<(650.0-450.0) )
             {
                 in_ask[6]=1;
                 SetActiveEgg(keys);
                 MovePen(238,650-450);
                 DrawBitmap("10.bmp");
             }
             if( y>(650.0-420.0) && y<(650.0-400.0) )
             {
                 in_ask[7]=1;
                 SetActiveEgg(keys);
                 MovePen(238,650-399);
                 DrawBitmap("11.bmp");
             }
             if( y>(650.0-370.0) && y<(650.0-350.0) )
             {
                 in_ask[8]=1;
                 SetActiveEgg(keys);
                 MovePen(238,650-350);
                 DrawBitmap("12.bmp");
             }
             if( y>(650.0-326.0) && y<(650.0-306.0) )
             {
                 in_ask[9]=1;
                 SetActiveEgg(keys);
                 MovePen(238,650-306);
                 DrawBitmap("13.bmp");
             }
         }
     }
     ReleaseMutex(Mutex);
}
