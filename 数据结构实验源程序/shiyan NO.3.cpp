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
    KeyType key;//���������ؼ��ֶ���
    char others[20];//����������ַ���
} TElemType; //������������Ͷ���
typedef struct BiTNode
{ 
    TElemType data;
    struct BiTNode *lchild, *rchild;//������������������
} BiTNode, *BiTree;//����������Ķ���
typedef struct
{
    int pos;
    TElemType data;
} DEF;//���ڴ���û������λ�á��ؼ��֡��ַ�����Ϣ
typedef struct
{ //�������Ĺ������
    struct
    {
        char name[30]; //����������
        BiTree T;//�����������ָ��
    } elem[10];   //��Ŷ������ļ���
    int length;   //���������ϵĳ���
    int listsize; //���������Ϸ���Ŀռ�
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
    } //��ʼ��
    while (op != -3)
    {
        system("cls");
        printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("         -1.MainTable/MultiBiTree     -2.SingleBiTree\n");
        printf("    	 -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     ��ѡ�����ڵĲ˵��㼶��\n");
        printf("     -1�����˵�ʵ�ֶ����������-2����ʱ������������������\n");
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
                        printf("\t������%d��δ����            \t������%d��δ����", i + 1, i + 6);
                    else if (Lists.elem[i].T == NULL && Lists.elem[i + 5].T != NULL)
                        printf("\t������%d��δ����            \t������%d��%s", i + 1, i + 6, Lists.elem[i + 5].name);
                    else if (Lists.elem[i].T != NULL && Lists.elem[i + 5].T == NULL)
                        printf("\t������%d��%s                \t������%d��δ����", i + 1, Lists.elem[i].name, i + 6);
                    else
                        printf("\t������%d��%s                \t������%d��%s", i + 1, Lists.elem[i].name, i + 6, Lists.elem[i + 5].name);
                    printf("\n");
                }
                printf("\n     ��ѡ����Ĳ���[0��17~20]:");
                scanf("%d", &op);
                switch (op)
                {
                    case 17:
                        printf("���������ӵĶ��������ƣ�");
                        scanf("%s",Name);
                        j=AddList(Lists,Name);
                        if(j==OK)
                            printf("��������ӳɹ���\n");
                        else if(j==ERROR)
                            printf("���������ʧ�ܣ��ö������Ѵ��ڣ�\n");
                        else if(j==OVERFLOW)
                            printf("���������ʧ�ܣ�����������������\n");
                        else if(j==INFEASIBLE)
                            printf("����������ʧ�ܣ��������Ľ��ؼ��ִ����ظ���\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 18:
                        printf("�������ɾ���Ķ��������ƣ�");
						scanf("%s",Name);
						j=RemoveList(Lists,Name);
						if(j==OK)
							printf("������ɾ���ɹ���\n");
						else if(j==ERROR)
							printf("������ɾ��ʧ�ܣ��������޴˶�������\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
                    case 19:
                        printf("����������ҵĶ��������ƣ�");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							printf("�ö�����λ�ڼ����е� %d λ��\n",j);
						else
							printf("����������ʧ�ܣ��������޴˶�������\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
                    case 20:
                        printf("������������Ķ��������ƣ�");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].T,op);
						else
						{
							getchar();
							printf("�������������ڼ����У����ܽ��뵥������������\n");
                            printf("---���������---\n");
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
                printf("     ��ѡ����Ĳ���[0~16]:");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        i=0;
                        printf("������������������λ����š��ؼ��֡����ݣ�\n");
                        do {
                            scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
                        } while (definition[i++].pos);
                        j=CreateBiTree(T,definition);
                        if(j==OK)
                            printf("�����������ɹ���\n");
                        else if(j==ERROR)
                            printf("����������ʧ�ܣ��������Ľ��ؼ��ִ����ظ���\n");
                        else if(j==INFEASIBLE)
                            printf("����������ʧ�ܣ��������Ѵ��ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyBiTree(T);
                        if(j==OK)
                            printf("���ٶ������ɹ���\n");
                        else
                            printf("�����������ڣ����ܽ������ٲ�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 3:
                        j=ClearBiTree(T);
                        if(j==OK)
                            printf("��ն������ɹ���\n");
                        else
                            printf("�����������ڣ����ܽ�����ղ�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 4:
                        j=BiTreeEmpty(T);
                        if(j==TRUE)
                            printf("������Ϊ�գ�\n");
                        else if(j==FALSE)
                            printf("��������Ϊ�գ�\n"); 
                        else
                            printf("�����������ڣ����ܽ����пղ�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 5:
                        j=BiTreeDepth(T);
                        if(j>=0)
                            printf("���������Ϊ %d ��\n",j);
                        else
                            printf("�����������ڣ����ܽ�������Ȳ�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 6:
                        printf("����������ҽ��ؼ��֣�");
                        scanf("%d",&e);
                        tmp=LocateNode(T,e);
                        if(tmp)
                            printf("��ȡ���ɹ������ؼ��ֺ��ַ���Ϊ %d %s ��\n",tmp->data.key,tmp->data.others);
                        else 
                            printf("�ؼ���Ϊ %d ��㲻���ڣ�����ʧ�ܣ�\n",e);
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 7:
                        printf("��������Ҫ���¸�ֵ�Ľ��Ĺؼ��֣�");
                        scanf("%d",&e);
                        printf("�������¸�ֵ�Ľ��ؼ��ֺ��ַ�����");
                        scanf("%d%s",&value.key,value.others);
                        j=Assign(T,e,value);
                        if(j==OK)
                            printf("��ֵ�ɹ���\n");
                        else if(j==ERROR)
                            printf("��ֵʧ�ܣ������Ǵ����¸�ֵ�Ĺؼ��ֲ����ڣ���ֵ��������йؼ����ظ���\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 8:
                        printf("��������Ҫ�������ֵܽ��Ľ��Ĺؼ��֣�");
                        scanf("%d",&e);
                        tmp=GetSibling(T,e);
                        if(tmp)
                            printf("�ֵܽ��ؼ��ֺ��ַ���Ϊ %d %s ��\n",tmp->data.key,tmp->data.others);
                        else
                            printf("�ý����ֵܽ�㲻���ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 9:
                        printf("��������������ؼ��֣�");
                        scanf("%d",&e);
                        printf("����ѡ��\n0��������������Ϊ��Ӧ�����������1��������������Ϊ��Ӧ�����������-1����Ϊ��������\n");
                        printf("��������뷽ʽѡ��");
                        scanf("%d",&i);
                        printf("�������������ؼ��ֺ��ַ�����");
                        scanf("%d%s",&value.key,value.others);
                        j=InsertNode(T,e,i,value);
                        if(j==OK)
                            printf("������ɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("������ʧ�ܣ��ö��������޹ؼ��� %d ��\n",e);
                        else if(j==ERROR)
                            printf("������ʧ�ܣ���������ؼ�����ԭ�������йؼ����ظ���\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 10:
                        printf("�������ɾ�����ؼ��֣�");
                        scanf("%d",&e);
                        j=DeleteNode(T,e);
                        if(j==OK)
                            printf("ɾ�����ɹ���\n");
                        else
                            printf("ɾ�����ʧ�ܣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 11:
                        j=PreOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n��������������ɹ���\n");
                        else
                            printf("\n�����������ڣ����ܽ��б�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 12:
                        j=InOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n��������������ɹ���\n");
                        else
                            printf("\n�����������ڣ����ܽ��б�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 13:
                        j=PostOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n��������������ɹ���\n");
                        else
                            printf("\n�����������ڣ����ܽ��б�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 14:
                        j=LevelOrderTraverse(T,visit);
                        if(j==OK)
                            printf("\n��������������ɹ���\n");
                        else
                            printf("\n�����������ڣ����ܽ��б�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 15:
                        printf("������������ļ�·�������ƣ�");
                        scanf("%s",FileName);
                        j=SaveBiTree(T,FileName);
                        if(j==OK)
                            printf("�������浵�ɹ���\n");
                        else
                            printf("�������浵ʧ�ܣ������������ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 16:
                        printf("������������ļ�·�������ƣ�");
                        scanf("%s",FileName);
                        j=LoadBiTree(T,FileName);
                        if(j==OK)
                            printf("�����������ɹ���\n");
                        else
                            printf("����������ʧ�ܣ��������Ѵ��ڣ�������ʹԭ��������Ԫ��ʧȥ��\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 0:
                        break;
                }//end of switch
            }//end of while
        }//end of if
    } //end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
} //end of main

//�˵�����ѡ�� 1 ����������
status CreateBiTree(BiTree &T, DEF definition[])
//���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK���������ͬ�Ĺؼ��֣�����ERROR��
{
    if(!T)
    {
        int i=0,j;
        BiTNode *p[Maxlength]={0};
        int v[Maxlength]={0};
        while (definition[i].data.key!=0)
        {//��Ƕ���������Ƿ���ֹ�������ͬ�ؼ���ʱ˵�������������
            if(!v[definition[i].data.key])
                v[definition[i].data.key]=1;
            else
                return ERROR;
            i++;
        }
        i=0;
        while (j=definition[i].pos)
        {//���ݶ��������λ�����뼰���ϵ����������
            p[j]=(BiTNode *)malloc(sizeof(BiTNode));
            p[j]->data=definition[i].data;
            p[j]->lchild=NULL;
            p[j]->rchild=NULL;
            if (j!=1)   //������λ���Ǹ��׽��λ�õ�2�����������Ǹ��׽��λ�õ�2��+1
                if (j%2)
                    p[j/2]->rchild=p[j];  
                else
                    p[j/2]->lchild=p[j];
            i++;
        }
        T=p[1]; //����㸳��T
        return OK;
    }
    else
        return INFEASIBLE;  //�������Ѵ��ڣ����ܴ���
}

//�˵�����ѡ�� 2 ���ٶ�����
status DestroyBiTree(BiTree &T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�,���ͷ�ͷ��㡣
{
    if(!T)  //������������
        return INFEASIBLE;
    else
    {//�ݹ�������ٶ���������
        if(T->lchild)
            DestroyBiTree(T->lchild);
        if(T->rchild)
            DestroyBiTree(T->rchild);
        free(T);
        T = NULL;
        return OK;
    }
}

//�˵�����ѡ�� 3 ��ն�����
status ClearBiTree(BiTree &T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ䡣
{
    if (!T)  //������������
        return INFEASIBLE;
    else
    {//�ݹ������ն���������
        if(T->lchild)
            ClearBiTree(T->lchild);
        if(T->rchild)
            ClearBiTree(T->rchild);
        free(T);
        T = NULL;
        return OK;
    }
}

//�˵�����ѡ�� 4 �������п�
status BiTreeEmpty(BiTree T)
//�ж϶������Ƿ�Ϊ���������򷵻�TRUE�����򷵻�FALSE��
{
    if (!T)
        return TRUE;
    else
        return FALSE;
}

//�˵�����ѡ�� 5 ����������
int BiTreeDepth(BiTree T)
//�ݹ��������T��Ȳ��������ֵ��
{
    if (!T)  //������������
        return 0;
    int lh = BiTreeDepth(T->lchild);    //�ݹ����
    int rh = BiTreeDepth(T->rchild);
    return 1 + (lh > rh ? lh : rh);
}

//�˵�����ѡ�� 6 ���ҽ��
BiTNode *LocateNode(BiTree T, KeyType e)
//e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ������e���ҷ��������Ľ�㣬���ظý��ָ�룬���޹ؼ���Ϊe�Ľ�㣬����NULL��
{
    if (!T)  //����������㲻����
        return NULL;
    else
    {
        if (T->data.key == e)
            return T;   //�����ɹ������ص�ǰ���
        BiTree p = NULL;
        if (T->lchild)
            p = LocateNode(T->lchild, e);
        if (T->rchild && !p)    //ע��!p�������жϣ�������������ʧ�ܲ�����������
            p = LocateNode(T->rchild, e);
        return p;
    }
}

//�˵�����ѡ�� 7 ��㸳ֵ
status Assign(BiTree T, KeyType e, TElemType value)
//e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ�����ҽ��ؼ��ֵ���e�Ľ�㣬�����ֵ�޸ĳ�value������OK��Ҫ����ؼ��ֱ���Ψһ�ԣ����������ʧ�ܣ�����ERROR��
{
    int v[Maxlength] = {0};
    if (!T)  //����������㲻����
        return ERROR;
    else
    {
        BiTree data[Maxlength], p;
        int top = 0;
        if (T)
        {//����������Զ��������ؼ��ֽ��б�ǣ����жϸ�ֵʱ�Ƿ���ֹؼ����ظ�
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
        {//����������Զ����������������Ը�ֵ
            data[top++] = T;
            while (top)
            {
                p = data[--top];
                if ((p->data.key == e && !v[value.key]) || (p->data.key == e && p->data.key == value.key))
                {//���ҵ������¸�ֵ������¹ؼ���δ����ǻ���ԭ�ؼ�����ͬ��ִ�и�ֵ����
                    p->data.key = value.key;
                    strcpy(p->data.others, value.others);
                    return OK;
                }
                else if (v[value.key] && p->data.key == e && p->data.key != value.key)//���ҵ������¸�ֵ��㵫�¹ؼ�����������������ؼ����ظ�
                    return ERROR;
                if (p->rchild)
                    data[top++] = p->rchild;
                if (p->lchild)
                    data[top++] = p->lchild;
            }
        }  
    }
}

//�˵�����ѡ�� 8 ��ȡ�ֵܽ��
BiTNode *GetSibling(BiTree T, KeyType e)
//e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ�����ҽ��ؼ��ֵ���e�Ľ����ֵܽ�㣬�������ֵܽ��ָ�롣�������ʧ�ܣ�����NULL��
{
    if (T->lchild != NULL && T->rchild != NULL)
    {//���������Բ�Ϊ�գ���������Ϊ�����ҽ��ʱ����������������������Ϊ�����ҽ��ʱ��������������
        if (T->lchild->data.key == e)
            return T->rchild;
        else if (T->rchild->data.key == e)
            return T->lchild;
    }
    BiTree p = NULL;
    if (T->lchild != NULL)  //�ݹ����
        p = GetSibling(T->lchild, e);
    if (T->rchild != NULL && !p)
        p = GetSibling(T->rchild, e);
    return p;
}

//�˵�����ѡ�� 9 ������
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
/*e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��LRΪ0��1��c�Ǵ������㣻����LRΪ0����1��������c��T�У���Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬���e��ԭ������������������Ϊ���c��������������OK���������ʧ�ܣ�����ERROR��
�ر�أ���LRΪ-1ʱ����Ϊ�������룬ԭ�������Ϊc����������*/
{
    BiTree p, t;
    BiTree data[Maxlength];
    int top = 0;
    p = LocateNode(T, c.key);
    if (p)  //���ò��Һ����жϴ�������ؼ����Ƿ������йؼ����ظ����ظ��򱨴�
        return INFEASIBLE;
    p = LocateNode(T, e);   //���ؼ��ֲ��ظ������ò��Һ����ҵ����������
    if (p)  //�����������ҳɹ�
    {
        if (!LR)
        {//���
            t = p->lchild;
            p->lchild = (BiTree)malloc(sizeof(BiTNode));
            p->lchild->data.key = c.key;
            strcpy(p->lchild->data.others, c.others);
            p->lchild->lchild = NULL;
            p->lchild->rchild = t;
        }
        else if (LR == 1)
        {//�Ҳ�
            t = p->rchild;
            p->rchild = (BiTree)malloc(sizeof(BiTNode)); 
            p->rchild->data.key = c.key;
            strcpy(p->rchild->data.others, c.others);
            p->rchild->lchild = NULL;
            p->rchild->rchild = t;
        }
        else if (LR == -1)
        {//ͷ��
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

//�˵�����ѡ�� 10 ɾ�����
status DeleteNode(BiTree &T, KeyType e)
/*e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��ɾ��T�йؼ���Ϊe�Ľ�㣻ͬʱ������ؼ���Ϊe�Ľ���Ϊ0��ɾ�����ɣ���ؼ���Ϊe�Ľ���Ϊ1���ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�ã���ؼ���Ϊe�Ľ���Ϊ2����e�����Ӵ��汻ɾ����eλ�ã�e����������Ϊe�������������ҽ�����������
�ɹ�ɾ�����󷵻�OK�����򷵻�ERROR��*/
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

//�˵�����ѡ�� 11 �������������
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T����ÿ��������һ���ҽ�һ�Ρ�
{
    BiTree data[Maxlength], p;
    int top = 0;
    if (T)
    {//����ջ�Զ��������зǵݹ��������
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

//�˵�����ѡ�� 12 �������������
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T����ÿ��������һ���ҽ�һ�Ρ�
{
    BiTree data[Maxlength], p;
    int top = 0;
    if (T)
    {//����ջ�Զ��������зǵݹ��������
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

//�˵�����ѡ�� 13 �������������
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T����ÿ��������һ���ҽ�һ�Ρ�
{
    BiTree data[Maxlength], p, pre;
    int top = 0, flag;
    if (T)
    {//����ջ�Զ��������зǵݹ�������
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

//�˵�����ѡ�� 14 �������������
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//�������������T����ÿ��������һ���ҽ�һ�Ρ�
{
    BiTree data[Maxlength];
    int in = 0, out = 0;
    data[in++] = T;
    while (in > out)
    {//����ջ�Զ��������зǵݹ�������
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

//�˵�����ѡ�� 15 �������浵
status SaveBiTree(BiTree T, char FileName[])
//���������Ľ������д�뵽�ļ�FileName�С�
{
    if(T)
    {//�ļ���ȡʱ���ö�����λ�ã����ڱ�Ǻʹ���
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
    else    //������������
        return INFEASIBLE;
}

//�˵�����ѡ�� 16 ����������
status LoadBiTree(BiTree &T, char FileName[])
//�����ļ�FileName�Ľ�����ݣ�������������
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
    else    //�������Ѵ��ڣ�������ʹ������������ʧȥ
        return INFEASIBLE;
}

//�˵�����ѡ�� 17 �����������֮���Ӷ�����
status AddList(LISTS &Lists, char ListName[])
// ��Lists������һ������ΪListName�Ķ�������
{
    if (Lists.length < Lists.listsize)
    {
        int i, j, flag = 0;
        DEF definition[Maxlength];
        for (i = 0; i < Lists.length; i++)
            if (!strcmp(Lists.elem[i].name, ListName))
            {//����strcmp�����Ƚ϶��������������뵱ǰ��������ƣ�����ͬ����
                flag = 1;
                break;
            }
        if (!flag)  //Ϊ����ǣ���ǰ���������ڶ����������У���������
        {//�������ĸ����Ϊ��ʱ�൱���������ڣ�������ʱ������������Ԫ�أ�����λ�ñ�ǹ��������
            i=0;
            strcpy(Lists.elem[Lists.length].name, ListName);
            printf("������������������λ����š��ؼ��֡����ݣ�\n");
            do {
                scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
            } while (definition[i++].pos);
            j=CreateBiTree(Lists.elem[Lists.length].T,definition);  //���ô�������������
            if(j==OK)
            {
                Lists.length++;
                return OK;
            }    
            else  //����������ʧ��
                return INFEASIBLE;
        }
        else   //����ǣ���ǰ���Ѵ��ڣ���������
            return ERROR;
    }
    else    //����������������������Ӷ�����
        return OVERFLOW;
}

//�˵�����ѡ�� 18 �����������֮ɾ��������
status RemoveList(LISTS &Lists, char ListName[])
// ��Lists��ɾ��һ������ΪListName�Ķ�������
{
    int i, flag = 0;
    for (i = 0; i < Lists.length; i++)
    {
        if (!strcmp(Lists.elem[i].name, ListName))
        {//�Զ��������ƽ��бȽϲ��ң����ҳɹ�ʱ��ǲ��˳�ѭ��
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        DestroyBiTree(Lists.elem[i].T);   //�������ٶ������������ٵ�ǰ������
        for (; i < Lists.length - 1; i++)	//�����ҵ��Ķ�������Ķ�����˳��ǰ��һλ
            Lists.elem[i] = Lists.elem[i + 1];
        if(i!=Lists.length-1)   //����ĩλ������δ�����٣��������ٶ�������������
            DestroyBiTree(Lists.elem[Lists.length-1].T);
        Lists.elem[Lists.length - 1].name[0] = '\0';	//��ԭ����ĩλ�Ķ�����������Ϊ�գ��ͷ�������
        Lists.elem[Lists.length - 1].T = NULL;
        free(Lists.elem[Lists.length - 1].T);
        Lists.length--;
        return OK;
    }
    else
        return ERROR;
}

//�˵�����ѡ�� 19 �����������֮���Ҷ�����
int LocateList(LISTS Lists, char ListName[])
// ��Lists�в���һ������ΪListName�Ķ����������ҳɹ������߼���ţ����򷵻�ERROR��
{
    int i, flag = 0;
    for (i = 0; i < Lists.length; i++)
    {
        if (!strcmp(Lists.elem[i].name, ListName))
        {//�Զ��������ƽ��бȽϲ��ң����ҳɹ�ʱ��ǲ��˳�ѭ��
            flag = 1;
            break;
        }
    }
    if (!flag || !Lists.length)	//����ʧ�ܻ���������ϳ���Ϊ0
        return ERROR;
    else    //���ҳɹ������߼�λ��
        return i + 1;
}

//�������������Ҹ��׽��
BiTNode *LocateTree(BiTree T, BiTree t)
//��������t�����丸�׽�㣬���ҳɹ��򷵻ظ��׽��ָ�룬���򷵻�NULL��
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

//�������������ʽ��
void visit(BiTree T)
//�Ե�ǰ���ִ���ض�������
{
    printf(" %d,%s", T->data.key, T->data.others);
}

//������������������˵�
void SecondaryTable(BiTree &T,int op)
// ����ѡ�Ķ�����������еĴ��������������ݽ�������˵��У�ʵ�ֶԵ��������Ļ�������
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
        printf("     ��ѡ����Ĳ���[0~16]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                i=0;
                printf("������������������λ����š��ؼ��֡����ݣ�\n");
                do {
                    scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
                } while (definition[i++].pos);
                j=CreateBiTree(T,definition);
                if(j==OK)
                    printf("�����������ɹ���\n");
                else if(j==ERROR)
                    printf("����������ʧ�ܣ��������Ľ��ؼ��ִ����ظ���\n");
                else if(j==INFEASIBLE)
                    printf("����������ʧ�ܣ��������Ѵ��ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 2:
                j=DestroyBiTree(T);
                if(j==OK)
                    printf("���ٶ������ɹ���\n");
                else
                    printf("�����������ڣ����ܽ������ٲ�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 3:
                j=ClearBiTree(T);
                if(j==OK)
                    printf("��ն������ɹ���\n");
                else
                    printf("�����������ڣ����ܽ�����ղ�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 4:
                j=BiTreeEmpty(T);
                if(j==TRUE)
                    printf("������Ϊ�գ�\n");
                else if(j==FALSE)
                    printf("��������Ϊ�գ�\n"); 
                else
                    printf("�����������ڣ����ܽ����пղ�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 5:
                j=BiTreeDepth(T);
                if(j>=0)
                    printf("���������Ϊ %d ��\n",j);
                else
                    printf("�����������ڣ����ܽ�������Ȳ�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 6:
                printf("����������ҽ��ؼ��֣�");
                scanf("%d",&e);
                tmp=LocateNode(T,e);
                if(tmp)
                    printf("��ȡ���ɹ������ؼ��ֺ��ַ���Ϊ %d %s ��\n",tmp->data.key,tmp->data.others);
                else 
                    printf("�ؼ���Ϊ %d ��㲻���ڣ�����ʧ�ܣ�\n",e);
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 7:
                printf("��������Ҫ���¸�ֵ�Ľ��Ĺؼ��֣�");
                scanf("%d",&e);
                printf("�������¸�ֵ�Ľ��ؼ��ֺ��ַ�����");
                scanf("%d%s",&value.key,value.others);
                j=Assign(T,e,value);
                if(j==OK)
                    printf("��ֵ�ɹ���\n");
                else if(j==ERROR)
                    printf("��ֵʧ�ܣ������Ǵ����¸�ֵ�Ĺؼ��ֲ����ڣ���ֵ��������йؼ����ظ���\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 8:
                printf("��������Ҫ�������ֵܽ��Ľ��Ĺؼ��֣�");
                scanf("%d",&e);
                tmp=GetSibling(T,e);
                if(tmp)
                    printf("�ֵܽ��ؼ��ֺ��ַ���Ϊ %d %s ��\n",tmp->data.key,tmp->data.others);
                else
                    printf("�ý����ֵܽ�㲻���ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 9:
                printf("��������������ؼ��֣�");
                scanf("%d",&e);
                printf("����ѡ��\n0��������������Ϊ��Ӧ�����������1��������������Ϊ��Ӧ�����������-1����Ϊ��������\n");
                printf("��������뷽ʽѡ��");
                scanf("%d",&i);
                printf("�������������ؼ��ֺ��ַ�����");
                scanf("%d%s",&value.key,value.others);
                j=InsertNode(T,e,i,value);
                if(j==OK)
                    printf("������ɹ���\n");
                else
                    printf("������ʧ�ܣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 10:
                printf("�������ɾ�����ؼ��֣�");
                scanf("%d",&e);
                j=DeleteNode(T,e);
                if(j==OK)
                    printf("ɾ�����ɹ���\n");
                else
                    printf("ɾ�����ʧ�ܣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 11:
                j=PreOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n��������������ɹ���\n");
                else
                    printf("\n�����������ڣ����ܽ��б�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 12:
                j=InOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n��������������ɹ���\n");
                else
                    printf("\n�����������ڣ����ܽ��б�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 13:
                j=PostOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n��������������ɹ���\n");
                else
                    printf("\n�����������ڣ����ܽ��б�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 14:
                j=LevelOrderTraverse(T,visit);
                if(j==OK)
                    printf("\n��������������ɹ���\n");
                else
                    printf("\n�����������ڣ����ܽ��б�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 15:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=SaveBiTree(T,FileName);
                if(j==OK)
                    printf("�������浵�ɹ���\n");
                else
                    printf("�������浵ʧ�ܣ������������ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 16:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=LoadBiTree(T,FileName);
                if(j==OK)
                    printf("�����������ɹ���\n");
                else
                    printf("����������ʧ�ܣ��������Ѵ��ڣ�������ʹԭ��������Ԫ��ʧȥ��\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
}

