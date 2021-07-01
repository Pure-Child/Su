/* Linear Table On Sequence Structure */
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2 //预定义的常量 

typedef int status;
typedef int ElemType; //数据元素类型定义

typedef struct LNode{   //单链表（链式结构）结点的定义
    ElemType data;      //单链表数据元素存放
    struct LNode *next; //单链表下一结点指向
}LNode,*LinkList;
typedef struct{  //线性表的管理表定义
    struct { char name[30]; //线性表名称 
     		LinkList L;	//线性表头指针
    } elem[10]; //存放线性表的集合 
    int length; //线性表集合的长度 
    int listsize; //线性表集合分配的空间 
}LISTS;

void SecondaryTable(LinkList &L,int op);
status InitInput(LinkList &L); //线性表数据输入 
status InitList(LinkList &L); //线性表初始化 
status DestroyList(LinkList &L); //线性表销毁 
status ClearList(LinkList &L); //线性表清空 
status ListEmpty(LinkList L); //线性表判空 
int ListLength(LinkList L); //求线性表表长 
status GetElem(LinkList L,int i,ElemType &e); //获取元素 
status LocateElem(LinkList L,ElemType e); //查找元素 
status PriorElem(LinkList L,ElemType e,ElemType &pre); //获取前驱元素 
status NextElem(LinkList L,ElemType e,ElemType &next); //获取后继元素 
status ListInsert(LinkList &L,int i,ElemType e); //插入元素 
status ListDelete(LinkList &L,int i,ElemType &e); //删除元素 
status ListTraverse(LinkList L); //遍历线性表 
status SaveList(LinkList L,char FileName[]); //线性表存档 
status LoadList(LinkList &L,char FileName[]); //线性表读档 
status AddList(LISTS &Lists,char ListName[]); //增加空线性表 
status RemoveList(LISTS &Lists,char ListName[]); //移除线性表
int LocateList(LISTS Lists,char ListName[]); //查找线性表 

