/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h> 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 //预定义的常量 

typedef int status; //函数返回结果标志 
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100 //线性表存储结构分配的空间 
#define LISTINCREMENT  10 //线性表空间分配增量 
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem; //存放抽象数据元素的顺序表 
	int length; //线性表表长 
	int listsize; //线性表分配空间大小 
}SqList;
typedef struct{  //线性表的管理表定义
    struct { char name[30]; //线性表名称 
     		SqList L;	
    } elem[10]; //存放线性表的集合 
    int length; //线性表集合的长度 
    int listsize; //线性表集合分配的空间 
}LISTS;

void SecondaryTable(SqList &L,int op);//进入二级菜单
status InitInput(SqList &L); //线性表数据输入 
status InitList(SqList &L); //线性表初始化 
status DestroyList(SqList &L); //线性表销毁 
status ClearList(SqList &L); //线性表清空 
status ListEmpty(SqList L); //线性表判空 
status ListLength(SqList L); //求线性表长度 
status GetElem(SqList L,int i,ElemType &e); //获取线性表中某位置的元素 
int LocateElem(SqList L,ElemType e); //查找元素在线性表中的位置 
status PriorElem(SqList L,ElemType e,ElemType &pre); //获取线性表中某元素的前驱元素 
status NextElem(SqList L,ElemType e,ElemType &next); //获取线性表中某元素的后继元素
status ListInsert(SqList &L,int i,ElemType e); //线性表插入元素 
status ListDelete(SqList &L,int i,ElemType &e); //线性表删除元素 
status ListTraverse(SqList L);  //遍历输出线性表元素
status SaveList(SqList L,char FileName[]); //线性表存档
status LoadList(SqList &L,char FileName[]); //线性表读档 
status AddList(LISTS &Lists,char ListName[]); //增加空线性表 
status RemoveList(LISTS &Lists,char ListName[]); //移除线性表
int LocateList(LISTS Lists,char ListName[]); //查找线性表 
/*--------------------------------------------*/
int main(){
	SqList L; 
	LISTS Lists;
	int op=1;
	int i,j;
	ElemType e,pre,next;
	char Name[30]={'\0'},FileName[100]={'\0'};
	L.elem=NULL;
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	Lists.length=0;
	Lists.listsize=10;
	for(j=0;j<10;j++)
	{
		Lists.elem[j].L.elem=NULL;
		Lists.elem[j].L.length=0;
	}//初始化 
	while(op!=-3){
		system("cls");	printf("\n\n");
		printf("          Menu for Linear Table On Sequence Structure \n");
		printf("--------------------------------------------------------------\n");
		printf("          -1.MainTable/MultiList     -2.SingleList\n");
		printf("    	  -3.Exit\n");
		printf("--------------------------------------------------------------\n");
		printf("     请选择所在的菜单层级：\n");
		printf("     -1：主菜单实现多线性表管理，-2：临时单线性表基本操作。\n");
		scanf("%d",&op);
		if(op==-1)
		{
			while(op)
			{
				system("cls");	printf("\n\n");
				printf("            Menu for Linear Table On Sequence Structure \n");
				printf("---------------------------------------------------------------------\n");
				printf("          15.AddList        16.RemoveList       17.LocateList\n");
				printf("          18.SecondaryTable\n");
				printf("    	  0. Exit\n");
				printf("---------------------------------------------------------------------\n");
				for(i=0;i<5;i++)
				{
					if(Lists.elem[i].L.elem==NULL&&Lists.elem[i+5].L.elem==NULL)
						printf("\t线性表%d：未创建            \t线性表%d：未创建",i+1,i+6);
					else if(Lists.elem[i].L.elem==NULL&&Lists.elem[i+5].L.elem!=NULL)
						printf("\t线性表%d：未创建            \t线性表%d：%s",i+1,i+6,Lists.elem[i+5].name);
					else if(Lists.elem[i].L.elem!=NULL&&Lists.elem[i+5].L.elem==NULL)
						printf("\t线性表%d：%s                \t线性表%d：未创建",i+1,Lists.elem[i].name,i+6);
					else
						printf("\t线性表%d：%s                \t线性表%d：%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
					printf("\n");
				}
				printf("     请选择你的操作[0或15~18]:");
				scanf("%d",&op);
				switch(op){
					case 15:
						printf("请输入待添加的线性表名称：");
						scanf("%s",Name);
						j=AddList(Lists,Name);
						if(j==OK)
						{
							printf("线性表添加成功！\n");
							i=LocateList(Lists,Name);
							InitInput(Lists.elem[i-1].L);
						}
						else if(j==ERROR)
							printf("线性表添加失败，该线性表已存在！\n");
                        else if(j==OVERFLOW)
                            printf("线性表添加失败，线性表集合已满！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
					case 16:
						printf("请输入待删除的线性表名称：");
						scanf("%s",Name);
						j=RemoveList(Lists,Name);
						if(j==OK)
							printf("线性表删除成功！\n");
						else if(j==ERROR)
							printf("线性表删除失败，集合中无此线性表！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
					case 17:
						printf("请输入待查找的线性表名称：");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							printf("该线性表位于集合中第 %d 位！\n",j);
						else
							printf("线性表查找失败，集合中无此线性表！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
					case 18:
						printf("请输入待操作的线性表名称：");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].L,op);
						else
						{
							getchar();
							printf("线性表不存在于集合中，不能进入单线性表操作！\n");
							getchar();
							break;
						}
						break;
					case 0:
						break;	
				}//end of switch
			}//end of while
		}//end of if	
		if(op==-2)
		{
			while(op)
			{
				system("cls");	printf("\n\n");
				printf("              Menu for Linear Table On Sequence Structure \n");
				printf("-------------------------------------------------------------------------\n");
				printf("    	  1. InitList       7. LocateElem            13.SaveList\n");
				printf("    	  2. DestroyList    8. PriorElem             14.LoadList\n");
				printf("    	  3. ClearList      9. NextElem\n");
				printf("    	  4. ListEmpty      10. ListInsert\n");
				printf("    	  5. ListLength     11. ListDelete\n");
				printf("    	  6. GetElem        12. ListTrabverse\n");
				printf("    	  0. Exit\n");
				printf("-------------------------------------------------------------------------\n");
				printf("     请选择你的操作[0~14]:");
				scanf("%d",&op);
			    switch(op){
				    case 1:
				    	j=InitList(L);
					 	if(j==OK)
					 	{
					 		printf("线性表创建成功！\n");
					 		InitInput(L);
						}	
					 	else if(j==ERROR)
					 		printf("线性表创建失败！\n");
						else if(j==INFEASIBLE)
							printf("线性表已存在，不能进行线性表初始化操作！\n");
					 	getchar();
						printf("---任意键继续---\n");
						getchar();
					 	break;
				   	case 2:
				   		j=DestroyList(L);
					 	if(j==OK)
					 		printf("线性表销毁成功！\n");
						else if(j==INFEASIBLE)
							printf("线性表不存在，不能进行线性表销毁操作！\n");
					 	getchar();
						printf("---任意键继续---\n"); 
						getchar();
					 	break;
				   	case 3:
						if(ClearList(L)==OK)
							printf("线性表清空成功！\n");
						else
							printf("线性表不存在，不能进行线性表清空操作！\n");    
					 	getchar();
						printf("---任意键继续---\n");
						getchar();
					 	break;
				   	case 4:
						j=ListEmpty(L);
						if(j==TRUE)
							printf("线性表为空！\n");
						else if(j==FALSE)
							printf("线性表不为空！\n");
						else if(j==INFEASIBLE)
							printf("线性表不存在,不能进行线性表判空操作！\n");    
					 	getchar();
						printf("---任意键继续---\n");
						getchar();
					 	break;
				    case 5:
						j=ListLength(L);
						if(j>=0)
							printf("线性表长度为 %d ！\n",j);
						else
							printf("线性表不存在，不能求表长！\n");    
					 	getchar();
						printf("---任意键继续---\n");
						getchar();
					 	break;
				   	case 6:
					 	printf("请输入查找元素的位置：");
					 	scanf("%d",&i); 
					 	j=GetElem(L,i,e);
					    if(j==OK)
					    	printf("第 %d 位元素是 %d ！\n",i,e);
					    else if(j==ERROR)
					    	printf("所选择的元素位置不合法，可能小于1或大于线性表长度！\n");
					    else if(j==INFEASIBLE)
					    	printf("线性表不存在，不能进行元素获取！\n");
					 	getchar();
						printf("---任意键继续---\n"); 
						getchar();
						break;
				   	case 7:
					 	printf("请输入待查找元素：");
					 	scanf("%d",&e);
						j=LocateElem(L,e);
						if(j>0)
							printf("待查找元素 %d 在线性表中的第 %d 位！\n",e,j);
						else if(j==ERROR)
							printf("查找元素失败，该元素不在线性表中！\n");
						else if(j==INFEASIBLE)
							printf("线性表不存在，不能进行元素查找！\n");
						getchar();
						printf("---任意键继续---\n"); 
						getchar();
						break;
				   	case 8:
						printf("请输入待查找元素以获取其前驱元素：");
						scanf("%d",&e);
						j=PriorElem(L,e,pre);
						if(j==OK)
							printf("元素 %d 的前驱元素是 %d ！\n",e,pre);
						else if(j==ERROR)
							printf("元素 %d 没有前驱元素！\n",e);
						else if(j==INFEASIBLE)
							printf("线性表不存在，不能获取元素！\n");	     
					 	getchar();
						printf("---任意键继续---\n"); 
						getchar();
					 	break;
				   	case 9:
						printf("请输入待查找元素以获取其后继元素：");
						scanf("%d",&e);
						j=NextElem(L,e,next);
						if(j==OK)
							printf("元素 %d 的后继元素是 %d ！\n",e,next);
						else if(j==ERROR)
							printf("元素 %d 没有后继元素！\n",e);
						else if(j==INFEASIBLE)
							printf("线性表不存在，不能获取元素！\n");	   
					 	getchar();
						printf("---任意键继续---"); 
						getchar();
					 	break;
				   	case 10:
						printf("请输入待插入元素：");
						scanf("%d",&e); 
						printf("请输入插入位置后一个元素序号：");
						scanf("%d",&i);
						j=ListInsert(L,i,e);
						if(j==OK)
							printf("插入元素成功！\n");
						else if(j==ERROR)
							printf("插入位置不正确！\n");
						else if(j==INFEASIBLE)
							printf("线性表不存在，不能进行插入操作！\n");   
					 	getchar();
						printf("---任意键继续---"); 
						getchar();
					 	break;
				   	case 11:
					 	printf("请输入需要删除的元素的位置：");
						scanf("%d",&i); 
						j=ListDelete(L,i,e);
						if(j==OK)
							printf("删除元素成功，所删除元素为 %d ！\n",e);
						else if(j==ERROR)
							printf("删除位置不正确！\n");
						else if(j==INFEASIBLE)
							printf("线性表不存在，不能进行删除操作！\n");
					 	getchar();
						printf("---任意键继续---"); 
						getchar();
					 	break;
				   	case 12:
					   	j=ListTraverse(L);
					 	if(j==OK)
						 	printf("\n线性表遍历成功！\n");
						else if(j==ERROR)
							printf("\n线性表中无元素！\n");
						else if(j==INFEASIBLE)
							printf("\n线性表不存在！\n");
						getchar(); 
						printf("---任意键继续---"); 
						getchar();
					 	break;
					case 13:
						printf("请输入待操作文件路径和名称：");
						scanf("%s",FileName);
						j=SaveList(L,FileName);
						if(j==OK)
							printf("线性表中数据已成功写入指定文件中！\n");
						else if(j==INFEASIBLE)
							printf("线性表不存在！\n");
						getchar(); 
						printf("---任意键继续---"); 
						getchar();
						break;
					case 14:
						printf("请输入待操作文件路径和名称：");
						scanf("%s",FileName);
						j=LoadList(L,FileName);
						if(j==OK)
							printf("文件中数据已成功写入线性表中！\n");
						else if(j==INFEASIBLE)
							printf("线性表已存在，直接写入会导致表中原数据丢失！\n");
						getchar(); 
						printf("---任意键继续---"); 
						getchar();
						break;	
					case 0:
			         	break;
				}//end of switch
			}//end of while
		}//end of if	
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()

//菜单功能选择 1 初始化线性表 
status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L.elem==NULL)
    {//使用malloc函数为顺序表开辟空间，表长为LIST_INIT_SIZE
        L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.length=0;
        L.listsize=LIST_INIT_SIZE;
		return OK;
    }
    else
        return INFEASIBLE;	//线性表已存在，不能构造空表
}

//菜单功能选择 2 销毁线性表 
status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L.elem)//通过顺序表首地址的指针是否为空判断线性表是否存在
    {
        L.elem=NULL;
        free(L.elem);
        L.length=0;	//将销毁后线性表表长和空间大小均置为0
        L.listsize=0;
        return OK;
    }
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 3 清空线性表 
status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L.elem)
    {
        L.length=0;	//清空线性表只清除线性表中元素，不销毁表头
        return OK;
    }
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 4 线性表判空
status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem)
    {
        if(L.length==0)	//通过线性表表长判断线性表是否为空
            return TRUE;
        else
            return FALSE;
    }
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 5 求线性表长度
status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if(L.elem)
        return L.length;	//线性表长度可直接由L.length反映
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 6 获取元素
status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{ 
    if(L.elem)
    {
	    if(i<1||i>L.length)	//待获取元素在线性表中位置不合法
	        return ERROR;
		e=L.elem[i-1];	//i为逻辑顺序，i-1为物理顺序
        return OK;
    }
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 7 查找元素 
int LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    int i,flag=1;
    if(L.elem) 
    {
        for(i=0;i<L.length;i++)	//遍历线性表
        {
            if(e==L.elem[i])	//获取线性表中与待查找元素相同的结点
            {
                flag=0;	//flag可用以标记线性表中是否有与待查找元素相同的结点（无flag也可）
                return i+1;	//返回值为逻辑序号
            }
        }
        if(flag)
            return ERROR;	//查找与e元素相同的结点失败
    }
    else
        return INFEASIBLE;	//线性表不存在
}
 
