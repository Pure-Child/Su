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
#define OVERFLOW -2 //Ԥ����ĳ��� 

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

typedef struct LNode{   //��������ʽ�ṹ�����Ķ���
    ElemType data;      //����������Ԫ�ش��
    struct LNode *next; //��������һ���ָ��
}LNode,*LinkList;
typedef struct{  //���Ա�Ĺ������
    struct { char name[30]; //���Ա����� 
     		LinkList L;	//���Ա�ͷָ��
    } elem[10]; //������Ա�ļ��� 
    int length; //���Ա��ϵĳ��� 
    int listsize; //���Ա��Ϸ���Ŀռ� 
}LISTS;

void SecondaryTable(LinkList &L,int op);
status InitInput(LinkList &L); //���Ա��������� 
status InitList(LinkList &L); //���Ա��ʼ�� 
status DestroyList(LinkList &L); //���Ա����� 
status ClearList(LinkList &L); //���Ա���� 
status ListEmpty(LinkList L); //���Ա��п� 
int ListLength(LinkList L); //�����Ա�� 
status GetElem(LinkList L,int i,ElemType &e); //��ȡԪ�� 
status LocateElem(LinkList L,ElemType e); //����Ԫ�� 
status PriorElem(LinkList L,ElemType e,ElemType &pre); //��ȡǰ��Ԫ�� 
status NextElem(LinkList L,ElemType e,ElemType &next); //��ȡ���Ԫ�� 
status ListInsert(LinkList &L,int i,ElemType e); //����Ԫ�� 
status ListDelete(LinkList &L,int i,ElemType &e); //ɾ��Ԫ�� 
status ListTraverse(LinkList L); //�������Ա� 
status SaveList(LinkList L,char FileName[]); //���Ա�浵 
status LoadList(LinkList &L,char FileName[]); //���Ա���� 
status AddList(LISTS &Lists,char ListName[]); //���ӿ����Ա� 
status RemoveList(LISTS &Lists,char ListName[]); //�Ƴ����Ա�
int LocateList(LISTS Lists,char ListName[]); //�������Ա� 

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
	}//��ʼ�� 
    while (op!=-3){
        system("cls");	printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("          -1.MainTable/MultiList     -2.SingleList\n");
        printf("    	  -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     ��ѡ�����ڵĲ˵��㼶��\n");
        printf("     -1�����˵�ʵ�ֶ����Ա����-2����ʱ�����Ա����������\n");
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
                        printf("\t���Ա�%d��δ����            \t���Ա�%d��δ����",i+1,i+6);
                    else if(Lists.elem[i].L==NULL&&Lists.elem[i+5].L!=NULL)
                        printf("\t���Ա�%d��δ����            \t���Ա�%d��%s",i+1,i+6,Lists.elem[i+5].name);
                    else if(Lists.elem[i].L!=NULL&&Lists.elem[i+5].L==NULL)
                        printf("\t���Ա�%d��%s                \t���Ա�%d��δ����",i+1,Lists.elem[i].name,i+6);
                    else
                        printf("\t���Ա�%d��%s                \t���Ա�%d��%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
                    printf("\n");
                }
                printf("\n     ��ѡ����Ĳ���[0��15~18]:");
				scanf("%d",&op);
				switch(op){
					case 15:
						printf("���������ӵ����Ա����ƣ�");
						scanf("%s",Name);
						j=AddList(Lists,Name);
						if(j==OK)
						{
							printf("���Ա���ӳɹ���\n");
							i=LocateList(Lists,Name);
							InitInput(Lists.elem[i-1].L);
						}
						else if(j==ERROR)
							printf("���Ա����ʧ�ܣ������Ա��Ѵ��ڣ�\n");
                        else if(j==OVERFLOW)
                            printf("���Ա����ʧ�ܣ����Ա���������\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
					case 16:
						printf("�������ɾ�������Ա����ƣ�");
						scanf("%s",Name);
						j=RemoveList(Lists,Name);
						if(j==OK)
							printf("���Ա�ɾ���ɹ���\n");
						else if(j==ERROR)
							printf("���Ա�ɾ��ʧ�ܣ��������޴����Ա�\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
					case 17:
						printf("����������ҵ����Ա����ƣ�");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							printf("�����Ա�λ�ڼ����е� %d λ��\n",j);
						else
							printf("���Ա����ʧ�ܣ��������޴����Ա�\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
					case 18:
						printf("����������������Ա����ƣ�");
						scanf("%s",Name);
						j=LocateList(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].L,op);
						else
						{
							getchar();
							printf("���Ա������ڼ����У����ܽ��뵥���Ա������\n");
                            printf("---���������---\n");
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
                printf("     ��ѡ����Ĳ���[0~14]:");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        j=InitList(L);
                        if(j==OK)
                        {
                            printf("�������Ա�ɹ���\n");
                            InitInput(L);
                        }
                        else
                            printf("�������Ա�ʧ�ܣ����Ա��Ѵ��ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyList(L);
                        if(j==OK)
                            printf("�������Ա�ɹ���\n");
                        else
                            printf("���Ա����ڣ����ܽ������ٲ�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 3:
                        j=ClearList(L);
                        if(j==OK)
                            printf("������Ա�ɹ���\n");
                        else
                            printf("���Ա����ڣ����ܽ�����ղ�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 4:
                        j=ListEmpty(L);
                        if(j==TRUE)
                            printf("���Ա�Ϊ�գ�\n");
                        else if(j==FALSE)
                            printf("���Ա�Ϊ�գ�\n"); 
                        else
                            printf("���Ա����ڣ����ܽ����пղ�����\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 5:
                        j=ListLength(L);
                        if(j>=0)
                            printf("���Ա���Ϊ %d ��\n",j);
                        else
                            printf("���Ա����ڣ����ܽ������������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 6:
                        printf("���������Ԫ�ص�λ�ã�");
                        scanf("%d",&i);
                        j=GetElem(L,i,e);
                        if(j==OK)
                            printf("��ȡԪ�سɹ����� %d ��Ԫ���� %d ��\n",i,e);
                        else if(j==ERROR)
                            printf("��ȡԪ��ʧ�ܣ�i��ֵ���Ϸ���\n");
                        else 
                            printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 7:
                        printf("�����������Ԫ�أ�");
                        scanf("%d",&e);
                        j=LocateElem(L,e);
                        if(j>0)
                            printf("����Ԫ�سɹ���%d �����Ա��е� %d ��Ԫ�أ�\n",e,j);
                        else if(j==ERROR)
                            printf("����Ԫ��ʧ�ܣ�%d �������Ա��У�\n",e);
                        else 
                            printf("���Ա����ڣ����ܲ���Ԫ�أ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break; 
                    case 8:
                        printf("�����������Ԫ���Ի�ȡ��ǰ��Ԫ�أ�");
                        scanf("%d",&e);
                        j=PriorElem(L,e,pre);
                        if(j==OK)
                            printf("��ȡԪ��ǰ���ɹ���%d ��ǰ��Ԫ���� %d ��\n",e,pre);
                        else if(j==ERROR)
                            printf("��ȡԪ��ǰ��ʧ�ܣ�%d ��ǰ��Ԫ�أ�\n",e);
                        else 
                            printf("���Ա����ڣ����ܻ�ȡǰ��Ԫ�أ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 9:
                        printf("�����������Ԫ���Ի�ȡ����Ԫ�أ�");
                        scanf("%d",&e);
                        j=NextElem(L,e,next);
                        if(j==OK)
                            printf("��ȡԪ�غ�̳ɹ���%d �ĺ��Ԫ���� %d ��\n",e,next);
                        else if(j==ERROR)
                            printf("��ȡԪ�غ��ʧ�ܣ�%d �޺��Ԫ�أ�\n",e);
                        else 
                            printf("���Ա����ڣ����ܻ�ȡ���Ԫ�أ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 10:
                        printf("�����������Ԫ�أ�");
						scanf("%d",&e); 
						printf("���������λ�ú�һ��Ԫ����ţ�");
						scanf("%d",&i);
                        j=ListInsert(L,i,e);
                        if(j==OK)
                            printf("����Ԫ�سɹ���\n");
                        else if(j==ERROR)
                            printf("����Ԫ��ʧ�ܣ�����λ�ò���ȷ��\n");
                        else 
                            printf("���Ա����ڣ����ܽ��в��������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 11:
                        printf("��������Ҫɾ����Ԫ�ص�λ�ã�");
                        scanf("%d",&i);
                        j=ListDelete(L,i,e);
                        if(j==OK)
                            printf("ɾ��Ԫ�سɹ���ɾ����Ԫ��Ϊ %d ��\n",e);
                        else if(j==ERROR)
                            printf("ɾ��Ԫ��ʧ�ܣ�ɾ��λ�ò���ȷ��\n");
                        else 
                            printf("���Ա����ڣ����ܽ���ɾ��������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 12:
                        j=ListTraverse(L);
                        if(j==OK)
                            printf("\n�������Ա�ɹ���\n");
                        else if(j==ERROR)
                            printf("\n���Ա�����Ԫ�أ�\n");
                        else
                            printf("\n���Ա����ڣ����ܽ��б���������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 13:
                        printf("������������ļ�·�������ƣ�");
                        scanf("%s",FileName);
                        j=SaveList(L,FileName);
                        if(j==OK)
                            printf("���Ա�浵�ɹ���\n");
                        else
                            printf("���Ա����ڣ����ܽ��д浵������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 14:
                        printf("������������ļ�·�������ƣ�");
                        scanf("%s",FileName);
                        j=LoadList(L,FileName);
                        if(j==OK)
                            printf("���Ա�����ɹ���\n");
                        else
                            printf("���Ա��Ѵ��ڣ���������ʧȥԭʼ���ݣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                }//end of switch
            }//end of while
        }//end of if
    }
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n"); 
}//end of main()

//�˵�ѡ���� 1 �������Ա�
status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L)   //��ͷ����Ѵ��ڣ�˵�����Ա����
        return INFEASIBLE;
    else
    {
        L=(LinkList)malloc(sizeof(LNode));  //��ʼ����ͷ���
        return OK;
    }
}

//�˵�ѡ���� 2 �������Ա� 
status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if(L)
    {
        LNode *p=L->next;
        while(p)
        {//����ָ��p����ͷŵ�������ռ�
            L->next=p->next;
            free(p);
            p=NULL;
            p=L->next;
        }
        free(L);
        L=NULL; //�ͷű�ͷ���ռ�
        return OK;
    }
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 3 ������Ա� 
status ClearList(LinkList &L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    if(L)
    {
        struct LNode *p=L->next;
        while(p)
        {//����ָ��p����ͷŵ�������ռ�
            L->next=p->next;
            free(p);
            p=L->next;
        }
        return OK;  //��ͷ�����Ȼ����
    }
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 4 ���Ա��п� 
status ListEmpty(LinkList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L)
        if(L->next==NULL)     //���Ա�����ұ�ͷ������һ��㲻Ϊ��
            return TRUE;
        else
            return FALSE;
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 5 ��� 
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    int len;
    if(L)
    {
        LinkList t=L;
        for(;t;t=t->next)
        {//����ָ��t�������Ա���len��¼��
            if(t->next)
                len++;
        }
        return len;
    }
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 6 ��ȡԪ�� 
status GetElem(LinkList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L)
    {
        if(i<1) //i��λ�ò��Ϸ�
            return ERROR;
        else
        {
            LinkList t=L;
            for(;t;i--,t=t->next)
                if(!i)
                {//i�ݼ���0ʱ�����ҵ�Ԫ�أ�������e��
                    e=t->data;
                    return OK;
                }
            return ERROR;   //i��λ�ô��ڱ�
        }
    }
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 7 ����Ԫ�� 
status LocateElem(LinkList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    if(L)
    {
        LinkList t=L;
        for(int i=0;t;t=t->next,i++)    //��t�������Ա���i��¼Ԫ��λ��
            if(e==t->data)
                return i;
        if(!t)  //�������������޷����ҵ�e����Ԫ��e�����������Ա���
            return ERROR;
    }
    else
        return INFEASIBLE;  //���Ա�����
}
 
 //�˵�����ѡ�� 8 ��ȡǰ��Ԫ�� 
 status PriorElem(LinkList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L)
    {
        LinkList t=L;
        for(int i=0;t->next;t=t->next,i++)
            if(e==t->next->data&&i!=0)  //����Ҫ��ȡǰ��Ԫ�أ������Ҫ�ҵ�t����һ���ֵ��e��ȣ�����ʱt���ֵ������pre��
            {
                pre=t->data;
                return OK;
            }
        return ERROR;   //Ԫ��e�������Ա���
    }
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 9 ��ȡ���Ԫ��
status NextElem(LinkList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L)
    {
        LinkList t=L;
        for(int i=0;t->next;t=t->next,i++)
            if(e==t->data)  //���ҵ���e��ȵĽ��󣬷��غ�һ���ֵ
            {
                next=t->next->data;
                return OK;
            }
        return ERROR;   //Ԫ��e�������Ա���
    }
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 10 ����Ԫ�� 
status ListInsert(LinkList &L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L)
    {
        LinkList t=L;
        for(int j=0;t;t=t->next,j++)
        {
            if(j+1==i)  //j���tָ��iλ�õ�ǰһ��Ԫ��
            {//�����������ָ����ɲ������
                LinkList tag;
                tag=(LinkList)malloc(sizeof(LNode));
                tag->data=e;
                tag->next=t->next;
                t->next=tag;
                return OK;
            }
        }
        return ERROR;   //iλ�ò��Ϸ�
    }
    else
        return INFEASIBLE;  //���Ա�����
}
 
//�˵�����ѡ�� 11 ɾ��Ԫ��
status ListDelete(LinkList &L,int i,ElemType &e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L)
    {
        LinkList t=L;
        for(int j=0;t;t=t->next,j++)
            if(j+1==i)  //j���tָ��iλ�õ�ǰһ��Ԫ��
            {//�����������ָ�����ɾ������
                LinkList tag=t->next;
                e=t->next->data;
                t->next=t->next->next;
                free(tag);
                return OK;
            }
        return ERROR;   //iλ�ò��Ϸ�
    }
    else
        return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 12 �������Ա�
status ListTraverse(LinkList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L)
    {
        LinkList t=L->next;
        int flag=0;
        for(;t;t=t->next)
        {//��tָ��������Ա�
            flag=1; //������Ա��Ƿ�Ϊ�գ���ʹ��flagҲ������ȷ����ֵ��
            if(t->next)
                printf("%d ",t->data);
            else
                printf("%d",t->data);
        }
        if(flag)
            return OK;
        else
            return ERROR;   //���Ա�Ϊ��
    }
    else
        return INFEASIBLE;  //���Ա�����
} 

//�˵�����ѡ�� 13 ���Ա�浵
status SaveList(LinkList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
	if(L)
	{
		LinkList t=L->next;
		FILE *fp;
		fp=fopen(FileName,"wb");
		while(t)
		{//��tָ��������Ա������Ա�Ԫ��д���ļ���
			fprintf(fp,"%d ",t->data);
			t=t->next;
		}
		fclose(fp);
		return OK;
	}
	else
		return INFEASIBLE;  //���Ա�����
}

//�˵�����ѡ�� 14 ���Ա���� 
status LoadList(LinkList &L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	if(!L)
	{
		L=(LinkList)malloc(sizeof(LNode));  //��ʼ����ͷ���
		L->next=NULL;
		FILE *fp;
		LinkList t;
		if((fp=fopen(FileName,"rb"))!=NULL)
		{
			L->next=(LinkList)malloc(sizeof(LNode));    //ʹ���Ƚ��ȳ��ĵ��������ļ�������Ԫ�ض������Ա���
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
		return INFEASIBLE;  //���Ա��Ѵ��ڣ�������ʹ����Ԫ��ʧȥ
} 

//�˵�����ѡ�� 15 �����Ա����֮���ӿ����Ա�
status AddList(LISTS &Lists,char ListName[])
// ��Lists������һ������ΪListName�Ŀ����Ա����Ա����������������롣
{
    if(Lists.length<Lists.listsize)
    {
        int i,flag=0;
    	for(i=0;i<Lists.length;i++)
			if(!strcmp(Lists.elem[i].name,ListName))
			{//�����Ա����ƽ��бȽϲ��ң����ҳɹ�ʱ��ǲ��˳�ѭ��
				flag=1;
				break;
			}				
		if(!flag)	//����ʧ�ܣ�˵�����޴����Ա���������
		{
			strcpy(Lists.elem[Lists.length].name,ListName);	//����strcpy�����������Ա�����
			Lists.elem[Lists.length].L=(LinkList)malloc(sizeof(LNode));	//Ϊ���Ա��ͷ��㿪�ٿռ�
            Lists.elem[Lists.length].L->next=NULL;
			Lists.length++;	//���ϳ�������
			return OK;
		}
	    else	//���Ա��Ѵ��ڣ���������
			return ERROR;
    }
    else	//���Ա�������������������Ա�
        return OVERFLOW;
}

//�˵�����ѡ�� 16 �����Ա����֮ɾ�����Ա� 
status RemoveList(LISTS &Lists,char ListName[])
// ��Lists��ɾ��һ������ΪListName�����Ա�
{
    int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
        if(!strcmp(Lists.elem[i].name,ListName))
		{//�����Ա����ƽ��бȽϲ��ң����ҳɹ�ʱ��ǲ��˳�ѭ��
			flag=1;
			break;
		}
	}
	if(flag)
	{
		DestroyList(Lists.elem[i].L);   //�����������Ա������ٵ�ǰ���Ա�
        for(;i<Lists.length-1;i++)	//�����ҵ������Ա������Ա�˳��ǰ��һλ
			Lists.elem[i]=Lists.elem[i+1];
        if(i!=Lists.length-1)   //����ĩλ���Ա�δ�����٣������������Ա�������
            DestroyList(Lists.elem[Lists.length-1].L);
        Lists.elem[Lists.length-1].name[0]='\0';	//��ԭ����ĩλ�����Ա�������Ϊ�գ��ͷ����ͷ���
        Lists.elem[Lists.length-1].L=NULL;
        free(Lists.elem[Lists.length-1].L);
		Lists.length--;
		return OK;
	}
	else
		return ERROR;
}

//�˵�����ѡ�� 17 �����Ա����֮�������Ա� 
int LocateList(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName�����Ա����ҳɹ������߼���ţ����򷵻�ERROR�� 
{
    int i,flag=0;
	for(i=0;i<Lists.length;i++)
	{
		if(!strcmp(Lists.elem[i].name,ListName))
		{//�����Ա����ƽ��бȽϲ��ң����ҳɹ�ʱ��ǲ��˳�ѭ��
			flag=1;
			break;
		}
	}
	if(!flag||!Lists.length)	//����ʧ�ܻ����Ա��ϳ���Ϊ0
		return ERROR;
	else    //���ҳɹ������߼�λ��
		return i+1;
}

//�����������������Ա�Ԫ��
status InitInput(LinkList &L)
// ѡ���Ƿ������Ա����������ݣ��������û�������0Ϊ������־��һ�����ݣ�����OK�����򷵻�0�� 
{
	int ord,temp;
	LinkList tail=L,p=L;
	printf("��������ѡ��1������ѡ��0��\n");
	scanf("%d",&ord);
	if(ord)
	{
		printf("������һ�����ݴ����Ƚ��ȳ�����0Ϊ������־��\n");
        scanf("%d",&temp);
		while(temp)
		{//�Ƚ��ȳ��ĵ�������
			tail=(LinkList)malloc(sizeof(LNode));
			tail->data=temp;
			tail->next=NULL;
			p->next=tail;
			p=p->next;
			scanf("%d",&temp);
		}
		printf("����ɹ���\n");
        return 0;
	}
	else
		return 0;
} 

//������������������˵�
void SecondaryTable(LinkList &L,int op)
// ����ѡ�Ķ����Ա����еĴ��������Ա��ݽ�������˵��У�ʵ�ֶԵ����Ա�Ļ���������
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
        printf("     ��ѡ����Ĳ���[-1��1~14]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                j=InitList(L);
                if(j==OK)
                {
                    printf("�������Ա�ɹ���\n");
                    InitInput(L);
                }
                else
                    printf("�������Ա�ʧ�ܣ����Ա��Ѵ��ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 2:
                j=DestroyList(L);
                if(j==OK)
                    printf("�������Ա�ɹ���\n");
                else
                    printf("���Ա����ڣ����ܽ������ٲ�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 3:
                j=ClearList(L);
                if(j==OK)
                    printf("������Ա�ɹ���\n");
                else
                    printf("���Ա����ڣ����ܽ�����ղ�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 4:
                j=ListEmpty(L);
                if(j==TRUE)
                    printf("���Ա�Ϊ�գ�\n");
                else if(j==FALSE)
                    printf("���Ա�Ϊ�գ�\n"); 
                else
                    printf("���Ա����ڣ����ܽ����пղ�����\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 5:
                j=ListLength(L);
                if(j>=0)
                    printf("���Ա���Ϊ %d ��\n",j);
                else
                    printf("���Ա����ڣ����ܽ������������\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 6:
                printf("���������Ԫ�ص�λ�ã�");
                scanf("%d",&i);
                j=GetElem(L,i,e);
                if(j==OK)
                    printf("��ȡԪ�سɹ����� %d ��Ԫ���� %d ��\n",i,e);
                else if(j==ERROR)
                    printf("��ȡԪ��ʧ�ܣ�i��ֵ���Ϸ���\n");
                else 
                    printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 7:
                printf("�����������Ԫ�أ�");
                scanf("%d",&e);
                j=LocateElem(L,e);
                if(j>0)
                    printf("����Ԫ�سɹ���%d �����Ա��е� %d ��Ԫ�أ�\n",e,j);
                else if(j==ERROR)
                    printf("����Ԫ��ʧ�ܣ�%d �������Ա��У�\n",e);
                else 
                    printf("���Ա����ڣ����ܲ���Ԫ�أ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break; 
            case 8:
                printf("�����������Ԫ���Ի�ȡ��ǰ��Ԫ�أ�");
                scanf("%d",&e);
                j=PriorElem(L,e,pre);
                if(j==OK)
                    printf("��ȡԪ��ǰ���ɹ���%d ��ǰ��Ԫ���� %d ��\n",e,pre);
                else if(j==ERROR)
                    printf("��ȡԪ��ǰ��ʧ�ܣ�%d ��ǰ��Ԫ�أ�\n",e);
                else 
                    printf("���Ա����ڣ����ܻ�ȡǰ��Ԫ�أ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 9:
                printf("�����������Ԫ���Ի�ȡ����Ԫ�أ�");
                scanf("%d",&e);
                j=NextElem(L,e,next);
                if(j==OK)
                    printf("��ȡԪ�غ�̳ɹ���%d �ĺ��Ԫ���� %d ��\n",e,next);
                else if(j==ERROR)
                    printf("��ȡԪ�غ��ʧ�ܣ�%d �޺��Ԫ�أ�\n",e);
                else 
                    printf("���Ա����ڣ����ܻ�ȡ���Ԫ�أ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 10:
                printf("�����������Ԫ�أ�");
                scanf("%d",&e); 
                printf("���������λ�ú�һ��Ԫ����ţ�");
                scanf("%d",&i);
                j=ListInsert(L,i,e);
                if(j==OK)
                    printf("����Ԫ�سɹ���\n");
                else if(j==ERROR)
                    printf("����Ԫ��ʧ�ܣ�����λ�ò���ȷ��\n");
                else 
                    printf("���Ա����ڣ����ܽ��в��������\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 11:
                printf("��������Ҫɾ����Ԫ�ص�λ�ã�");
                scanf("%d",&i);
                j=ListDelete(L,i,e);
                if(j==OK)
                    printf("ɾ��Ԫ�سɹ���ɾ����Ԫ��Ϊ %d ��\n",e);
                else if(j==ERROR)
                    printf("ɾ��Ԫ��ʧ�ܣ�ɾ��λ�ò���ȷ��\n");
                else 
                    printf("���Ա����ڣ����ܽ���ɾ��������\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 12:
                j=ListTraverse(L);
                if(j==OK)
                    printf("\n�������Ա�ɹ���\n");
                else if(j==ERROR)
                    printf("\n���Ա�����Ԫ�أ�\n");
                else
                    printf("\n���Ա����ڣ����ܽ��б���������\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 13:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=SaveList(L,FileName);
                if(j==OK)
                    printf("���Ա�浵�ɹ���\n");
                else
                    printf("���Ա����ڣ����ܽ��д浵������\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 14:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=LoadList(L,FileName);
                if(j==OK)
                    printf("���Ա�����ɹ���\n");
                else
                    printf("���Ա��Ѵ��ڣ���������ʧȥԭʼ���ݣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case -1:
                break;
        }//end of switch
    }//end of while
}