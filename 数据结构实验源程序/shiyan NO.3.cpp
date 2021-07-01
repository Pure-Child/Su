/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define Maxlength 100

typedef int status;
typedef int KeyType;
typedef struct
{
    KeyType key;//二叉树结点关键字定义
    char others[20];//二叉树结点字符串
} TElemType; //二叉树结点类型定义
typedef struct BiTNode
{ 
    TElemType data;
    struct BiTNode *lchild, *rchild;//二叉树左右子树定义
} BiTNode, *BiTree;//二叉链表结点的定义
typedef struct
{
    int pos;
    TElemType data;
} DEF;//用于存放用户输入的位置、关键字、字符串信息
typedef struct
{ //二叉树的管理表定义
    struct
    {
        char name[30]; //二叉树名称
        BiTree T;//二叉树根结点指针
    } elem[10];   //存放二叉树的集合
    int length;   //二叉树集合的长度
    int listsize; //二叉树集合分配的空间
} LISTS;

BiTNode *LocateTree(BiTree T, BiTree t);
void visit(BiTree T);
void SecondaryTable(BiTree &T,int op);
status CreateBiTree(BiTree &T, DEF definition[]);
status DestroyBiTree(BiTree &T);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode *LocateNode(BiTree T, KeyType e);
status Assign(BiTree T, KeyType e, TElemType value);
BiTNode *GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree &T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);