//菜单功能选择 8 获取前驱元素 
status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    int i;
    if(L.elem)
    {
        for(i=1;i<L.length;i++)
        {//遍历线性表
            if(e==L.elem[i])
            {//查找到对应元素后，返回其前驱元素
                pre=L.elem[i-1];
                return OK;
            }
        }
        return ERROR;	//查找与e元素相同的结点失败
    }
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 9 获取后继元素
status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    int i;
    if(L.elem)
    {
        for(i=0;i<L.length-1;i++)
        {//遍历线性表
            if(e==L.elem[i])
            {//查找到对应元素后，返回其后继元素
                next=L.elem[i+1];
                return OK;
            }
        }
        return ERROR;	//查找与e元素相同的结点失败
    }
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 10 插入元素 
status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    int j;
    if(L.elem)
    {	
		if(i<=L.length+1&&i>0&&L.length<L.listsize)	//i位置合法且线性表未满
        {
	        for(j=L.length;j>=i-1;j--)	//将第i个位置（逻辑位置）后的元素全部后移一位，将待插入元素插入到i对应位置
	            L.elem[j]=L.elem[j-1];
	        L.elem[i-1]=e;
			L.length++;	//线性表长度增加
            return OK;
        }
        else if(i<=L.length+1&&i>0&&L.length>=L.listsize)	//i位置合法且线性表已满
        {
            L.elem=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));	//为线性表增加空间以存放新增数据元素
            L.listsize+=LISTINCREMENT;	//线性表空间增加
        	for(j=L.length;j>=i-1;j--)
	            L.elem[j]=L.elem[j-1];
	        L.elem[i-1]=e;
			L.length++;
            return OK;
		}
        else
            return ERROR;	//i位置不合法
    }
    else
        return INFEASIBLE;	//线性表不存在
} 