int main(){
	LinkList L;
    LISTS Lists;
	int op=1;
	int i,j;
	ElemType e,pre,next;
	char Name[30]={'\0'},FileName[30]={'\0'};
    L->data=NULL;
    L->next=NULL;
    Lists.length=0;
	Lists.listsize=10;
    for(j=0;j<10;j++)
	{
		Lists.elem[j].L=NULL;
	}//初始化 
    while (op!=-3){
        system("cls");	printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("          -1.MainTable/MultiList     -2.SingleList\n");
        printf("    	  -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     请选择所在的菜单层级：\n");
        printf("     -1：主菜单实现多线性表管理，-2：临时单线性表基本操作。\n");
        scanf("%d",&op);
		if(op==-1){
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
                    if(Lists.elem[i].L==NULL&&Lists.elem[i+5].L==NULL)
                        printf("\t线性表%d：未创建            \t线性表%d：未创建",i+1,i+6);
                    else if(Lists.elem[i].L==NULL&&Lists.elem[i+5].L!=NULL)
                        printf("\t线性表%d：未创建            \t线性表%d：%s",i+1,i+6,Lists.elem[i+5].name);
                    else if(Lists.elem[i].L!=NULL&&Lists.elem[i+5].L==NULL)
                        printf("\t线性表%d：%s                \t线性表%d：未创建",i+1,Lists.elem[i].name,i+6);
                    else
                        printf("\t线性表%d：%s                \t线性表%d：%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
                    printf("\n");
                }
                printf("\n     请选择你的操作[0或15~18]:");
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
                            printf("---任意键继续---\n");
							getchar();
							break;
						}
						break;
					case 0:
						break;	
				}//end of switch
			}//end of while
		}//end of if
        if(op==-2){
            while(op){
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
                            printf("创建线性表成功！\n");
                            InitInput(L);
                        }
                        else
                            printf("创建线性表失败，线性表已存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyList(L);
                        if(j==OK)
                            printf("销毁线性表成功！\n");
                        else
                            printf("线性表不存在，不能进行销毁操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 3:
                        j=ClearList(L);
                        if(j==OK)
                            printf("清空线性表成功！\n");
                        else
                            printf("线性表不存在，不能进行清空操作！\n");
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
                        else
                            printf("线性表不存在，不能进行判空操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 5:
                        j=ListLength(L);
                        if(j>=0)
                            printf("线性表长度为 %d ！\n",j);
                        else
                            printf("线性表不存在，不能进行求表长操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 6:
                        printf("请输入查找元素的位置：");
                        scanf("%d",&i);
                        j=GetElem(L,i,e);
                        if(j==OK)
                            printf("获取元素成功，第 %d 个元素是 %d ！\n",i,e);
                        else if(j==ERROR)
                            printf("获取元素失败，i的值不合法！\n");
                        else 
                            printf("线性表不存在，不能获取元素！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 7:
                        printf("请输入待查找元素：");
                        scanf("%d",&e);
                        j=LocateElem(L,e);
                        if(j>0)
                            printf("查找元素成功，%d 是线性表中第 %d 个元素！\n",e,j);
                        else if(j==ERROR)
                            printf("查找元素失败，%d 不在线性表中！\n",e);
                        else 
                            printf("线性表不存在，不能查找元素！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break; 
                    case 8:
                        printf("请输入待查找元素以获取其前驱元素：");
                        scanf("%d",&e);
                        j=PriorElem(L,e,pre);
                        if(j==OK)
                            printf("获取元素前驱成功，%d 的前驱元素是 %d ！\n",e,pre);
                        else if(j==ERROR)
                            printf("获取元素前驱失败，%d 无前驱元素！\n",e);
                        else 
                            printf("线性表不存在，不能获取前驱元素！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 9:
                        printf("请输入待查找元素以获取其后继元素：");
                        scanf("%d",&e);
                        j=NextElem(L,e,next);
                        if(j==OK)
                            printf("获取元素后继成功，%d 的后继元素是 %d ！\n",e,next);
                        else if(j==ERROR)
                            printf("获取元素后继失败，%d 无后继元素！\n",e);
                        else 
                            printf("线性表不存在，不能获取后继元素！\n");
                        getchar();
                        printf("---任意键继续---\n");
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
                            printf("插入元素失败，插入位置不正确！\n");
                        else 
                            printf("线性表不存在，不能进行插入操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 11:
                        printf("请输入需要删除的元素的位置：");
                        scanf("%d",&i);
                        j=ListDelete(L,i,e);
                        if(j==OK)
                            printf("删除元素成功，删除的元素为 %d ！\n",e);
                        else if(j==ERROR)
                            printf("删除元素失败，删除位置不正确！\n");
                        else 
                            printf("线性表不存在，不能进行删除操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 12:
                        j=ListTraverse(L);
                        if(j==OK)
                            printf("\n遍历线性表成功！\n");
                        else if(j==ERROR)
                            printf("\n线性表中无元素！\n");
                        else
                            printf("\n线性表不存在，不能进行遍历操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 13:
                        printf("请输入待操作文件路径和名称：");
                        scanf("%s",FileName);
                        j=SaveList(L,FileName);
                        if(j==OK)
                            printf("线性表存档成功！\n");
                        else
                            printf("线性表不存在，不能进行存档操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 14:
                        printf("请输入待操作文件路径和名称：");
                        scanf("%s",FileName);
                        j=LoadList(L,FileName);
                        if(j==OK)
                            printf("线性表读档成功！\n");
                        else
                            printf("线性表已存在，读档可能失去原始数据！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                }//end of switch
            }//end of while
        }//end of if
    }
	printf("欢迎下次再使用本系统！\n"); 
}//end of main()

//菜单选择功能 1 创建线性表
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L)   //表头结点已存在，说明线性表存在
        return INFEASIBLE;
    else
    {
        L=(LinkList)malloc(sizeof(LNode));  //初始化表头结点
        return OK;
    }
}

//菜单选择功能 2 销毁线性表 
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if(L)
    {
        LNode *p=L->next;
        while(p)
        {//利用指针p逐个释放单链表结点空间
            L->next=p->next;
            free(p);
            p=NULL;
            p=L->next;
        }
        free(L);
        L=NULL; //释放表头结点空间
        return OK;
    }
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 3 清空线性表 
status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if(L)
    {
        struct LNode *p=L->next;
        while(p)
        {//利用指针p逐个释放单链表结点空间
            L->next=p->next;
            free(p);
            p=L->next;
        }
        return OK;  //表头结点依然保留
    }
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 4 线性表判空 
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if(L)
        if(L->next==NULL)     //线性表存在且表头结点的下一结点不为空
            return TRUE;
        else
            return FALSE;
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 5 求表长 
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    int len;
    if(L)
    {
        LinkList t=L;
        for(;t;t=t->next)
        {//利用指针t遍历线性表，用len记录表长
            if(t->next)
                len++;
        }
        return len;
    }
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 6 获取元素 
status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L)
    {
        if(i<1) //i的位置不合法
            return ERROR;
        else
        {
            LinkList t=L;
            for(;t;i--,t=t->next)
                if(!i)
                {//i递减至0时即查找到元素，保存在e中
                    e=t->data;
                    return OK;
                }
            return ERROR;   //i的位置大于表长
        }
    }
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 7 查找元素 
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if(L)
    {
        LinkList t=L;
        for(int i=0;t;t=t->next,i++)    //用t遍历线性表，用i记录元素位置
            if(e==t->data)
                return i;
        if(!t)  //遍历结束后仍无法查找到e，即元素e不存在于线性表中
            return ERROR;
    }
    else
        return INFEASIBLE;  //线性表不存在
}
 
 //菜单功能选择 8 获取前驱元素 
 status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L)
    {
        LinkList t=L;
        for(int i=0;t->next;t=t->next,i++)
            if(e==t->next->data&&i!=0)  //由于要获取前驱元素，因此需要找到t的下一结点值与e相等，将此时t结点值保存在pre中
            {
                pre=t->data;
                return OK;
            }
        return ERROR;   //元素e不在线性表中
    }
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 9 获取后继元素
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L)
    {
        LinkList t=L;
        for(int i=0;t->next;t=t->next,i++)
            if(e==t->data)  //查找到与e相等的结点后，返回后一结点值
            {
                next=t->next->data;
                return OK;
            }
        return ERROR;   //元素e不在线性表中
    }
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 10 插入元素 
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L)
    {
        LinkList t=L;
        for(int j=0;t;t=t->next,j++)
        {
            if(j+1==i)  //j标记t指向i位置的前一个元素
            {//利用两个结点指针完成插入操作
                LinkList tag;
                tag=(LinkList)malloc(sizeof(LNode));
                tag->data=e;
                tag->next=t->next;
                t->next=tag;
                return OK;
            }
        }
        return ERROR;   //i位置不合法
    }
    else
        return INFEASIBLE;  //线性表不存在
}
 
//菜单功能选择 11 删除元素
status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if(L)
    {
        LinkList t=L;
        for(int j=0;t;t=t->next,j++)
            if(j+1==i)  //j标记t指向i位置的前一个元素
            {//利用两个结点指针完成删除操作
                LinkList tag=t->next;
                e=t->next->data;
                t->next=t->next->next;
                free(tag);
                return OK;
            }
        return ERROR;   //i位置不合法
    }
    else
        return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 12 遍历线性表
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if(L)
    {
        LinkList t=L->next;
        int flag=0;
        for(;t;t=t->next)
        {//用t指针遍历线性表
            flag=1; //标记线性表是否为空（不使用flag也可有正确返回值）
            if(t->next)
                printf("%d ",t->data);
            else
                printf("%d",t->data);
        }
        if(flag)
            return OK;
        else
            return ERROR;   //线性表为空
    }
    else
        return INFEASIBLE;  //线性表不存在
} 