int main()
{
    BiTree T = NULL, tmp = NULL;
    LISTS Lists;
    TElemType value;
    DEF definition[Maxlength];
    KeyType e;
    int op = 1;
    int i, j;
    char Name[30] = {'\0'}, FileName[30] = {'\0'};
    value.key=0;
    value.others[0]='\0';
    Lists.length = 0;
    Lists.listsize = 10;
    for (j = 0; j < 10; j++)
    {
        Lists.elem[j].T = NULL;
    } //初始化
    while (op != -3)
    {
        system("cls");
        printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("         -1.MainTable/MultiBiTree     -2.SingleBiTree\n");
        printf("    	 -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     请选择所在的菜单层级：\n");
        printf("     -1：主菜单实现多二叉树管理，-2：临时单二叉树基本操作。\n");
        scanf("%d", &op);
        if (op == -1)
        {
            while (op)
            {
                system("cls");
                printf("\n\n");
                printf("            Menu for Linear Table On Sequence Structure \n");
                printf("---------------------------------------------------------------------\n");
                printf("       17.AddBiTree        18.RemoveBiTree      19.LocateBiTree\n");
                printf("       20.SecondaryTable\n");
                printf("   	   0. Exit\n");
                printf("---------------------------------------------------------------------\n");
                for (i = 0; i < 5; i++)
                {
                    if (Lists.elem[i].T == NULL && Lists.elem[i + 5].T == NULL )
                        printf("\t二叉树%d：未创建            \t二叉树%d：未创建", i + 1, i + 6);
                    else if (Lists.elem[i].T == NULL && Lists.elem[i + 5].T != NULL)
                        printf("\t二叉树%d：未创建            \t二叉树%d：%s", i + 1, i + 6, Lists.elem[i + 5].name);
                    else if (Lists.elem[i].T != NULL && Lists.elem[i + 5].T == NULL)
                        printf("\t二叉树%d：%s                \t二叉树%d：未创建", i + 1, Lists.elem[i].name, i + 6);
                    else
                        printf("\t二叉树%d：%s                \t二叉树%d：%s", i + 1, Lists.elem[i].name, i + 6, Lists.elem[i + 5].name);
                    printf("\n");
                }
                printf("\n     请选择你的操作[0或17~20]:");
                scanf("%d", &op);
                switch (op)
                {
                    case 17:
                        printf("请输入待添加的二叉树名称：");
                        scanf("%s",Name);
                        j=AddList(Lists,Name);
                        if(j==OK)
                            printf("二叉树添加成功！\n");
                        else if(j==ERROR)
                            printf("二叉树添加失败，该二叉树已存在！\n");
                        else if(j==OVERFLOW)
                            printf("二叉树添加失败，二叉树集合已满！\n");
                        else if(j==INFEASIBLE)
                            printf("创建二叉树失败，二叉树的结点关键字存在重复！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 18:
                        printf("请输入待删除的二叉树名称：");
						scanf("%s",Name);
						j=RemoveList(Lists,Name);
						if(j==OK)
							printf("二叉树删除成功！\n");
						else if(j==ERROR)
							printf("二叉树删除失败，集合中无此二叉树！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 19:
                        printf("请输入待查找的二叉树名称：");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							printf("该二叉树位于集合中第 %d 位！\n",j);
						else
							printf("二叉树查找失败，集合中无此二叉树！\n");
						getchar();
						printf("---任意键继续---\n");
						getchar();
						break;
                    case 20:
                        printf("请输入待操作的二叉树名称：");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].T,op);
						else
						{
							getchar();
							printf("二叉树不存在于集合中，不能进入单二叉树操作！\n");
                            printf("---任意键继续---\n");
							getchar();
							break;
						}
						break;
					case 0:
						break;
                } //end of switch
            } //end of while
        } //end of if
        if(op==-2)
        {
            while(op){
                system("cls");
                printf("\n\n");
                printf("                      Menu for Linear Table On Sequence Structure \n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("    	  1. CreateBiTree       7. Assign                13. PostOrderTraverse\n");
                printf("    	  2. DestroyBiTree      8. GetSibling            14. LevelOrderTraverse\n");
                printf("    	  3. ClearBiTree        9. InsertNode            15. SaveBiTree\n");
                printf("    	  4. BiTreeEmpty        10. DeleteNode           16. LoadBiTree\n");
                printf("    	  5. BiTreeDepth        11. PreOrderTraverse\n");
                printf("    	  6. LocateNode         12. InOrderTraverse\n");
                printf("    	  0. Exit\n");
                printf("---------------------------------------------------------------------------------------\n");
                printf("     请选择你的操作[0~16]:");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        i=0;
                        printf("请依次输入二叉树结点位置序号、关键字、内容：\n");
                        do {
                            scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
                        } while (definition[i++].pos);
                        j=CreateBiTree(T,definition);
                        if(j==OK)
                            printf("创建二叉树成功！\n");
                        else if(j==ERROR)
                            printf("创建二叉树失败，二叉树的结点关键字存在重复！\n");
                        else if(j==INFEASIBLE)
                            printf("创建二叉树失败，二叉树已存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyBiTree(T);
                        if(j==OK)
                            printf("销毁二叉树成功！\n");
                        else
                            printf("二叉树不存在，不能进行销毁操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 3:
                        j=ClearBiTree(T);
                        if(j==OK)
                            printf("清空二叉树成功！\n");
                        else
                            printf("二叉树不存在，不能进行清空操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 4:
                        j=BiTreeEmpty(T);
                        if(j==TRUE)
                            printf("二叉树为空！\n");
                        else if(j==FALSE)
                            printf("二叉树不为空！\n"); 
                        else
                            printf("二叉树不存在，不能进行判空操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 5:
                        j=BiTreeDepth(T);
                        if(j>=0)
                            printf("二叉树深度为 %d ！\n",j);
                        else
                            printf("二叉树不存在，不能进行求深度操作！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 6:
                        printf("请输入待查找结点关键字：");
                        scanf("%d",&e);
                        tmp=LocateNode(T,e);
                        if(tmp)
                            printf("获取结点成功，结点关键字和字符串为 %d %s ！\n",tmp->data.key,tmp->data.others);
                        else 
                            printf("关键字为 %d 结点不存在，查找失败！\n",e);
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 7:
                        printf("请输入需要重新赋值的结点的关键字：");
                        scanf("%d",&e);
                        printf("请输入新赋值的结点关键字和字符串：");
                        scanf("%d%s",&value.key,value.others);
                        j=Assign(T,e,value);
                        if(j==OK)
                            printf("赋值成功！\n");
                        else if(j==ERROR)
                            printf("赋值失败，可能是待重新赋值的关键字不存在，或赋值后二叉树中关键字重复！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 8:
                        printf("请输入需要查找其兄弟结点的结点的关键字：");
                        scanf("%d",&e);
                        tmp=GetSibling(T,e);
                        if(tmp)
                            printf("兄弟结点关键字和字符串为 %d %s ！\n",tmp->data.key,tmp->data.others);
                        else
                            printf("该结点的兄弟结点不存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 9:
                        printf("请输入待操作结点关键字：");
                        scanf("%d",&e);
                        printf("插入选择：\n0：将待插入结点作为对应结点左子树；1：将待插入结点作为对应结点右子树；-1：作为根结点插入\n");
                        printf("请输入插入方式选择：");
                        scanf("%d",&i);
                        printf("请输入待插入结点关键字和字符串：");
                        scanf("%d%s",&value.key,value.others);
                        j=InsertNode(T,e,i,value);
                        if(j==OK)
                            printf("插入结点成功！\n");
                        else if(j==INFEASIBLE)
                            printf("插入结点失败，该二叉树中无关键字 %d ！\n",e);
                        else if(j==ERROR)
                            printf("插入结点失败，待插入结点关键字与原二叉树中关键字重复！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 10:
                        printf("请输入待删除结点关键字：");
                        scanf("%d",&e);
                        j=DeleteNode(T,e);
                        if(j==OK)
                            printf("删除结点成功！\n");
                        else
                            printf("删除结点失败！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 11:
                        j=PreOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n先序遍历二叉树成功！\n");
                        else
                            printf("\n二叉树不存在，不能进行遍历！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 12:
                        j=InOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n中序遍历二叉树成功！\n");
                        else
                            printf("\n二叉树不存在，不能进行遍历！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 13:
                        j=PostOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n后序遍历二叉树成功！\n");
                        else
                            printf("\n二叉树不存在，不能进行遍历！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 14:
                        j=LevelOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n按层遍历二叉树成功！\n");
                        else
                            printf("\n二叉树不存在，不能进行遍历！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 15:
                        printf("请输入待操作文件路径和名称：");
                        scanf("%s",FileName);
                        j=SaveBiTree(T,FileName);
                        if(j==OK)
                            printf("二叉树存档成功！\n");
                        else
                            printf("二叉树存档失败，二叉树不存在！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 16:
                        printf("请输入待操作文件路径和名称：");
                        scanf("%s",FileName);
                        j=LoadBiTree(T,FileName);
                        if(j==OK)
                            printf("二叉树读档成功！\n");
                        else
                            printf("二叉树读档失败，二叉树已存在，读档会使原二叉树中元素失去！\n");
                        getchar();
                        printf("---任意键继续---\n");
                        getchar();
                        break;
                    case 0:
                        break;
                }//end of switch
            }//end of while
        }//end of if
    } //end of while
    printf("欢迎下次再使用本系统！\n");
} //end of main

//菜单功能选择 1 创建二叉树
status CreateBiTree(BiTree &T, DEF definition[])
//根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，如果有相同的关键字，返回ERROR。
{
    if(!T)
    {
        int i=0,j;
        BiTNode *p[Maxlength]={0};
        int v[Maxlength]={0};
        while (definition[i].data.key!=0)
        {//标记二叉树结点是否出现过，有相同关键字时说明数据输入错误
            if(!v[definition[i].data.key])
                v[definition[i].data.key]=1;
            else
                return ERROR;
            i++;
        }
        i=0;
        while (j=definition[i].pos)
        {//根据二叉树结点位置输入及其关系创建二叉树
            p[j]=(BiTNode *)malloc(sizeof(BiTNode));
            p[j]->data=definition[i].data;
            p[j]->lchild=NULL;
            p[j]->rchild=NULL;
            if (j!=1)   //左子树位置是父亲结点位置的2倍，右子树是父亲结点位置的2倍+1
                if (j%2)
                    p[j/2]->rchild=p[j];  
                else
                    p[j/2]->lchild=p[j];
            i++;
        }
        T=p[1]; //根结点赋给T
        return OK;
    }
    else
        return INFEASIBLE;  //二叉树已存在，不能创建
}

//菜单功能选择 2 销毁二叉树
status DestroyBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间,并释放头结点。
{
    if(!T)  //二叉树不存在
        return INFEASIBLE;
    else
    {//递归调用销毁二叉树函数
        if(T->lchild)
            DestroyBiTree(T->lchild);
        if(T->rchild)
            DestroyBiTree(T->rchild);
        free(T);
        T = NULL;
        return OK;
    }
}

//菜单功能选择 3 清空二叉树
status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间。
{
    if (!T)  //二叉树不存在
        return INFEASIBLE;
    else
    {//递归调用清空二叉树函数
        if(T->lchild)
            ClearBiTree(T->lchild);
        if(T->rchild)
            ClearBiTree(T->rchild);
        free(T);
        T = NULL;
        return OK;
    }
}

//菜单功能选择 4 二叉树判空
status BiTreeEmpty(BiTree T)
//判断二叉树是否为空树，是则返回TRUE，否则返回FALSE。
{
    if (!T)
        return TRUE;
    else
        return FALSE;
}

//菜单功能选择 5 求二叉树深度
int BiTreeDepth(BiTree T)
//递归求二叉树T深度并返回深度值。
{
    if (!T)  //二叉树不存在
        return 0;
    int lh = BiTreeDepth(T->lchild);    //递归调用
    int rh = BiTreeDepth(T->rchild);
    return 1 + (lh > rh ? lh : rh);
}

//菜单功能选择 6 查找结点
BiTNode *LocateNode(BiTree T, KeyType e)
//e是和T中结点关键字类型相同的给定值；根据e查找符合条件的结点，返回该结点指针，如无关键字为e的结点，返回NULL。
{
    if (!T)  //二叉树根结点不存在
        return NULL;
    else
    {
        if (T->data.key == e)
            return T;   //搜索成功，返回当前结点
        BiTree p = NULL;
        if (T->lchild)
            p = LocateNode(T->lchild, e);
        if (T->rchild && !p)    //注意!p条件的判断，即左子树搜索失败才搜索右子树
            p = LocateNode(T->rchild, e);
        return p;
    }
}

//菜单功能选择 7 结点赋值
status Assign(BiTree T, KeyType e, TElemType value)
//e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结点，将结点值修改成value，返回OK（要求结点关键字保持唯一性）。如果查找失败，返回ERROR。
{
    int v[Maxlength] = {0};
    if (!T)  //二叉树根结点不存在
        return ERROR;
    else
    {
        BiTree data[Maxlength], p;
        int top = 0;
        if (T)
        {//先序遍历，对二叉树结点关键字进行标记，以判断赋值时是否出现关键字重复
            data[top++] = T;
            while (top)
            {
                p = data[--top];
                if(!v[p->data.key])
                    v[p->data.key]=1;
                if (p->rchild)
                    data[top++] = p->rchild;
                if (p->lchild)
                    data[top++] = p->lchild;
            }
        }
        if (T)
        {//先序遍历，对二叉树结点进行搜索以赋值
            data[top++] = T;
            while (top)
            {
                p = data[--top];
                if ((p->data.key == e && !v[value.key]) || (p->data.key == e && p->data.key == value.key))
                {//查找到待重新赋值结点且新关键字未被标记或与原关键字相同，执行赋值操作
                    p->data.key = value.key;
                    strcpy(p->data.others, value.others);
                    return OK;
                }
                else if (v[value.key] && p->data.key == e && p->data.key != value.key)//查找到待重新赋值结点但新关键字与二叉树中其他关键字重复
                    return ERROR;
                if (p->rchild)
                    data[top++] = p->rchild;
                if (p->lchild)
                    data[top++] = p->lchild;
            }
        }  
    }
}

//菜单功能选择 8 获取兄弟结点
BiTNode *GetSibling(BiTree T, KeyType e)
//e是和T中结点关键字类型相同的给定值；查找结点关键字等于e的结点的兄弟结点，返回其兄弟结点指针。如果查找失败，返回NULL。
{
    if (T->lchild != NULL && T->rchild != NULL)
    {//左右子树皆不为空，当左子树为待查找结点时，返回右子树；当右子树为待查找结点时，返回左子树；
        if (T->lchild->data.key == e)
            return T->rchild;
        else if (T->rchild->data.key == e)
            return T->lchild;
    }
    BiTree p = NULL;
    if (T->lchild != NULL)  //递归查找
        p = GetSibling(T->lchild, e);
    if (T->rchild != NULL && !p)
        p = GetSibling(T->rchild, e);
    return p;
}

//菜单功能选择 9 插入结点
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
/*e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；根据LR为0或者1，插入结点c到T中，作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树，返回OK。如果插入失败，返回ERROR。
特别地，当LR为-1时，作为根结点插入，原根结点作为c的右子树。*/
{
    BiTree p, t;
    BiTree data[Maxlength];
    int top = 0;
    p = LocateNode(T, c.key);
    if (p)  //调用查找函数判断待插入结点关键字是否与已有关键字重复，重复则报错
        return INFEASIBLE;
    p = LocateNode(T, e);   //若关键字不重复，调用查找函数找到待操作结点
    if (p)  //待操作结点查找成功
    {
        if (!LR)
        {//左插
            t = p->lchild;
            p->lchild = (BiTree)malloc(sizeof(BiTNode));
            p->lchild->data.key = c.key;
            strcpy(p->lchild->data.others, c.others);
            p->lchild->lchild = NULL;
            p->lchild->rchild = t;
        }
        else if (LR == 1)
        {//右插
            t = p->rchild;
            p->rchild = (BiTree)malloc(sizeof(BiTNode)); 
            p->rchild->data.key = c.key;
            strcpy(p->rchild->data.others, c.others);
            p->rchild->lchild = NULL;
            p->rchild->rchild = t;
        }
        else if (LR == -1)
        {//头插
            t = (BiTree)malloc(sizeof(BiTNode));
            t->data.key = c.key;
            strcpy(t->data.others, c.others);
            t->lchild = NULL;
            t->rchild = T;
            T = t;
        }
        return OK;
    }
    else
        return INFEASIBLE;
}

//菜单功能选择 10 删除结点
status DeleteNode(BiTree &T, KeyType e)
/*e是和T中结点关键字类型相同的给定值。删除T中关键字为e的结点；同时，如果关键字为e的结点度为0，删除即可；如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；如关键字为e的结点度为2，用e的左孩子代替被删除的e位置，e的右子树作为e的左子树中最右结点的右子树。
成功删除结点后返回OK，否则返回ERROR。*/
{
    BiTree p, pre, tmp;
    p = LocateNode(T, e);
    if (!p)
        return ERROR;
    else
    {
        if (p == T)
            pre = NULL;
        else
            pre = LocateTree(T, p);
        if (!p->lchild && !p->rchild)
        {
            if (!pre)
                ;
            else if (pre->lchild == p)
                pre->lchild = NULL;
            else if (pre->rchild == p)
                pre->rchild = NULL;
        }
        else if (p->lchild && p->rchild)
        {
            tmp = p->lchild;
            while (tmp->rchild)
            {
                tmp = tmp->rchild;
            }
            tmp->rchild = (BiTree)malloc(sizeof(BiTNode));
            tmp->rchild = p->rchild;
            if (!pre)
            {
                pre = p->lchild;
                T = pre;
            }
            else if (pre->lchild == p)
                pre->lchild = p->lchild;
            else if (pre->rchild == p)
                pre->rchild = p->lchild;
        }
        else if (p->lchild)
        {
            if (!pre)
            {
                pre = p->lchild;
                T = pre;
            }
            else if (pre->lchild == p)
                pre->lchild = p->lchild;
            else if (pre->rchild == p)
                pre->rchild = p->lchild;
        }
        else if (p->rchild)
        {
            if (!pre)
            {
                pre = p->rchild;
                T = pre;
            }
            else if (pre->lchild == p)
                pre->lchild = p->rchild;
            else if (pre->rchild == p)
                pre->rchild = p->rchild;
        }
        free(p);
        return OK;
    }
}

//菜单功能选择 11 先序遍历二叉树
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//先序遍历二叉树T，对每个结点访问一次且仅一次。
{
    BiTree data[Maxlength], p;
    int top = 0;
    if (T)
    {//利用栈对二叉树进行非递归先序遍历
        data[top++] = T;
        while (top)
        {
            p = data[--top];
            visit(p);
            if (p->rchild)
                data[top++] = p->rchild;
            if (p->lchild)
                data[top++] = p->lchild;
        }
        return OK;
    }
    else
        return INFEASIBLE;
}

//菜单功能选择 12 中序遍历二叉树
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//中序遍历二叉树T，对每个结点访问一次且仅一次。
{
    BiTree data[Maxlength], p;
    int top = 0;
    if (T)
    {//利用栈对二叉树进行非递归中序遍历
        p = T;
        do
        {
            while (p)
            {
                if (top == Maxlength)
                    exit(OVERFLOW);
                data[top++] = p;
                p = p->lchild;
            }
            if (top)
            {
                p = data[--top];
                visit(p);
                p = p->rchild;
            }
        } while (top || p);
        return OK;
    }
    else
        return INFEASIBLE;
}

//菜单功能选择 13 后序遍历二叉树
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//后序遍历二叉树T，对每个结点访问一次且仅一次。
{
    BiTree data[Maxlength], p, pre;
    int top = 0, flag;
    if (T)
    {//利用栈对二叉树进行非递归后序遍历
        p = T;
        do
        {
            while (p)
            {
                if (top == Maxlength)
                    exit(OVERFLOW);
                data[top++] = p;
                p = p->lchild;
            }
            pre = NULL;
            flag = 1;
            while (top && flag)
            {
                p = data[top - 1];
                if (p->rchild == pre)
                {
                    visit(p);
                    top--;
                    pre = p;
                }
                else
                {
                    p = p->rchild;
                    flag = 0;
                }
            }
        } while (top);
        return OK;
    }
    else
        return INFEASIBLE;
}

//菜单功能选择 14 层序遍历二叉树
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//按层遍历二叉树T，对每个结点访问一次且仅一次。
{
    BiTree data[Maxlength];
    int in = 0, out = 0;
    data[in++] = T;
    while (in > out)
    {//利用栈对二叉树进行非递归层序遍历
        if (data[out])
        {
            visit(data[out]);
            data[in++] = data[out]->lchild;
            data[in++] = data[out]->rchild;
        }
        out++;
    }
    return OK;
}

//菜单功能选择 15 二叉树存档
status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中。
{
    if(T)
    {//文件存取时利用二叉树位置，便于标记和创建
        FILE *fp;
        BiTree node[Maxlength + 1] = {0};
        node[1] = T;
        int i = 1;
        int depth = BiTreeDepth(T);
        if ((fp = fopen(FileName, "wb")) != NULL)
        {
            while (i < pow(2,depth))
            {
                if (node[i] != NULL)
                {
                    fprintf(fp, "%d %d %s ", i, node[i]->data.key, node[i]->data.others);
                    if (node[i]->lchild != NULL)
                    {
                        node[2 * i] = node[i]->lchild;
                    }
                    if (node[i]->rchild != NULL)
                    {
                        node[2 * i + 1] = node[i]->rchild;
                    }
                }
                i++;
            }
            fclose(fp);
            return OK;
        }
        else
            return ERROR;
    }
    else    //二叉树不存在
        return INFEASIBLE;
}

//菜单功能选择 16 二叉树读档
status LoadBiTree(BiTree &T, char FileName[])
//读入文件FileName的结点数据，创建二叉树。
{
    if(!T)
    {
        BiTree node[Maxlength];
        for (int i = 0; i < Maxlength; ++i)
            node[i] = NULL;
        FILE *fp;
        fp = fopen(FileName, "rb");
        int a, b;
        char string[20];
        while (fscanf(fp, "%d %d %s ", &a, &b, string) != EOF)
        {
            node[a] = (BiTree)malloc(sizeof(BiTNode));
            node[a]->data.key = b;
            strcpy(node[a]->data.others, string);
            node[a]->rchild = node[a]->lchild = NULL;
        }
        for (int i = 2; i < Maxlength; ++i)
        {
            if (node[i / 2] != NULL)
            {
                if (i % 2 == 1)
                    node[i / 2]->rchild = node[i];
                else
                    node[i / 2]->lchild = node[i];
            }
        }
        T = node[1];
        fclose(fp);
        return OK;
    }
    else    //二叉树已存在，读档会使二叉树中数据失去
        return INFEASIBLE;
}

//菜单功能选择 17 多二叉树管理之增加二叉树
status AddList(LISTS &Lists, char ListName[])
// 在Lists中增加一个名称为ListName的二叉树。
{
    if (Lists.length < Lists.listsize)
    {
        int i, j, flag = 0;
        DEF definition[Maxlength];
        for (i = 0; i < Lists.length; i++)
            if (!strcmp(Lists.elem[i].name, ListName))
            {//利用strcmp函数比较二叉树集合中树与当前输入的名称，若相同则标记
                flag = 1;
                break;
            }
        if (!flag)  //为被标记，当前树不存在于二叉树集合中，可以增加
        {//由于树的根结点为空时相当于树不存在，增加树时即向树中输入元素，利用位置标记构造二叉树
            i=0;
            strcpy(Lists.elem[Lists.length].name, ListName);
            printf("请依次输入二叉树结点位置序号、关键字、内容：\n");
            do {
                scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
            } while (definition[i++].pos);
            j=CreateBiTree(Lists.elem[Lists.length].T,definition);  //调用创建二叉树函数
            if(j==OK)
            {
                Lists.length++;
                return OK;
            }    
            else  //创建二叉树失败
                return INFEASIBLE;
        }
        else   //被标记，当前树已存在，不能增加
            return ERROR;
    }
    else    //二叉树集合已满，不能添加二叉树
        return OVERFLOW;
}

//菜单功能选择 18 多二叉树管理之删除二叉树
status RemoveList(LISTS &Lists, char ListName[])
// 在Lists中删除一个名称为ListName的二叉树。
{
    int i, flag = 0;
    for (i = 0; i < Lists.length; i++)
    {
        if (!strcmp(Lists.elem[i].name, ListName))
        {//对二叉树名称进行比较查找，查找成功时标记并退出循环
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        DestroyBiTree(Lists.elem[i].T);   //调用销毁二叉树函数销毁当前二叉树
        for (; i < Lists.length - 1; i++)	//将查找到的二叉树后的二叉树顺序前移一位
            Lists.elem[i] = Lists.elem[i + 1];
        if(i!=Lists.length-1)   //若最末位二叉树未被销毁，调用销毁二叉树函数销毁
            DestroyBiTree(Lists.elem[Lists.length-1].T);
        Lists.elem[Lists.length - 1].name[0] = '\0';	//将原本最末位的二叉树名称置为空，释放其根结点
        Lists.elem[Lists.length - 1].T = NULL;
        free(Lists.elem[Lists.length - 1].T);
        Lists.length--;
        return OK;
    }
    else
        return ERROR;
}

//菜单功能选择 19 多二叉树管理之查找二叉树
int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的二叉树，查找成功返回逻辑序号，否则返回ERROR。
{
    int i, flag = 0;
    for (i = 0; i < Lists.length; i++)
    {
        if (!strcmp(Lists.elem[i].name, ListName))
        {//对二叉树名称进行比较查找，查找成功时标记并退出循环
            flag = 1;
            break;
        }
    }
    if (!flag || !Lists.length)	//查找失败或二叉树集合长度为0
        return ERROR;
    else    //查找成功返回逻辑位置
        return i + 1;
}

//辅助函数：查找父亲结点
BiTNode *LocateTree(BiTree T, BiTree t)
//根据子树t查找其父亲结点，查找成功则返回父亲结点指针，否则返回NULL。
{
    if (!T)
        return NULL;
    else
    {
        if (T->lchild == t || T->rchild == t)
            return T;
        BiTree p = NULL;
        if (T->lchild)
            p = LocateTree(T->lchild, t);
        if (T->rchild && !p)
            p = LocateTree(T->rchild, t);
        return p;
    }
}

//辅助函数：访问结点
void visit(BiTree T)
//对当前结点执行特定操作。
{
    printf(" %d,%s", T->data.key, T->data.others);
}

//辅助函数：进入二级菜单
void SecondaryTable(BiTree &T,int op)
// 将所选的多二叉树集合中的待操作二叉树传递进入二级菜单中，实现对单二叉树的基本操作
{
    BiTree tmp;
    TElemType value;
    DEF definition[Maxlength];
    KeyType e;
    int i, j;
    char FileName[30]={'\0'};
    while(op){
        system("cls");
        printf("\n\n");
        printf("                      Menu for Linear Table On Sequence Structure \n");
        printf("---------------------------------------------------------------------------------------\n");
        printf("    	  1. CreateBiTree       7. Assign                13. PostOrderTraverse\n");
        printf("    	  2. DestroyBiTree      8. GetSibling            14. LevelOrderTraverse\n");
        printf("    	  3. ClearBiTree        9. InsertNode            15. SaveBiTree\n");
        printf("    	  4. BiTreeEmpty        10. DeleteNode           16. LoadBiTree\n");
        printf("    	  5. BiTreeDepth        11. PreOrderTraverse\n");
        printf("    	  6. LocateNode         12. InOrderTraverse\n");
        printf("    	  0. Exit\n");
        printf("---------------------------------------------------------------------------------------\n");
        printf("     请选择你的操作[0~16]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                i=0;
                printf("请依次输入二叉树结点位置序号、关键字、内容：\n");
                do {
                    scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
                } while (definition[i++].pos);
                j=CreateBiTree(T,definition);
                if(j==OK)
                    printf("创建二叉树成功！\n");
                else if(j==ERROR)
                    printf("创建二叉树失败，二叉树的结点关键字存在重复！\n");
                else if(j==INFEASIBLE)
                    printf("创建二叉树失败，二叉树已存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 2:
                j=DestroyBiTree(T);
                if(j==OK)
                    printf("销毁二叉树成功！\n");
                else
                    printf("二叉树不存在，不能进行销毁操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 3:
                j=ClearBiTree(T);
                if(j==OK)
                    printf("清空二叉树成功！\n");
                else
                    printf("二叉树不存在，不能进行清空操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 4:
                j=BiTreeEmpty(T);
                if(j==TRUE)
                    printf("二叉树为空！\n");
                else if(j==FALSE)
                    printf("二叉树不为空！\n"); 
                else
                    printf("二叉树不存在，不能进行判空操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 5:
                j=BiTreeDepth(T);
                if(j>=0)
                    printf("二叉树深度为 %d ！\n",j);
                else
                    printf("二叉树不存在，不能进行求深度操作！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 6:
                printf("请输入待查找结点关键字：");
                scanf("%d",&e);
                tmp=LocateNode(T,e);
                if(tmp)
                    printf("获取结点成功，结点关键字和字符串为 %d %s ！\n",tmp->data.key,tmp->data.others);
                else 
                    printf("关键字为 %d 结点不存在，查找失败！\n",e);
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 7:
                printf("请输入需要重新赋值的结点的关键字：");
                scanf("%d",&e);
                printf("请输入新赋值的结点关键字和字符串：");
                scanf("%d%s",&value.key,value.others);
                j=Assign(T,e,value);
                if(j==OK)
                    printf("赋值成功！\n");
                else if(j==ERROR)
                    printf("赋值失败，可能是待重新赋值的关键字不存在，或赋值后二叉树中关键字重复！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 8:
                printf("请输入需要查找其兄弟结点的结点的关键字：");
                scanf("%d",&e);
                tmp=GetSibling(T,e);
                if(tmp)
                    printf("兄弟结点关键字和字符串为 %d %s ！\n",tmp->data.key,tmp->data.others);
                else
                    printf("该结点的兄弟结点不存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 9:
                printf("请输入待操作结点关键字：");
                scanf("%d",&e);
                printf("插入选择：\n0：将待插入结点作为对应结点左子树；1：将待插入结点作为对应结点右子树；-1：作为根结点插入\n");
                printf("请输入插入方式选择：");
                scanf("%d",&i);
                printf("请输入待插入结点关键字和字符串：");
                scanf("%d%s",&value.key,value.others);
                j=InsertNode(T,e,i,value);
                if(j==OK)
                    printf("插入结点成功！\n");
                else
                    printf("插入结点失败！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 10:
                printf("请输入待删除结点关键字：");
                scanf("%d",&e);
                j=DeleteNode(T,e);
                if(j==OK)
                    printf("删除结点成功！\n");
                else
                    printf("删除结点失败！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 11:
                j=PreOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n先序遍历二叉树成功！\n");
                else
                    printf("\n二叉树不存在，不能进行遍历！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 12:
                j=InOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n中序遍历二叉树成功！\n");
                else
                    printf("\n二叉树不存在，不能进行遍历！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 13:
                j=PostOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n后序遍历二叉树成功！\n");
                else
                    printf("\n二叉树不存在，不能进行遍历！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 14:
                j=LevelOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n按层遍历二叉树成功！\n");
                else
                    printf("\n二叉树不存在，不能进行遍历！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 15:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=SaveBiTree(T,FileName);
                if(j==OK)
                    printf("二叉树存档成功！\n");
                else
                    printf("二叉树存档失败，二叉树不存在！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 16:
                printf("请输入待操作文件路径和名称：");
                scanf("%s",FileName);
                j=LoadBiTree(T,FileName);
                if(j==OK)
                    printf("二叉树读档成功！\n");
                else
                    printf("二叉树读档失败，二叉树已存在，读档会使原二叉树中元素失去！\n");
                getchar();
                printf("---任意键继续---\n");
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
}