//菜单功能选择 11 删除元素
status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem)
    {
        if(L.length>0&&i<L.length&&i>0)	//i位置合法
        {
            e=L.elem[i-1];	//利用i定位元素，并保存在e中
			for(;i<L.length;i++)	//将i位置之后的元素在线性表中前移一位
                L.elem[i-1]=L.elem[i];
            L.length--;	//表长减1
            return OK;
        }
        else
            return ERROR;	//i位置不合法
    }
    else
        return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 12 遍历线性表 
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L.elem)
    {
        if(!L.length)	//线性表为空
        	return ERROR;
		for(int i=0;i<L.length;i++)
        {
            if(i!=L.length-1)	//遍历线性表达到末位
                printf("%d ",L.elem[i]);
            else
                printf("%d",L.elem[i]);
        }    
        return OK;
    }
    else
        return INFEASIBLE;	//线性表不存在
} 

//菜单功能选择 13 线性表存档 
status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    FILE *fp;
    int i=0;
	if(L.elem)
	{
		fp=fopen(FileName,"wb");
		if(!fp)	//文件打开失败
			return ERROR;
		while(i<L.length)
		{
			fprintf(fp,"%d ",L.elem[i]);	//将线性表中数据写入文件
			i++;
		}
		fclose(fp);
		return OK;
	}
	else
		return INFEASIBLE;	//线性表不存在
}

