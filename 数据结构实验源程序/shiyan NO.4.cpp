/* Linear Table On Sequence Structure */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAX_KEY 100
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;

typedef struct {
        KeyType  key;
        char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
        int adjvex;              //顶点位置编号 
        struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode{				//头结点及其数组类型定义
        VertexType data;       	//顶点信息
        ArcNode *firstarc;      	 //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;
typedef struct{  //无向图的管理表定义
    struct { char name[30]; //无向图名称 
     		ALGraph G;	
    } elem[10]; //存放无向图的集合 
    int length; //无向图集合的长度 
    int listsize; //无向图集合分配的空间 
}LISTS; 

typedef int ElemType;   //栈和队列的定义
typedef struct stack
{
    ElemType elem[MAX_VERTEX_NUM];
    int p;
} stack; //栈的定义
typedef struct QUEUE
{
    ElemType elem[MAX_VERTEX_NUM];
    int front, length;
} QUEUE; //循环队列

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G,KeyType u);
status PutVex(ALGraph &G,KeyType u,VertexType value);
int FirstAdjVex(ALGraph G,KeyType u);
int NextAdjVex(ALGraph G,KeyType v,KeyType w);
status InsertVex(ALGraph &G,VertexType v);
status DeleteVex(ALGraph &G,KeyType v);
status InsertArc(ALGraph &G,KeyType v,KeyType w);
status DeleteArc(ALGraph &G,KeyType v,KeyType w);
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status AddGraph(LISTS &Lists,char ListName[]);
status RemoveGraph(LISTS &Lists,char ListName[]);
int LocateGraph(LISTS Lists,char ListName[]);
void SecondaryTable(ALGraph &G,int op);
void DFS(AdjList verx,int index,int visited[100],void (*visit)(VertexType));
void visit(VertexType v);
void iniStack(stack &S);
int isEmptyStack(stack &S);
int push(stack &S, ElemType e);
ElemType pop(stack &S);
void iniQueue(QUEUE &Q);
int enQueue(QUEUE &Q, ElemType e);
int deQueue(QUEUE &Q, ElemType &e);
int isEmptyQueue(QUEUE &Q);

int main(){
    int i,j,op=1;
    char Name[30]={'\0'},FileName[30]={'\0'};
    KeyType u,w;
    ALGraph G;
    VertexType value;
    LISTS Lists;
    G.vexnum=G.arcnum=0;
    G.kind=UDG;   
    value.key=0;
    value.others[0]='\0';   
    Lists.length=0;
	Lists.listsize=10;
	for(j=0;j<10;j++)
	{
		Lists.elem[j].G.arcnum=Lists.elem[j].G.vexnum=0;
		Lists.elem[j].G.kind=UDG;
	}//初始化 
	while(op!=-3){
        system("cls");	printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("         -1.MainTable/MultiGraph     -2.SingleGraph\n");
        printf("    	 -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     请选择所在的菜单层级：\n");
        printf("     -1：主菜单实现多无向图管理，-2：临时单无向图基本操作。\n");
		scanf("%d",&op);
		if(op==-1)
		{
			while(op)
			{
                system("cls");	printf("\n\n");
                printf("            Menu for Linear Table On Sequence Structure \n");
                printf("---------------------------------------------------------------------\n");
                printf("         15.AddGraph        16.RemoveGraph      17.LocateGraph\n");
                printf("         18.SecondaryTable\n");
                printf("    	 0. Exit\n");
                printf("---------------------------------------------------------------------\n");
                for(i=0;i<5;i++)
                {
                    if(Lists.elem[i].G.vexnum==0&&Lists.elem[i+5].G.vexnum==0)
                        printf("\t无向图%d：未创建            \t无向图%d：未创建",i+1,i+6);
                    else if(Lists.elem[i].G.vexnum==0&&Lists.elem[i+5].G.vexnum!=0)
                        printf("\t无向图%d：未创建            \t无向图%d：%s",i+1,i+6,Lists.elem[i+5].name);
                    else if(Lists.elem[i].G.vexnum!=0&&Lists.elem[i+5].G.vexnum==0)
                        printf("\t无向图%d：%s                \t无向图%d：未创建",i+1,Lists.elem[i].name,i+6);
                    else
                        printf("\t无向图%d：%s                \t无向图%d：%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
                    printf("\n");
                }
                printf("     请选择你的操作[0或15~18]:");
				scanf("%d",&op);
				switch(op){
                    case 15:
                        printf("请输入待添加的无向图名称：");
                        scanf("%s",Name);
                        j=AddGraph(Lists,Name);
                        if(j==OK)
                            printf("无向图添加成功！\n");
                        else if(j==INFEASIBLE)
                            printf("无向图添加失败，该无向图已存在！\n");
                        else if(j==OVERFLOW)
                            printf("无向图添加失败，无向图集合已满！\n");
                        else if(j==ERROR)
                            printf("创建无向图失败，无向图为空或数据输入错误！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 16:
                        printf("请输入待删除的无向图名称：");
						scanf("%s",Name);
						j=RemoveGraph(Lists,Name);
						if(j==OK)
							printf("无向图删除成功！\n");
						else if(j==ERROR)
							printf("无向图删除失败，集合中无此无向图！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 17:
                        printf("请输入待查找的无向图名称：");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							printf("该无向图位于集合中第 %d 位！\n",j);
						else
							printf("无向图查找失败，集合中无此无向图！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 18:
                        printf("请输入待操作的无向图名称：");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].G,op);
						else
						{
							getchar();
							printf("无向图不存在于集合中，不能进入单无向图操作！\n");
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
        if(op==-2)
        {
            while(op){
                system("cls");
                printf("\n\n");
                printf("                Menu for Linear Table On Sequence Structure \n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("    	  1. CreateGraph        7. InsertVex            13. SaveGraph\n");
                printf("    	  2. DestroyGraph       8. DeleteVex            14. LoadGraph\n");
                printf("    	  3. LocateVex          9. InsertArc            15. ShowGraph\n");
                printf("    	  4. PutVex             10. DeleteArc\n");
                printf("    	  5. FirstAdjVex        11. DFSTraverse\n");
                printf("    	  6. NextAdjVex         12. BFSTraverse\n");
                printf("    	  0. Exit\n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("     请选择你的操作[0~15]:");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        i=0;
                        VertexType V[30];
                        KeyType VR[100][2];
                        printf("请输入图中所有顶点关键字和字符串，输入（-1，null）终止：\n");
                        do {
                            scanf("%d%s",&V[i].key,V[i].others);
                        } while(V[i++].key!=-1);
                        i=0;
                        printf("请输入图中所有弧，输入（-1，-1）终止：\n");
                        do {
                            scanf("%d%d",&VR[i][0],&VR[i][1]);
                        } while(VR[i++][0]!=-1);
                        j=CreateGraph(G,V,VR);
                        if(j==OK)
                            printf("创建无向图成功！\n");
                        else if(j==INFEASIBLE)
                            printf("无向图添加失败，该无向图已存在！\n");
                        else if(j==ERROR)
                            printf("创建无向图失败，无向图数据输入错误！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyGraph(G);
                        if(j==OK)
                            printf("销毁无向图成功！\n");
                        else
                            printf("销毁无向图失败，无向图不存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 3:
                        printf("请输入待查找顶点关键字：");
                        scanf("%d",&u);
                        j=LocateVex(G,u);
                        if(j==INFEASIBLE)
                            printf("关键字为 %d 顶点不存在，查找失败！\n",u);
                        else
                            printf("查找顶点成功，关键字为 %d 的顶点在邻接表数组中关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 4:
                        printf("请输入需要重新赋值的顶点的关键字：");
                        scanf("%d",&u);
                        printf("请输入新赋值的顶点关键字和字符串：");
                        scanf("%d%s",&value.key,value.others);
                        j=PutVex(G,u,value);
                        if(j==OK)
                            printf("赋值成功！\n");
                        else if(j==ERROR)
                            printf("赋值失败，可能是待重新赋值的关键字不存在，或赋值后无向图中关键字重复！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 5:
                        printf("请输入需要获取第一邻接点的顶点的关键字：");
                        scanf("%d",&u);
                        j=FirstAdjVex(G,u);
                        if(j==OVERFLOW)
                            printf("获取失败，该顶点无邻接顶点！\n");
                        else if(j==INFEASIBLE)
                            printf("获取失败，无向图中无此顶点！\n");
                        else
                            printf("获取成功，关键字为 %d 的顶点的第一邻接顶点关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 6:
                        printf("请输入需要获取邻接点的顶点的关键字：");
                        scanf("%d",&u);
                        printf("请输入需要获取下一邻接点的顶点的关键字：");
                        scanf("%d",&w);
                        j=NextAdjVex(G,u,w);
                        if(j==ERROR)
                            printf("获取失败，w无下一邻接顶点！\n");
                        else if(j==INFEASIBLE)
                            printf("获取失败，v不在无向图中！\n");
                        else
                            printf("获取成功，顶点v的邻接顶点相对于w的下一邻接顶点的关键字和字符串为 %d %s ！\n",G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 7:
                        printf("请输入插入顶点的关键字和字符串：");
                        scanf("%d%s",&value.key,value.others);
                        j=InsertVex(G,value);
                        if(j==OK)
                            printf("插入顶点成功！\n");
                        else if(j==OVERFLOW)
                            printf("插入顶点失败，顶点集已满！\n");
                        else if(j==ERROR)
                            printf("插入顶点失败，新插入顶点的关键字与已有顶点关键字重复！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 8:
                        printf("请输入删除顶点的关键字：");
                        scanf("%d",&u);
                        j=DeleteVex(G,u);
                        if(j==OK)
                            printf("删除顶点成功！\n");
                        else
                            printf("删除顶点失败，无向图为空或无此顶点！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 9:
                        printf("请输入待插入弧的两个顶点：");
                        scanf("%d%d",&u,&w);
                        j=InsertArc(G,u,w);
                        if(j==OK)
                            printf("插入弧成功！\n");
                        else if(j==INFEASIBLE)
                            printf("插入弧失败，输入的弧顶点不存在于图中！\n");
                        else if(j==ERROR)
                            printf("插入弧失败，插入的弧已存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 10:
                        printf("请输入待删除弧的两个顶点：");
                        scanf("%d%d",&u,&w);
                        j=DeleteArc(G,u,w);
                        if(j==OK)
                            printf("删除弧成功！\n");
                        else if(j==INFEASIBLE)
                            printf("删除弧失败，输入的弧顶点不存在于图中！\n");
                        else if(j==ERROR)
                            printf("删除弧失败，待删除的弧不存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 11:
                        j=DFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n深度搜索无向图成功！\n");
                        else
                            printf("\n搜索图失败，图为空！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 12:
                        j=BFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n广度搜索无向图成功！\n");
                        else
                            printf("\n搜索图失败，图为空！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 13:
                        printf("请输入待操作文件路径和名称：");
                        scanf("%s",FileName);
                        j=SaveGraph(G,FileName);
                        if(j==OK)
                            printf("无向图存档成功！\n");
                        else if(j==ERROR)
                            printf("创建/打开文件失败！\n");
                        else
                            printf("无向图存档失败，无向图为空！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 14:
                        printf("请输入待操作文件路径和名称：");
                        scanf("%s",FileName);
                        j=LoadGraph(G,FileName);
                        if(j==OK)
                            printf("无向图读档成功！\n");
                        else if(j==ERROR)
                            printf("打开文件失败！\n");
                        else
                            printf("无向图读档失败，无向图已存在，读档会使原无向图中数据失去！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 15:
                        for(j=0;j<G.vexnum;j++)
                        {
                            ArcNode *p=G.vertices[j].firstarc;
                            printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
                            while (p)
                            {
                                printf(" %d",p->adjvex);
                                p=p->nextarc;
                            }
                            printf("\n");
                        }
                        getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 0:
                        break;
                }//end of switch
            }//end of while
        }//end of if
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}

//栈的函数
void iniStack(stack &S)
//该函数初始化栈S
{
    S.p = 0;
}
int isEmptyStack(stack &S)
//判断是不是空栈，是则返回1，不是则返回0
{
    if (S.p)
        return 0;
    else
        return 1;
}
int push(stack &S, ElemType e)
//该函数将元素进栈，成功则返回1，失败返回0
{
    if (S.p == MAX_VERTEX_NUM - 1)
        return OVERFLOW;
    else
    {
        S.elem[++S.p] = e;
    }
    return OK;
}
ElemType pop(stack &S)
//该函数将元素出栈，返回出栈的元素值
{
    if (S.p == 0)
        return ERROR;
    else
        return S.elem[S.p--];
}

//队列的函数
void iniQueue(QUEUE &Q)
//该函数实现初始化Q
{
    Q.front = 0;
    Q.length = 0;
}
int isEmptyQueue(QUEUE &Q)
//判断队列是否为空，若为空返回1，否则返回0
{
    if (Q.length)
        return 0;
    else
        return 1;
}
int enQueue(QUEUE &Q, ElemType e)
//将元素e入队Q。成功入栈返回1，否则返回0
{
    if (Q.length == MAX_VERTEX_NUM)
        return 0;
    Q.elem[(Q.front + Q.length++) % MAX_VERTEX_NUM] = e;
    return 1;
}
int deQueue(QUEUE &Q, ElemType &e)
//将Q队首元素出队，赋值给e。成功出队返回1，否则返回0
{
    if (Q.length == 0)
        return 0;
    e = Q.elem[(Q.front++) % MAX_VERTEX_NUM];
    Q.length--;
    return 1;
}

//菜单功能选择 1 创建无向图
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]) 
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR。如果有相同的关键字，返回ERROR。*/
{
    int i,j,flag[MAX_KEY]={0};
    ArcNode *tmp;
    if(G.vexnum)
        return INFEASIBLE;
    G.vexnum=G.arcnum=0;
    G.kind=UDG;     //初始化无向图
    if(V[0].key==-1)
        return ERROR;       //无向图为空
    for(i=0;V[i].key!=-1;i++)
    { //用flag数组标记存在的顶点
        if(flag[V[i].key])
        {
            G.vexnum=G.arcnum=0;
            return ERROR;   //重复输入结点关键字
        }
        flag[V[i].key]=1;
        G.vexnum++;
        if(G.vexnum>20)
        {//顶点数超出最大值
            G.vexnum=0;
            return ERROR;
        }   
    }
    for(i=0;V[i].key!=-1;i++)
    {   //为顶点赋值
        G.vertices[i].data.key=V[i].key;
        strcpy(G.vertices[i].data.others,V[i].others);
        G.vertices[i].firstarc=NULL;
    }
    for(i=0;VR[i][0]!=-1;i++)
    {   //创建邻接表
        if(!flag[VR[i][0]]||!flag[VR[i][1]])
        {   //输入的边的顶点不存在
            G.vexnum=G.arcnum=0;
            return ERROR;
        }   
        if(VR[i][0]==VR[i][1])
            continue;   //输入的边为自环
        for(j=0;j<G.vexnum;j++)
        {
            int f[MAX_VERTEX_NUM]={0};
            ArcNode *t=G.vertices[j].firstarc;           
            if(G.vertices[j].data.key==VR[i][0])    //输入边的顶点顺序可能有两种情况，但最终创建邻接表的结果是一样的
            {
                for(;t;t=t->nextarc)    //标记已经创建的边               
                    f[t->adjvex]=1;       
                int k=0;
                while (G.vertices[k].data.key!=VR[i][1])    //找到另一顶点的序号               
                    k++;          
                if(!f[k])
                {//此边未创建时用首插法创建边
                    tmp=G.vertices[j].firstarc;
                    G.vertices[j].firstarc=(ArcNode *)malloc(sizeof(ArcNode));
                    G.vertices[j].firstarc->adjvex=k;
                    G.vertices[j].firstarc->nextarc=tmp;
                    G.arcnum++; //边数只需要在顶点顺序的某一种情况下增加
                }
            }
            if(G.vertices[j].data.key==VR[i][1])
            {
                for(;t;t=t->nextarc)
                    f[t->adjvex]=1;
                int k=0;
                while (G.vertices[k].data.key!=VR[i][0])
                    k++;
                if(!f[VR[i][0]])
                {
                    tmp=G.vertices[j].firstarc;
                    G.vertices[j].firstarc=(ArcNode *)malloc(sizeof(ArcNode));
                    G.vertices[j].firstarc->adjvex=k;
                    G.vertices[j].firstarc->nextarc=tmp;
                }
            }
        }
    }
    return OK;
}

//菜单功能选择 2 销毁无向图
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    if(!G.vexnum)
        return INFEASIBLE;
    ArcNode *tmp1,*tmp2=NULL;
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        tmp1=G.vertices[i].firstarc;
        if(tmp1)    //对任一顶点，若没有边与它相连，则不需要进行删除边操作
            tmp2=G.vertices[i].firstarc->nextarc;
        for(;tmp1;)
        {//依次删除头顶点后的边
            //通过两个顶点指针的移动实现循环删除边顶点
            G.vertices[i].firstarc=tmp2;
            free(tmp1);
            tmp1=NULL;
            tmp1=tmp2;
            if(tmp2)
                tmp2=tmp2->nextarc;
        }
    }
    G.vexnum=G.arcnum=0;    //将顶点数和边数置为0
    return OK;
}

//菜单功能选择 3 查找顶点
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回INFEASIBLE
{
    int i,flag=0;
    for(i=0;i<G.vexnum;i++)
    {//遍历顶点数组，至查找到待查找顶点时标记并退出循环
        if(u==G.vertices[i].data.key)
        {
            flag=1;
            break;
        }   
    }
    if(flag)
        return i;
    else
        return INFEASIBLE;
}

//菜单功能选择 4 顶点赋值
status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；如果查找失败或关键字不唯一，返回ERROR
{
    int i,v[MAX_KEY]={0};
    for(i=0;i<G.vexnum;i++)
    {//标记已出现过的顶点关键字
        v[G.vertices[i].data.key]=1;
    }
    for(i=0;i<G.vexnum;i++)
    {//遍历顶点数组
        if(u==G.vertices[i].data.key)
        {//查找到待修改顶点
            if(value.key==u||!v[value.key])
            {//当新关键字不与现有关键字重复，或新关键字与待修改顶点关键字相同时，进行赋值操作
                G.vertices[i].data.key=value.key;
                strcpy(G.vertices[i].data.others,value.others);
                return OK;
            }
        }
    }
    return ERROR;
}

//菜单功能选择 5 获取第一邻接点
int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序。若顶点无邻接顶点，返回ERROR；若顶点不在图中，返回INFEASIBLE。
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {//遍历顶点数组，查找到与u关键字相同的顶点
        if(u==G.vertices[i].data.key&&G.vertices[i].firstarc)   //顶点有邻接顶点
            return G.vertices[i].firstarc->adjvex;
        else if(u==G.vertices[i].data.key)  //顶点无邻接顶点
            return OVERFLOW;
    }
    return INFEASIBLE;
}

//菜单功能选择 6 获取下一邻接点
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据v在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找邻接顶点失败返回ERROR，查找顶点失败返回INFEASIBLE
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(v==G.vertices[i].data.key)
        {
            ArcNode *tmp=G.vertices[i].firstarc;
            for(;tmp;tmp=tmp->nextarc)
                if(w==G.vertices[tmp->adjvex].data.key&&tmp->nextarc)
                    return tmp->nextarc->adjvex;
            return ERROR;  //查找邻接顶点失败
        }
    }
    return INFEASIBLE;  //查找顶点失败
}

//菜单功能选择 7 插入顶点
status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    int i,flag[MAX_KEY]={0};
    if(G.vexnum==MAX_VERTEX_NUM)
        return OVERFLOW;   //顶点集已满
    for(i=0;i<G.vexnum;i++)
    {//标记出现过的关键字
        flag[G.vertices[i].data.key]=1;
    }
    if(!flag[v.key])
    {//关键字不重复，则新增顶点，否则报错
        G.vertices[i].data.key=v.key;
        strcpy(G.vertices[i].data.others,v.others);
        G.vertices[i].firstarc=NULL;
        G.vexnum++;
        return OK;
    }
    else
        return ERROR;
}

//菜单功能选择 8 删除顶点
status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    int a=-1,flag[MAX_KEY]={0};
    for(int i=0;i<G.vexnum;i++)
        flag[G.vertices[i].data.key]=1;
    if(!flag[v]||!G.vexnum)
        return ERROR;//图中无顶点（空图）或无对应关键字的顶点时，返回ERROR
    else
    {
        for(int i=0;i<G.vexnum;i++)
        {
            if(v==G.vertices[i].data.key)
            {//查找到关键字对应的顶点时，将其邻接表中的弧全部删掉
                for(ArcNode *tmp1=G.vertices[i].firstarc;tmp1;)
                {
                    G.vertices[i].firstarc=tmp1->nextarc;
                    ArcNode *tmp2=tmp1;
                    tmp1=tmp1->nextarc;
                    free(tmp2);
                    tmp2=NULL;
                    G.arcnum--;
                }
                a=i;    //a用于记录待删除顶点的位序，便于后续修改邻接表
            }
            else
            {//不是关键字对应的顶点时，查找邻接表中与关键字顶点相关的弧并删除
                for(ArcNode *tmp1=G.vertices[i].firstarc;tmp1;tmp1=tmp1->nextarc)
                {//因无图头结点，关键字对应于第一邻接点或其他点时要分开讨论
                    //使用tmp1、tmp2两个顶点指针进行顶点删除操作
                    ArcNode *tmp2;
                    if(G.vertices[G.vertices[i].firstarc->adjvex].data.key==v)
                    {//关键字对应于第一邻接点
                        tmp2=G.vertices[i].firstarc;
                        G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
                        free(tmp2);
                        tmp2=NULL;
                        break;
                    }
                    else if(tmp1->nextarc&&G.vertices[tmp1->nextarc->adjvex].data.key==v)
                    {//关键字对应于除第一邻接点外的其他顶点
                        tmp2=tmp1->nextarc;
                        tmp1->nextarc=tmp2->nextarc;
                        free(tmp2);
                        tmp2=NULL;
                        break;
                    }
                }
            }
        }
        for(int i=0;i<G.vexnum;i++)
        {//在顶点数组中删除顶点，并修改其后位序的顶点在邻接表中的位序值
            if(v==G.vertices[i].data.key)
            {
                for(int j=i;j<G.vexnum-1;j++)
                    G.vertices[j]=G.vertices[j+1];
                for(ArcNode *t=G.vertices[i].firstarc;t;t=t->nextarc)
                {//在顶点数组中移位后要对补充到原删除顶点位置的顶点的邻接表进行修改
                    if(t->adjvex>a)
                        t->adjvex-=1;   //删除顶点其后位序的顶点在邻接表中位序减一
                }
                G.vexnum--;
            }
            else
                for(ArcNode *t=G.vertices[i].firstarc;t;t=t->nextarc)
                    if(t->adjvex>a)
                        t->adjvex-=1;
        }
        return OK;
    }
}

//菜单功能选择 9 插入弧
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    int i,a,b,flag[MAX_KEY]={0};
    for(i=0;i<G.vexnum;i++)
    {//标记图中所有顶点；用a、b记录待插入弧的两个顶点
        flag[G.vertices[i].data.key]=1;
        if(G.vertices[i].data.key==v)
            a=i;
        if(G.vertices[i].data.key==w)
            b=i;
    }
    if(a==b)    //待插入弧为自环时，不进行操作
        return OK;
    if(!flag[v]||!flag[w])  //待插入弧的任一顶点不在图中时，返回ERROR
        return INFEASIBLE;
    for(i=0;i<G.vexnum;i++)
    {//分别查找v、w对应的顶点，在其邻接表中首插法插入弧
        if(v==G.vertices[i].data.key)
        {
            ArcNode *tmp=G.vertices[i].firstarc;
            for(;tmp;tmp=tmp->nextarc)  //判断待插入的弧是否已经存在，存在则返回ERROR
                if(tmp->adjvex==b)
                    return ERROR;
            tmp=G.vertices[i].firstarc;
            G.vertices[i].firstarc=(ArcNode *)malloc(sizeof(ArcNode));          
            G.vertices[i].firstarc->adjvex=b;
            G.vertices[i].firstarc->nextarc=tmp;
        }
        if(w==G.vertices[i].data.key)
        {
            ArcNode *tmp=G.vertices[i].firstarc;
            for(;tmp;tmp=tmp->nextarc)
                if(tmp->adjvex==a)
                    return ERROR;
            tmp=G.vertices[i].firstarc;
            G.vertices[i].firstarc=(ArcNode *)malloc(sizeof(ArcNode));
            G.vertices[i].firstarc->adjvex=a;
            G.vertices[i].firstarc->nextarc=tmp;
        }
    }
    G.arcnum++;
    return OK;
}

//菜单功能选择 10 删除弧
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    int i,a,b,flag[MAX_KEY]={0};
    for(i=0;i<G.vexnum;i++)
    {//标记图中所有顶点；用a、b记录待删除弧的两个顶点
        flag[G.vertices[i].data.key]=1;
        if(v==G.vertices[i].data.key)
            a=i;
        if(w==G.vertices[i].data.key)
            b=i;
    }
    if(!flag[v]||!flag[w])  //待删除弧的任一顶点不在图中时，返回ERROR
        return INFEASIBLE;
    for(i=0;i<G.vexnum;i++)
    {
        if(v==G.vertices[i].data.key)
        {//分别查找v、w对应的顶点，在其邻接表中进行删除弧操作
            ArcNode *tmp1=G.vertices[i].firstarc;
            int pt=0;   //pt用于标记待删除弧是否存在，不存在则返回ERROR
            for(;tmp1;tmp1=tmp1->nextarc)
                if(tmp1->adjvex==b)
                {
                    pt=1;
                    break;
                }    
            if(pt)
            {//因无图头结点，关键字对应于第一邻接点或其他点时要分开讨论
                //使用tmp1、tmp2两个顶点指针进行弧删除操作
                if(G.vertices[i].firstarc->adjvex==b)
                {//关键字对应于第一邻接点
                    tmp1=G.vertices[i].firstarc->nextarc;
                    ArcNode *tmp2=G.vertices[i].firstarc;
                    G.vertices[i].firstarc=tmp1;
                    free(tmp2);
                    tmp2=NULL;
                }
                else
                {//关键字对应于除第一邻接点外的其他顶点
                    for(tmp1=G.vertices[i].firstarc;tmp1->nextarc->adjvex!=b;tmp1=tmp1->nextarc);               
                    ArcNode *tmp2=tmp1->nextarc;
                    tmp1->nextarc=tmp2->nextarc;
                    free(tmp2);
                    tmp2=NULL;
                }
            }
            else
                return ERROR;
        }
        if(w==G.vertices[i].data.key)
        {
            ArcNode *tmp1=G.vertices[i].firstarc;
            int pt=0;
            for(;tmp1;tmp1=tmp1->nextarc)
                if(tmp1->adjvex==a)
                {
                    pt=1;
                    break;
                }    
            if(pt)
            {
                if(G.vertices[i].firstarc->adjvex==a)
                {
                    tmp1=G.vertices[i].firstarc->nextarc;
                    ArcNode *tmp2=G.vertices[i].firstarc;
                    G.vertices[i].firstarc=tmp1;
                    free(tmp2);
                    tmp2=NULL;
                }
                else
                {
                    for(tmp1=G.vertices[i].firstarc;tmp1->nextarc->adjvex!=a;tmp1=tmp1->nextarc);               
                    ArcNode *tmp2=tmp1->nextarc;
                    tmp1->nextarc=tmp2->nextarc;
                    free(tmp2);
                    tmp2=NULL;
                }
            }
            else
                return ERROR;
        }
    }
    G.arcnum--;
    return OK;
}

//深搜的辅助函数，用于递归查找
void DFS(AdjList verx,int index,int visited[100],void (*visit)(VertexType))
{
    ArcNode *p=verx[index].firstarc;
    if(visited[index])
        return;
    visited[index]=1;
    visit(verx[index].data);
    while(p)
    {
        if(!visited[p->adjvex])
            DFS(verx,p->adjvex,visited,visit);
        p=p->nextarc;
    }
}
//菜单功能选择 11 深度优先搜索遍历
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    if(!G.vexnum)//空图
        return ERROR;
    int visited[MAX_VERTEX_NUM]={0};
    for(int i=0;i<G.vexnum;i++)
        if(!visited[i])
            DFS(G.vertices,i,visited,visit); 
    return OK;
}

//菜单功能选择 12 广度优先搜索遍历
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    if (G.vexnum==0) //空图
        return ERROR;
    QUEUE Q;
    int visited[G.vexnum]={0};  //数组标记各顶点是否被访问过
    iniQueue(Q);
    for(int i=0;i<G.vexnum;i++)
    {//广度优先遍历每一个连通子图
        if(!visited[i])
        {//如果当前顶点不在被遍历过的连通子图中
            visited[i]=1;
            visit(G.vertices[i].data);
            enQueue(Q,i);
            while(!isEmptyQueue(Q))
            {//队列非空时循环
                deQueue(Q,i);
                ArcNode *q=G.vertices[i].firstarc;
                for(;q!=NULL;q=q->nextarc)
                {//依次将当前顶点的所有未访问过的邻接点入队列，并标记为已访问
                    if(!visited[q->adjvex])
                    {
                        enQueue(Q,q->adjvex);
                        visited[q->adjvex]=1;
                        visit(G.vertices[q->adjvex].data);
                    }
                }
            }
        }
    }
    return OK;
}

//菜单功能选择 13 无向图存档
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp;
    if(!G.vexnum)
        return INFEASIBLE;
    if (!(fp = fopen(FileName, "wb")))
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    { //写入每一个顶点
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc)
        { //顺序写入该顶点的每一个邻接点的位置
            fprintf(fp, "%d ", p->adjvex);
        }
        fprintf(fp, "%d ", -1); //邻接点结尾处写上-1
    }
    fprintf(fp, "%d %s ", -1, "nil"); //顶点结尾处写上-1
    fclose(fp);
    return OK;
}

//菜单功能选择 14 无向图读档
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
//本函数调用栈的数据结构及其操作函数
{
    if (G.vexnum > 0)
        return  INFEASIBLE;
    FILE *fp;
    if (!(fp = fopen(FileName, "rb")))
        return ERROR;
    G.vexnum = G.arcnum = 0;
    KeyType key;          //存储从文件中读取顶点key值的临时变量
    int ConnectVerLocate; //存储读取的顶点邻接点的位置的临时变量
    char others[20];      //存储读取的顶点的data中others分量的临时变量
    stack S;              //定义栈
    iniStack(S);
    fscanf(fp, "%d ", &key);
    fscanf(fp, "%s ", others);
    for (int i = 0; key != -1 && G.vexnum < MAX_VERTEX_NUM; i++)
    { //创建顶点
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        fscanf(fp, "%d ", &ConnectVerLocate);
        for (; ConnectVerLocate != -1;)
        { //建立顶点的邻接表
            //通过入栈出栈把顺序倒置，确保读取后顶点邻接表顺序与原图相同
            push(S, ConnectVerLocate);
            fscanf(fp, "%d ", &ConnectVerLocate);
        }
        for (ArcNode *p; !isEmptyStack(S);)
        {                              //栈不为空时循环
            ConnectVerLocate = pop(S); //出栈
            //从邻接表头部插入邻接点结点
            p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = ConnectVerLocate;
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
            G.arcnum++; //图的边数自增
        }
        G.vexnum++;                        //图的顶点数自增
        fscanf(fp, "%d %s", &key, others); //读取下一顶点
    }
    G.arcnum/=2;
    fclose(fp);
    return OK;
}

//菜单功能选择 15 多无向图管理之增加无向图 
status AddGraph(LISTS &Lists,char ListName[])
// 在Lists中增加一个名称为ListName的无向图。
{
    if(Lists.length<Lists.listsize)
    {
    	int i,flag=0;
    	for(i=0;i<Lists.length;i++)
			if(!strcmp(Lists.elem[i].name,ListName))
			{
				flag=1;
				break;
			}				
		if(!flag)
		{
			strcpy(Lists.elem[Lists.length].name,ListName);
            VertexType V[30];   //由于图为空时相当于图不存在，增加图时即向图中输入元素
            KeyType VR[100][2];
            int i=0,j;
            printf("请输入图中所有顶点关键字和字符串，输入（-1，null）终止：\n");
            do {
                scanf("%d%s",&V[i].key,V[i].others);
            } while(V[i++].key!=-1);
            i=0;
            printf("请输入图中所有弧，输入（-1，-1）终止：\n");
            do {
                scanf("%d%d",&VR[i][0],&VR[i][1]);
            } while(VR[i++][0]!=-1);
			j=CreateGraph(Lists.elem[Lists.length].G,V,VR);
            if(j==ERROR)
                return ERROR;
			Lists.length++;
			return OK;
		}
	    else
			return INFEASIBLE;	
	}
	else
		return OVERFLOW;
} 

//菜单功能选择 16 多无向图管理之删除无向图 
status RemoveGraph(LISTS &Lists,char ListName[])
// 在Lists中删除一个名称为ListName的无向图。 
{
    int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
		if(!strcmp(Lists.elem[i].name,ListName))
		{
			flag=1;
			break;
		}	
	}
	if(flag)
	{
        DestroyGraph(Lists.elem[i].G);
        for(;i<Lists.length-1;i++)
			Lists.elem[i]=Lists.elem[i+1];
        if(i!=Lists.length-1)
            DestroyGraph(Lists.elem[Lists.length-1].G);
        Lists.elem[Lists.length-1].G.vexnum=Lists.elem[Lists.length-1].G.arcnum=0;
        Lists.elem[Lists.length-1].name[0]='\0';
		Lists.length--;
		return OK;
	}
	else
		return ERROR;
} 

//菜单功能选择 17 多无向图管理之查找无向图 
int LocateGraph(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的无向图，查找成功返回逻辑序号，否则返回ERROR。 
{
	int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
		if(!strcmp(Lists.elem[i].name,ListName))
		{
			flag=1;
			break;
		}
	}
	if(!flag||!Lists.length)
		return ERROR;
	else
		return i+1;
}

//辅助函数：访问图顶点
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

//辅助函数：进入二级菜单
void SecondaryTable(ALGraph &G,int op)
{
    int i,j;
    char Name[30]={'\0'},FileName[30]={'\0'};
    KeyType u,w;
    VertexType value;
    while(op){
        system("cls");
        printf("\n\n");
        printf("                Menu for Linear Table On Sequence Structure \n");
        printf("---------------------------------------------------------------------------------------\n");
        printf("    	  1. CreateGraph        7. InsertVex            13. SaveGraph\n");
        printf("    	  2. DestroyGraph       8. DeleteVex            14. LoadGraph\n");
        printf("    	  3. LocateVex          9. InsertArc            15. ShowGraph\n");
        printf("    	  4. PutVex             10. DeleteArc\n");
        printf("    	  5. FirstAdjVex        11. DFSTraverse\n");
        printf("    	  6. NextAdjVex         12. BFSTraverse\n");
        printf("    	  0. Exit\n");
        printf("---------------------------------------------------------------------------------------\n");
        printf("     请选择你的操作[0~15]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                i=0;
                VertexType V[30];
                KeyType VR[100][2];
                printf("请输入图中所有顶点关键字和字符串，输入（-1，null）终止：\n");
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                printf("请输入图中所有弧，输入（-1，-1）终止：\n");
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                j=CreateGraph(G,V,VR);
                if(j==OK)
                    printf("创建无向图成功！\n");
                else if(j==INFEASIBLE)
                    printf("无向图添加失败，该无向图已存在！\n");
                else if(j==ERROR)
                    printf("创建无向图失败，无向图数据输入错误！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 2:
                j=DestroyGraph(G);
                if(j==OK)
                    printf("销毁无向图成功！\n");
                else
                    printf("销毁无向图失败，无向图不存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 3:
                printf("请输入待查找顶点关键字：");
                scanf("%d",&u);
                j=LocateVex(G,u);
                if(j==INFEASIBLE)
                    printf("关键字为 %d 顶点不存在，查找失败！\n",u);
                else
                    printf("查找顶点成功，关键字为 %d 的顶点在邻接表数组中关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 4:
                printf("请输入需要重新赋值的顶点的关键字：");
                scanf("%d",&u);
                printf("请输入新赋值的顶点关键字和字符串：");
                scanf("%d%s",&value.key,value.others);
                j=PutVex(G,u,value);
                if(j==OK)
                    printf("赋值成功！\n");
                else if(j==ERROR)
                    printf("赋值失败，可能是待重新赋值的关键字不存在，或赋值后无向图中关键字重复！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 5:
                printf("请输入需要获取第一邻接点的顶点的关键字：");
                scanf("%d",&u);
                j=FirstAdjVex(G,u);
                if(j==OVERFLOW)
                    printf("获取失败，该顶点无邻接顶点！\n");
                else if(j==INFEASIBLE)
                    printf("获取失败，无向图中无此顶点！\n");
                else
                    printf("获取成功，关键字为 %d 的顶点的第一邻接顶点关键字和字符串为 %d %s ！\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 6:
                printf("请输入需要获取邻接点的顶点的关键字：");
                scanf("%d",&u);
                printf("请输入需要获取下一邻接点的顶点的关键字：");
                scanf("%d",&w);
                j=NextAdjVex(G,u,w);
                if(j==ERROR)
                    printf("获取失败，w无下一邻接顶点！\n");
                else if(j==INFEASIBLE)
                    printf("获取失败，v不在无向图中！\n");
                else
                    printf("获取成功，顶点v的邻接顶点相对于w的下一邻接顶点的位序为 %d %s ！\n",G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 7:
                printf("请输入插入顶点的关键字和字符串：");
                scanf("%d%s",&value.key,value.others);
                j=InsertVex(G,value);
                if(j==OK)
                    printf("插入顶点成功！\n");
                else if(j==OVERFLOW)
                    printf("插入顶点失败，顶点集已满！\n");
                else if(j==ERROR)
                    printf("插入顶点失败，新插入顶点的关键字与已有顶点关键字重复！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 8:
                printf("请输入删除顶点的关键字：");
                scanf("%d",&u);
                j=DeleteVex(G,u);
                if(j==OK)
                    printf("删除顶点成功！\n");
                else
                    printf("删除顶点失败，无向图为空或无此顶点！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 9:
                printf("请输入待插入弧的两个顶点：");
                scanf("%d%d",&u,&w);
                j=InsertArc(G,u,w);
                if(j==OK)
                    printf("插入弧成功！\n");
                else if(j==INFEASIBLE)
                    printf("插入弧失败，输入的弧顶点不存在于图中！\n");
                else if(j==ERROR)
                    printf("插入弧失败，插入的弧已存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 10:
                printf("请输入待删除弧的两个顶点：");
                scanf("%d%d",&u,&w);
                j=DeleteArc(G,u,w);
                if(j==OK)
                    printf("删除弧成功！\n");
                else if(j==INFEASIBLE)
                    printf("删除弧失败，输入的弧顶点不存在于图中！\n");
                else if(j==ERROR)
                    printf("删除弧失败，待删除的弧不存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 11:
                j=DFSTraverse(G,visit);
                if(j==OK)
                    printf("\n深度搜索无向图成功！\n");
                else
                    printf("\n搜索图失败，图为空！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 12:
                j=BFSTraverse(G,visit);
                if(j==OK)
                    printf("\n广度搜索无向图成功！\n");
                else
                    printf("\n搜索图失败，图为空！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 13:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=SaveGraph(G,FileName);
                if(j==OK)
                    printf("无向图存档成功！\n");
                else if(j==ERROR)
                    printf("创建/打开文件失败！\n");
                else
                    printf("无向图存档失败，无向图为空！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 14:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=LoadGraph(G,FileName);
                if(j==OK)
                    printf("无向图读档成功！\n");
                else if(j==ERROR)
                    printf("打开文件失败！\n");
                else
                    printf("无向图读档失败，无向图已存在，读档会使原无向图中数据失去！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 15:
                for(j=0;j<G.vexnum;j++)
                {
                    ArcNode *p=G.vertices[j].firstarc;
                    printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
                    while (p)
                    {
                        printf(" %d",p->adjvex);
                        p=p->nextarc;
                    }
                    printf("\n");
                }
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
}