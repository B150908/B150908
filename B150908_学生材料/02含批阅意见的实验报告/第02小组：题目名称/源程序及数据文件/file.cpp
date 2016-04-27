/*li12_1.c*/
#include<stdio.h>
#include<stdlib.h>
#include"file.h"
#include"car.h"

void printHead( )      /*打印车辆信息的表头*/
{
printf("%5s %2s %8s %6s %6s %6s %6s %6s %6s %2s \n","车牌号","车主","车型号","车颜色","违规记录","缴费状态","违规时间","扣分情况","罚款","排名");
}

void menu( )         /*顶层菜单函数*/
{
		printf("******** 1. 显示基本信息 ********\n");
		printf("******** 2. 基本信息管理 ********\n");
		printf("******** 3. 车辆信息管理 ********\n");
        printf("******** 4. 根据条件查询 ********\n");
		printf("******** 0. 退出         ********\n");
}

void menuBase( )     /*2、基本信息管理菜单函数*/
{
		printf("%%%%%%%% 1. 插入车辆信息 %%%%%%%%\n");
		printf("%%%%%%%% 2. 删除车辆信息 %%%%%%%%\n");
		printf("%%%%%%%% 3. 修改车辆记录 %%%%%%%%\n");
		printf("%%%%%%%% 0. 返回上层菜单 %%%%%%%%\n");
}


void menuSearch()    /*5、根据条件查询菜单函数*/
{
		printf("######## 1. 按车牌号查询   ########\n");
		printf("######## 2. 按车主查询     ########\n");
		printf("######## 3. 按扣分查询     ########\n");
		printf("######## 4. 车的型号查询   ########\n");
		printf("######## 5. 车的颜色查询   ########\n");
		printf("######## 0. 返回上层菜单   ########\n");
}

int baseManage(car che[],int n)    	     /*该函数完成基本信息管理*/
/*按车牌号进行插入删除修改，车牌号不能重复*/
{  
		int choice,t,find[NUM];
        car s;
do
	    {   
menuBase( );                  /*显示对应的二级菜单*/
printf("choose one operation you want to do:\n");
		     scanf("%d",&choice);	          /*读入选项*/
		     switch(choice)
		     {
			   case 1:	 readche(&s,1);       /*读入一条待插入的违规记录*/
					 n=insertche(che,n,s);   /*调用函数插入违规记录*/
					 break;
			   case 2:  printf("Input the number deleted\n");
					 scanf("%s",&s.number);  /*读入一个待删除的车牌号*/
					 n=deleteche(che,n,s);   /*调用函数删除指定车辆的违规记录*/
					 break;
			   case 3:  printf("Input the number modified\n");
					 scanf("%s",&s.number);  /*读入一个待修改的车牌号*/
				      t=searchche(che,n,s,1,find) ; /*调用函数查找指定车牌号的违规记录*/
				      if (t)                 /*如果该车牌号的记录存在*/
					 {
						  readche(&s,1);   /*读入一条完整的车辆违规记录信息*/
					      che[find[0]]=s;    /*将刚读入的记录赋值给需要修改的数组记录*/ 					 
					  }					 
					 else                 /*如果该车辆的记录不存在*/ 
 printf("this cheliang is not in,can not be modified.\n"); /*输出提示信息*/
					 break;
			    case 0: break;
		    }
	}while(choice);
return n;                             /*返回当前操作结束后的实际记录条数*/
}

void scoreManage(car che[],int n)          /*该函数完成车辆的扣分管理功能*/
{  
	int choice;
	do
	{
		printf("choose one operation you want to do:\n");
		scanf("%d",&choice);	                 /*读入二级选项*/
		switch(choice)
		{
			case 1:   calcuRank(che,n);         /*根据所有车辆扣分排名次*/
				      break;		
			case 0:   break;
		}
	}while(choice);
}

void searchManage(car che[],int n)               /*该函数完成根据条件查询功能*/
{
    int i,choice,findnum,f[NUM];
    car s;
	   do
{
			menuSearch( );                         /*显示对应的二级菜单*/
			printf("choose one operation you want to do:\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:   printf("Input a cheliang\'s num will be searched:\n");
				      scanf("%ld",&s.number);         /*输入待查询车辆的车牌号*/
					  break;
				case 2:   printf("Input a cheliang\'s name will be searched:\n");
				      scanf("%s",s.name);	          /*输入待查询车辆的车主名*/		  
				      break;   
				case 3:   printf("Input a rank will be searched:\n");
				      scanf("%d",&s.rank);          /*输入待查询车辆违规扣分的名次*/
					  break;
				case 0:   break;
			}
		 	if (choice>=1&&choice<=3)
			{ 
				findnum=searchche(che,n,s,choice,f);    /*查找的符合条件元素的下标存于f数组中*/
				if (findnum)				     /*如果查找成功*/
				{
			   		 printHead( );                  /*打印表头*/
					 for (i=0;i<findnum;i++)         /*循环控制f数组的下标*/
	      	 printche(&che[f[i]],1);      /*每次输出一条记录*/
				}
		    		else
			    	    printf("this record does not exist!\n"); /*如果查找不到元素，则输出提示信息*/
		     }		
	    }while (choice);
}

int runMain(car che[],int n,int choice)    /*主控模块，对应于一级菜单其下各功能选择执行*/
{
		switch(choice)
		{
			case 1: printHead( );           /* 1. 显示基本信息*/
				 sortche(che,n,1);         /*按扣分由小到大的顺序排序记录*/ 
          	 printche(che,n);          /*按扣分由小到大的顺序输出所有记录*/
					break;
			case 2: n=baseManage(che,n);    /* 2. 基本信息管理*/
			   	     break;
			case 3: scoreManage(che,n);     /* 3. 车辆扣分管理*/
					break;
			case 4: searchManage(che,n);     /* 4. 根据条件查询*/
				     break;
          case 0: break;
		}
		return n;
}

int main( )
{
		car che[NUM];                /*定义实参一维数组存储车辆违规记录*/
      int choice,n;
	 n=readFile(che);                  /*首先读取文件，记录条数返回赋值给n*/
	 if (!n)                          /*如果原来的文件为空*/
	     {
		    n=createFile(che);              /*则首先要建立文件，从键盘上读入一系列记录存于文件*/
}	 	 
	do
	     {
	         menu();                      /*显示主菜单*/
	         printf("Please input your choice: ");
	         scanf("%d",&choice);
	         if (choice>=0&&choice<=5)
	              n=runMain(che,n,choice);    /*通过调用此函数进行一级功能项的选择执行*/
	         else 
		          printf("error input,please input your choice again!\n");
	} while (choice);
	sortche(che,n,1);                   /*存入文件前按车辆扣分由小到大排序*/ 
	     saveFile(che,n);                   /*将结果存入文件*/
      return 0;
}