//菜单功能选择 14 线性表读档 
status  LoadList(SqList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	FILE *fp;
    int i=0; 
	if(L.elem)
		return INFEASIBLE;	//线性表已存在，读档会使元素失去
	else
	{
		L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);	//初始化线性表
        L.length=0;
       	L.listsize=LIST_INIT_SIZE;
		if((fp=fopen(FileName,"rb"))!=NULL)
		{
			while((fscanf(fp,"%d ",&L.elem[i]))!=EOF)	//文件未读取完成
            {
                if(L.length<L.listsize-1)	//线性表未满，直接读入数据
                {
	                L.length++;
	                i++;
				}
				else	//线性表已满，重新分配空间再读入数据
				{
					L.elem=(ElemType *)realloc(L.elem,sizeof(ElemType)*(L.listsize+LISTINCREMENT));
					L.listsize+=LISTINCREMENT;
					L.length++;
					i++;
				}
            } 
		}
		fclose(fp);
		return OK;
	}
} 

//菜单功能选择 15 多线性表管理之增加空线性表 
status AddList(LISTS &Lists,char ListName[])
// 在Lists中增加一个名称为ListName的空线性表，线性表数据由主函数插入。
{
    if(Lists.length<Lists.listsize)
    {
    	int i,flag=0;
    	for(i=0;i<Lists.length;i++)
			if(!strcmp(Lists.elem[i].name,ListName))
			{//对线性表名称进行比较查找，查找成功时标记并退出循环
				flag=1;
				break;
			}				
		if(!flag)	//查找失败，说明中无此线性表，可以新增
		{
			strcpy(Lists.elem[Lists.length].name,ListName);	//调用strcpy函数复制线性表名称
			Lists.elem[Lists.length].L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));	//为线性表开辟空间初始化空间大小和长度
			Lists.elem[Lists.length].L.listsize=LIST_INIT_SIZE;	//初始化空间大小和长度
			Lists.elem[Lists.length].L.length=0;
			Lists.length++;	//集合长度增加
			return OK;
		}
	    else	//线性表已存在，不能新增
			return ERROR;	
	}
	else	//线性表集合已满，不能添加线性表
		return OVERFLOW;
} 

