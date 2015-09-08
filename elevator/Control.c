#include"base.h"
#include<math.h>
extern struct Lift_State Lift;

extern int dest[26];
extern int in_ask[10];
extern int out_up_ask[9];
extern int out_down_ask[10]; 

extern char strategy;

void Control()//������˳����������ȷ�����ݵ�Ŀ��  
{
    	int i;
    	
    	if( Lift.state == STOP )
    	{
            if( Lift.BeforeState == UP )//�������ͣ��֮ǰΪ����  
            {
                for( i=8 ; i >= Lift.floor+1 ; i-- )//�Ӱ�¥�����ڵ���һ�������������  
                {
                     if( out_up_ask[i] == 1 && i <= dest[1] )//���������Ŀ�꣬�޸ĵ���Ŀ��  
                     {
                         dest[1]=i;
                     }
                }
            }
            else if( Lift.BeforeState == DOWN )//�����������  
            {
                 for( i=2 ; i <= Lift.floor-1 ; i++ )
                 {
                      if( out_down_ask[i] == 1 && i >= dest[1] )
                      {
                          dest[1]=i;
                      }
                 }
            }
            else//�������֮ǰΪ����  
            {
                for( i=8 ; i >= 1 ; i-- )//��Ҫ����ȫ������������Ϊ�����ҵ�һ��Ŀ��  
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
        else if( Lift.state == UP )//��������״̬Ϊ����  
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
        else if( Lift.state == DOWN )//������������  
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
        else//�����ǿ��е�  
        {
            for( i=8 ; i >= 1 ; i-- )//��Ҫ����ȫ������������Ϊ�����ҵ�һ��Ŀ��  
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
