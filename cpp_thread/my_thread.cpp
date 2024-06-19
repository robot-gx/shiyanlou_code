
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include<queue>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <thread>
#include <bitset>
#include <math.h>
#include <sys/time.h>
#define FILE_LOCK_NAME  ".log/main.run"



/////////////////////////////////////////////////////////////
////函数名称:robot_main_thread_routine
////输入参数:main_thred_sw_p,启动开关
////输出参数:无
////返回值		:1,执行成功;
////函数说明:主线程
/////////////////////////////////////////////////////////////
int robot_main_thread_routine(int* main_thred_sw_p)
{
	unsigned 	int  			global_counter 			=	0;
	const 		int				meta_time_unit			=	100;//元时间单元50ms
	int							ms_100_by_counter		=	0;//100ms


	while(1)
	{
		this_thread::sleep_for(chrono::milliseconds(meta_time_unit));

		if(main_thred_sw_p==NULL || *main_thred_sw_p<0)
		{
			this_thread::yeild();
			continue;
		}

		if(global_counter == 0)
		{
			printf("robot_main_thread_routine start !\n");
		}

		if(global_counter<10) 
		{
			global_counter++;
		}
		else
		{
			global_counter								=	1;
			//循环执行的loop函数
		}



	}
	return 1;
}

int robot_net_communicate_thread_routine(int *net_thread_sw_p)
{
	unsigned 	int  			global_counter 			=	0;
	const 		int				meta_time_unit			=	100;//元时间单元50ms


	while(1)
	{
		//网络初始化,成功退出循环
		break;
	}
	while(1)
	{
		this_thread::sleep_for(chrono::milliseconds(meta_time_unit));

		if(*net_thread_sw_p<=0 || net_thread_sw_p==NULL)
		{
			this_thread::yeild();
			continue;
		}


		//do something

	}

}

int robot_com_thread_routine(int *com_thread_sw_p)
{
	unsigned 	int  			global_counter 			=	0;
	const 		int				meta_time_unit			=	10;//元时间单元50ms


	while(1)
	{
		//串口初始化,成功退出循环
		break;
	}
	while(1)
	{
		this_thread::sleep_for(chrono::milliseconds(meta_time_unit));

		if(*com_thread_sw_p<=0 || com_thread_sw_p==NULL)
		{
			this_thread::yeild();
			continue;
		}


		//do something

	}
}

int robot_can_thread_routine(int *can_thread_sw_p)
{
	unsigned 	int  			global_counter 			=	0;
	const 		int				meta_time_unit			=	5;//元时间单元50ms


	while(1)
	{
		//串口初始化,成功退出循环
		break;
	}
	while(1)
	{
		this_thread::sleep_for(chrono::milliseconds(meta_time_unit));

		if(*can_thread_sw_p<=0 || can_thread_sw_p==NULL)
		{
			this_thread::yeild();
			continue;
		}


		//do something

	}
}




int check_process_running(const char *flock_name)
{
	int lock_fd;;
	const char *file  = flock_name;

	if ((lock_fd = open(file, O_RDWR | O_CREAT)) < 0)
	{
        return -2; 
    }
    if (flock(lock_fd, LOCK_EX|LOCK_NB) < 0)  
	{
        return -1; 
    }

    return 0;
}
void print_func_exe_cycle(void)
{
	static unsigned long long pre_t=0;
	unsigned long long cur_t,deta_t;
	unsigned long long int sec1 = 0,usec1 =0;
    struct timeval tv;
    unsigned long long int val1;

    gettimeofday(&tv, NULL);
    sec1 = tv.tv_sec;
    usec1 = tv.tv_usec;
    val1 = sec1*1000000;
    val1 = val1 + usec1;
	cur_t = val1;
	deta_t = cur_t- pre_t;
	printf("cur_t=%llu,pre_t=%llu,deta_t=%llu \n",cur_t,pre_t,deta_t);
	pre_t = cur_t;		
}
int robot_init_public_resource(void)
{
	//配置文件读取，失败返回-1
	//全局变量初始化
	return 1;
}
int main(int arg,void *argv)
{

	int 	main_thread_sw=0; //主线程开关.......
	int 	net_thread_sw=1;
	int 	com_thread_sw=1;
	int 	can_thread_sw=1;
	printf("test thread main version 20240619 \n");
	if(check_process_running(FILE_LOCK_NAME)<0)
	{
        printf("check robot main process exclusive fail\n");
        printf("check robot main process exclusive fail\n");
        printf("check robot main process exclusive fail\n");		
		exit(EXIT_FAILURE);
	}

	//线程变量定义
	thread	robot_main_thread(robot_main_thread_routine,&main_thread_sw);
	thread  robot_netptp_thread(robot_net_communicate_thread_routine,&net_thread_sw);
	thread  robot_com_thread(robot_com_thread_routine,&com_thread_sw);
	thread  robot_can_thread(robot_can_thread_routine,&can_thread_sw);



	//
	if(robot_init_public_resource()>0);
	{
		main_thread_sw=1;
	}

	robot_main_thread.join();
	robot_netptp_thread.join();
	robot_com_thread.join();
	robot_can_thread.join();
	return 1;
}