//菜单功能选择 16 多线性表管理之删除线性表 
status RemoveList(LISTS &Lists,char ListName[])
// 在Lists中删除一个名称为ListName的线性表。 
{
    int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
		if(!strcmp(Lists.elem[i].name,ListName))
		{//对线性表名称进行比较查找，查找成功时标记并退出循环
			flag=1;
			break;
		}
	}
	if(flag)	//查找成功
	{
		for(;i<Lists.length-1;i++)	//将查找到的线性表后的线性表顺序前移一位
			Lists.elem[i]=Lists.elem[i+1];
		Lists.elem[Lists.length-1].name[0]='\0';	//将原本最末位的线性表名称和内容置为空
		Lists.elem[Lists.length-1].L.elem=NULL;
		Lists.elem[Lists.length-1].L.length=0;
		Lists.elem[Lists.length-1].L.listsize=0;
		Lists.length--;
		return OK;
	}
	else
		return ERROR;
} 

//菜单功能选择 17 多线性表管理之查找线性表 
int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，查找成功返回逻辑序号，否则返回ERROR。 
{
	int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
		if(!strcmp(Lists.elem[i].name,ListName))
		{//对线性表名称进行比较查找，查找成功时标记并退出循环
			flag=1;
			break;
		}
	}
	if(!flag||!Lists.length)	//查找失败或线性表集合长度为0
		return ERROR;
	else    //查找成功返回逻辑位置
		return i+1;
}