//菜单功能选择 13 线性表存档
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	if(L)
	{
		LinkList t=L->next;
		FILE *fp;
		fp=fopen(FileName,"wb");
		while(t)
		{//用t指针遍历线性表，将线性表元素写入文件中
			fprintf(fp,"%d ",t->data);
			t=t->next;
		}
		fclose(fp);
		return OK;
	}
	else
		return INFEASIBLE;  //线性表不存在
}

//菜单功能选择 14 线性表读档 
status LoadList(LinkList &L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	if(!L)
	{
		L=(LinkList)malloc(sizeof(LNode));  //初始化表头结点
		L->next=NULL;
		FILE *fp;
		LinkList t;
		if((fp=fopen(FileName,"rb"))!=NULL)
		{
			L->next=(LinkList)malloc(sizeof(LNode));    //使用先进先出的单链表，将文件中数据元素读入线性表中
			t=L->next;
			t->next=NULL;
			while((fscanf(fp,"%d ",&t->data))!=EOF)
			{
				if(!feof(fp))
				{
					t->next=(LinkList)malloc(sizeof(LNode));
					t=t->next;
				}
			}
			t->next=NULL;
			fclose(fp);
		}
		return OK;
	}
	else
		return INFEASIBLE;  //线性表已存在，读档会使其中元素失去
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
			Lists.elem[Lists.length].L=(LinkList)malloc(sizeof(LNode));	//为线性表表头结点开辟空间
            Lists.elem[Lists.length].L->next=NULL;
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
	if(flag)
	{
		DestroyList(Lists.elem[i].L);   //调用销毁线性表函数销毁当前线性表
        for(;i<Lists.length-1;i++)	//将查找到的线性表后的线性表顺序前移一位
			Lists.elem[i]=Lists.elem[i+1];
        if(i!=Lists.length-1)   //若最末位线性表未被销毁，调用销毁线性表函数销毁
            DestroyList(Lists.elem[Lists.length-1].L);
        Lists.elem[Lists.length-1].name[0]='\0';	//将原本最末位的线性表名称置为空，释放其表头结点
        Lists.elem[Lists.length-1].L=NULL;
        free(Lists.elem[Lists.length-1].L);
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

//辅助函数：输入线性表元素
status InitInput(LinkList &L)
// 选择是否向线性表中输入数据，是则由用户输入以0为结束标志的一组数据，返回OK，否则返回0。 
{
	int ord,temp;
	LinkList tail=L,p=L;
	printf("输入数据选择1，否则选择0：\n");
	scanf("%d",&ord);
	if(ord)
	{
		printf("请输入一组数据创建先进先出链表，0为结束标志：\n");
        scanf("%d",&temp);
		while(temp)
		{//先进先出的单链表创建
			tail=(LinkList)malloc(sizeof(LNode));
			tail->data=temp;
			tail->next=NULL;
			p->next=tail;
			p=p->next;
			scanf("%d",&temp);
		}
		printf("输入成功！\n");
        return 0;
	}
	else
		return 0;
} 

//辅助函数：进入二级菜单
void SecondaryTable(LinkList &L,int op)
// 将所选的多线性表集合中的待操作线性表传递进入二级菜单中，实现对单线性表的基本操作。
{
	int i,j;
	ElemType e,pre,next;
	char FileName[30];
    while(op!=-1){
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
                    printf("创建线性表成功！\n");
                    InitInput(L);
                }
                else
                    printf("创建线性表失败，线性表已存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 2:
                j=DestroyList(L);
                if(j==OK)
                    printf("销毁线性表成功！\n");
                else
                    printf("线性表不存在，不能进行销毁操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 3:
                j=ClearList(L);
                if(j==OK)
                    printf("清空线性表成功！\n");
                else
                    printf("线性表不存在，不能进行清空操作！\n");
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
                else
                    printf("线性表不存在，不能进行判空操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 5:
                j=ListLength(L);
                if(j>=0)
                    printf("线性表长度为 %d ！\n",j);
                else
                    printf("线性表不存在，不能进行求表长操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 6:
                printf("请输入查找元素的位置：");
                scanf("%d",&i);
                j=GetElem(L,i,e);
                if(j==OK)
                    printf("获取元素成功，第 %d 个元素是 %d ！\n",i,e);
                else if(j==ERROR)
                    printf("获取元素失败，i的值不合法！\n");
                else 
                    printf("线性表不存在，不能获取元素！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 7:
                printf("请输入待查找元素：");
                scanf("%d",&e);
                j=LocateElem(L,e);
                if(j>0)
                    printf("查找元素成功，%d 是线性表中第 %d 个元素！\n",e,j);
                else if(j==ERROR)
                    printf("查找元素失败，%d 不在线性表中！\n",e);
                else 
                    printf("线性表不存在，不能查找元素！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break; 
            case 8:
                printf("请输入待查找元素以获取其前驱元素：");
                scanf("%d",&e);
                j=PriorElem(L,e,pre);
                if(j==OK)
                    printf("获取元素前驱成功，%d 的前驱元素是 %d ！\n",e,pre);
                else if(j==ERROR)
                    printf("获取元素前驱失败，%d 无前驱元素！\n",e);
                else 
                    printf("线性表不存在，不能获取前驱元素！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 9:
                printf("请输入待查找元素以获取其后继元素：");
                scanf("%d",&e);
                j=NextElem(L,e,next);
                if(j==OK)
                    printf("获取元素后继成功，%d 的后继元素是 %d ！\n",e,next);
                else if(j==ERROR)
                    printf("获取元素后继失败，%d 无后继元素！\n",e);
                else 
                    printf("线性表不存在，不能获取后继元素！\n");
                getchar();
                printf("---任意键继续---\n");
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
                    printf("插入元素失败，插入位置不正确！\n");
                else 
                    printf("线性表不存在，不能进行插入操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 11:
                printf("请输入需要删除的元素的位置：");
                scanf("%d",&i);
                j=ListDelete(L,i,e);
                if(j==OK)
                    printf("删除元素成功，删除的元素为 %d ！\n",e);
                else if(j==ERROR)
                    printf("删除元素失败，删除位置不正确！\n");
                else 
                    printf("线性表不存在，不能进行删除操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 12:
                j=ListTraverse(L);
                if(j==OK)
                    printf("\n遍历线性表成功！\n");
                else if(j==ERROR)
                    printf("\n线性表中无元素！\n");
                else
                    printf("\n线性表不存在，不能进行遍历操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 13:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=SaveList(L,FileName);
                if(j==OK)
                    printf("线性表存档成功！\n");
                else
                    printf("线性表不存在，不能进行存档操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 14:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=LoadList(L,FileName);
                if(j==OK)
                    printf("线性表读档成功！\n");
                else
                    printf("线性表已存在，读档可能失去原始数据！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case -1:
                break;
        }//end of switch
    }//end of while
}