#include"base.h"
#include<math.h>
extern struct Lift_State Lift;

extern int dest[26];
extern int in_ask[10];
extern int out_up_ask[9];
extern int out_down_ask[10]; 

extern char strategy;

void Control()//用于在顺便服务策略下确定电梯的目标  
{
    	int i;
    	
    	if( Lift.state == STOP )
    	{
            if( Lift.BeforeState == UP )//如果电梯停靠之前为上行  
            {
                for( i=8 ; i >= Lift.floor+1 ; i-- )//从八楼到所在的上一层检索上行请求  
                {
                     if( out_up_ask[i] == 1 && i <= dest[1] )//如果有优先目标，修改电梯目标  
                     {
                         dest[1]=i;
                     }
                }
            }
            else if( Lift.BeforeState == DOWN )//如果电梯下行  
            {
                 for( i=2 ; i <= Lift.floor-1 ; i++ )
                 {
                      if( out_down_ask[i] == 1 && i >= dest[1] )
                      {
                          dest[1]=i;
                      }
                 }
            }
            else//如果电梯之前为空闲  
            {
                for( i=8 ; i >= 1 ; i-- )//需要检索全部三个数组来为电梯找到一个目标  
                {
                     if( out_up_ask[i] == 1 )
                     {
                         dest[1]=i;
                     }
                }
                for( i=2 ; i <= 9 ; i++ )
                {
                     if( out_down_ask[i] == 1 )
                     {
                         dest[1]=i;
                     }
                }
                for( i=1 ; i <= 9 ; i++ )
                {
                     if( in_ask[i] == 1 )
                     {
                         dest[1]=i;
                     }
                }
            }
        }
        else if( Lift.state == UP )//电梯现在状态为上行  
        {
             for( i=8 ; i > Lift.floor+1 ; i-- )
             {
                  if( out_up_ask[i] == 1 && i <= dest[1] )
                  {
                      dest[1]=i;
                  }
             }
             for( i=9 ; i > Lift.floor+1 ; i-- )
             {
                  if( in_ask[i] == 1 && i <= dest[1] )
                  {
                      dest[1]=i;
                  }
             }
        }
        else if( Lift.state == DOWN )//电梯正在下行  
        {
            for( i=2 ; i < Lift.floor-1 ; i++ )
            {
                 if( out_down_ask[i] == 1 && i >= dest[1] )
                 {
                     dest[1]=i;
                 }
            }
            for( i=1 ; i < Lift.floor-1 ; i++ )
            {
                 if( in_ask[i] == 1 && i >= dest[1] )
                  {
                     dest[1]=i;
                  }
            }
        }
        else//电梯是空闲的  
        {
            for( i=8 ; i >= 1 ; i-- )//需要检索全部三个数组来为电梯找到一个目标  
            {
                 if( out_up_ask[i] == 1 )
                 {
                     dest[1]=i;
                 }
            }
            for( i=2 ; i <= 9 ; i++ )
            {
                 if( out_down_ask[i] == 1 )
                 {
                     dest[1]=i;
                 }
            }
            for( i=1 ; i <= 9 ; i++ )
            {
                 if( in_ask[i] == 1 )
                 {
                     dest[1]=i;
                 }
            }
        }
}