//辅助函数：线性表数据输入
status InitInput(SqList &L)
// 选择是否向线性表中输入数据，是则由用户输入以0为结束标志的一组数据，返回OK，否则返回0。
{
	int ord, temp; 
	printf("输入数据选择1，否则选择0：\n");
	scanf("%d",&ord);
	if(ord==0)	//以0为结束标志
		return 0;
	else
	{
		printf("请输入一组数据，0为结束标志：\n");
		scanf("%d",&temp);
		while(temp != 0)	//元素输入截止的标志
		{
			ListInsert(L,L.length+1,temp);	//调用插入函数在线性表尾部增加元素
			scanf("%d",&temp);
		}
		printf("输入成功！\n");
		return OK;
	}
}

//辅助函数：进入二级菜单
void SecondaryTable(SqList &L,int op)
// 将所选的多线性表集合中的待操作线性表传递进入二级菜单中，实现对单线性表的基本操作。
{
	int i,j;
	ElemType e,pre,next;
	char FileName[30];
	while(op!=-1)
	{
		system("cls");	printf("\n\n");
		printf("              Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------------------------------\n");
		printf("    	  1. InitList       7. LocateElem            13.SaveList\n");
		printf("    	  2. DestroyList    8. PriorElem             14.LoadList\n");
		printf("    	  3. ClearList      9. NextElem\n");
		printf("    	  4. ListEmpty      10. ListInsert\n");
		printf("    	  5. ListLength     11. ListDelete\n");
		printf("    	  6. GetElem        12. ListTrabverse\n");
		printf("    	  -1. Exit\n");
		printf("-------------------------------------------------------------------------\n");
		printf("     请选择你的操作[-1或1~14]:");
		scanf("%d",&op);
		switch(op){
			case 1:
				j=InitList(L);
				if(j==OK)
				{
					printf("线性表创建成功！\n");
					InitInput(L);
				}	
				else if(j==ERROR)
					printf("线性表创建失败！\n");
				else if(j==INFEASIBLE)
					printf("线性表已存在，不能进行线性表初始化操作！\n");
				getchar();
				printf("---任意键继续---\n");
				getchar();
				break;
			case 2:
				j=DestroyList(L);
				if(j==OK)
					printf("线性表销毁成功！\n");
				else if(j==ERROR)
					printf("线性表销毁失败！\n");
				else if(j==INFEASIBLE)
					printf("线性表不存在，不能进行线性表销毁操作！\n");
			 	getchar();
				printf("---任意键继续---\n"); 
				getchar();
			 	break;
		   	case 3:
				if(ClearList(L)==OK)
					printf("线性表清空成功！\n");
				else
					printf("线性表不存在，不能进行线性表清空操作！\n");    
				getchar();
				printf("---任意键继续---\n");
				getchar();
				break;
			case 4:
				j=ListEmpty(L);
				if(j==TRUE)
					printf("线性表为空！\n");
				else if(j==FALSE)
					printf("线性表不为空！\n");
				else if(j==INFEASIBLE)
					printf("线性表不存在,不能进行线性表判空操作！\n");    
				getchar();
				printf("---任意键继续---\n");
				getchar();
				break;
			case 5:
				j=ListLength(L);
				if(j>=0)
					printf("线性表长度为 %d ！\n",j);
				else
					printf("线性表不存在，不能求表长！\n");    
				getchar();
				printf("---任意键继续---\n");
				getchar();
				break;
			case 6:
				printf("请输入查找元素的位置：");
				scanf("%d",&i); 
				j=GetElem(L,i,e);
				if(j==OK)
					printf("第 %d 位元素是 %d ！\n",i,e);
				else if(j==ERROR)
					printf("所选择的元素位置不合法，可能小于1或大于线性表长度！\n");
				else if(j==INFEASIBLE)
					printf("线性表不存在，不能进行元素获取！\n");
				getchar();
				printf("---任意键继续---\n"); 
				getchar();
				break;
			case 7:
				printf("请输入待查找元素：");
				scanf("%d",&e);
				j=LocateElem(L,e);
				if(j>0)
					printf("待查找元素 %d 在线性表中的第 %d 位！\n",e,j);
				else if(j==ERROR)
					printf("查找元素失败，该元素不在线性表中！\n");
				else if(j==INFEASIBLE)
					printf("线性表不存在，不能进行元素查找！\n");
				getchar();
				printf("---任意键继续---\n"); 
				getchar();
				break;
			case 8:
				printf("请输入待查找元素以获取其前驱元素：");
				scanf("%d",&e);
				j=PriorElem(L,e,pre);
				if(j==OK)
					printf("元素 %d 的前驱元素是 %d ！\n",e,pre);
				else if(j==ERROR)
					printf("元素 %d 没有前驱元素！\n",e);
				else if(j==INFEASIBLE)
					printf("线性表不存在，不能获取元素！\n");	     
				getchar();
				printf("---任意键继续---\n"); 
				getchar();
				break;
			case 9:
				printf("请输入待查找元素以获取其后继元素：");
				scanf("%d",&e);
				j=NextElem(L,e,next);
				if(j==OK)
					printf("元素 %d 的后继元素是 %d ！\n",e,next);
				else if(j==ERROR)
					printf("元素 %d 没有后继元素！\n",e);
				else if(j==INFEASIBLE)
					printf("线性表不存在，不能获取元素！\n");	   
				getchar();
				printf("---任意键继续---"); 
				getchar();
				break;
			case 10:
				printf("请输入待插入元素：");
				scanf("%d",&e); 
				printf("请输入插入位置后一个元素序号：");
				scanf("%d",&i);
				j=ListInsert(L,i,e);
				if(j==OK)
					printf("插入元素成功！\n");
				else if(j==ERROR)
					printf("插入位置不正确！\n");
				else if(j==INFEASIBLE)
					printf("线性表不存在，不能进行插入操作！\n");   
				getchar();
				printf("---任意键继续---"); 
				getchar();
				break;
			case 11:
				printf("请输入需要删除的元素的位置：");
				scanf("%d",&i);
				j=ListDelete(L,i,e);
				if(j==OK)
					printf("删除元素成功，所删除元素为 %d ！\n",e);
				else if(j==ERROR)
					printf("删除位置不正确！\n");
				else if(j==INFEASIBLE)
					printf("线性表不存在，不能进行删除操作！\n");
				getchar();
				printf("---任意键继续---"); 
				getchar();
				break;
			case 12:
				j=ListTraverse(L);
				if(j==OK)
					printf("\n线性表遍历成功！\n");
				else if(j==ERROR)
					printf("\n线性表中无元素！\n");
				else if(j==INFEASIBLE)
					printf("\n线性表不存在！\n");
				getchar(); 
				printf("---任意键继续---"); 
				getchar();
				break;
			case 13:
				printf("请输入待操作文件路径和名称：");
				scanf("%s",FileName);
				j=SaveList(L,FileName);
				if(j==OK)
					printf("线性表中数据已成功写入指定文件中！\n");
				else if(j==INFEASIBLE)
					printf("线性表不存在！\n");
				getchar(); 
				printf("---任意键继续---"); 
				getchar();
				break;
			case 14:
				printf("请输入待操作文件路径和名称：");
				scanf("%s",FileName);
				j=LoadList(L,FileName);
				if(j==OK)
					printf("文件中数据已成功写入线性表中！\n");
				else if(j==INFEASIBLE)
					printf("线性表已存在，直接写入会导致表中原数据丢失！\n");
				getchar(); 
				printf("---任意键继续---"); 
				getchar();
				break;	
			case -1:
				break;
		}//end of switch
	}//end of while
}