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
#define OVERFLOW -2 //Ԥ����ĳ��� 

typedef int status; //�������ؽ����־ 
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100 //���Ա�洢�ṹ����Ŀռ� 
#define LISTINCREMENT  10 //���Ա�ռ�������� 
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem; //��ų�������Ԫ�ص�˳��� 
	int length; //���Ա�� 
	int listsize; //���Ա����ռ��С 
}SqList;
typedef struct{  //���Ա�Ĺ������
    struct { char name[30]; //���Ա����� 
     		SqList L;	
    } elem[10]; //������Ա�ļ��� 
    int length; //���Ա��ϵĳ��� 
    int listsize; //���Ա��Ϸ���Ŀռ� 
}LISTS;

void SecondaryTable(SqList &L,int op);//��������˵�
status InitInput(SqList &L); //���Ա��������� 
status InitList(SqList &L); //���Ա��ʼ�� 
status DestroyList(SqList &L); //���Ա����� 
status ClearList(SqList &L); //���Ա���� 
status ListEmpty(SqList L); //���Ա��п� 
status ListLength(SqList L); //�����Ա��� 
status GetElem(SqList L,int i,ElemType &e); //��ȡ���Ա���ĳλ�õ�Ԫ�� 
int LocateElem(SqList L,ElemType e); //����Ԫ�������Ա��е�λ�� 
status PriorElem(SqList L,ElemType e,ElemType &pre); //��ȡ���Ա���ĳԪ�ص�ǰ��Ԫ�� 
status NextElem(SqList L,ElemType e,ElemType &next); //��ȡ���Ա���ĳԪ�صĺ��Ԫ��
status ListInsert(SqList &L,int i,ElemType e); //���Ա����Ԫ�� 
status ListDelete(SqList &L,int i,ElemType &e); //���Ա�ɾ��Ԫ�� 
status ListTraverse(SqList L);  //����������Ա�Ԫ��
status SaveList(SqList L,char FileName[]); //���Ա�浵
status LoadList(SqList &L,char FileName[]); //���Ա���� 
status AddList(LISTS &Lists,char ListName[]); //���ӿ����Ա� 
status RemoveList(LISTS &Lists,char ListName[]); //�Ƴ����Ա�
int LocateList(LISTS Lists,char ListName[]); //�������Ա� 
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
	}//��ʼ�� 
	while(op!=-3){
		system("cls");	printf("\n\n");
		printf("          Menu for Linear Table On Sequence Structure \n");
		printf("--------------------------------------------------------------\n");
		printf("          -1.MainTable/MultiList     -2.SingleList\n");
		printf("    	  -3.Exit\n");
		printf("--------------------------------------------------------------\n");
		printf("     ��ѡ�����ڵĲ˵��㼶��\n");
		printf("     -1�����˵�ʵ�ֶ����Ա����-2����ʱ�����Ա����������\n");
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
						printf("\t���Ա�%d��δ����            \t���Ա�%d��δ����",i+1,i+6);
					else if(Lists.elem[i].L.elem==NULL&&Lists.elem[i+5].L.elem!=NULL)
						printf("\t���Ա�%d��δ����            \t���Ա�%d��%s",i+1,i+6,Lists.elem[i+5].name);
					else if(Lists.elem[i].L.elem!=NULL&&Lists.elem[i+5].L.elem==NULL)
						printf("\t���Ա�%d��%s                \t���Ա�%d��δ����",i+1,Lists.elem[i].name,i+6);
					else
						printf("\t���Ա�%d��%s                \t���Ա�%d��%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
					printf("\n");
				}
				printf("     ��ѡ����Ĳ���[0��15~18]:");
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
				printf("     ��ѡ����Ĳ���[0~14]:");
				scanf("%d",&op);
			    switch(op){
				    case 1:
				    	j=InitList(L);
					 	if(j==OK)
					 	{
					 		printf("���Ա����ɹ���\n");
					 		InitInput(L);
						}	
					 	else if(j==ERROR)
					 		printf("���Ա���ʧ�ܣ�\n");
						else if(j==INFEASIBLE)
							printf("���Ա��Ѵ��ڣ����ܽ������Ա��ʼ��������\n");
					 	getchar();
						printf("---���������---\n");
						getchar();
					 	break;
				   	case 2:
				   		j=DestroyList(L);
					 	if(j==OK)
					 		printf("���Ա����ٳɹ���\n");
						else if(j==INFEASIBLE)
							printf("���Ա����ڣ����ܽ������Ա����ٲ�����\n");
					 	getchar();
						printf("---���������---\n"); 
						getchar();
					 	break;
				   	case 3:
						if(ClearList(L)==OK)
							printf("���Ա���ճɹ���\n");
						else
							printf("���Ա����ڣ����ܽ������Ա���ղ�����\n");    
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
						else if(j==INFEASIBLE)
							printf("���Ա�����,���ܽ������Ա��пղ�����\n");    
					 	getchar();
						printf("---���������---\n");
						getchar();
					 	break;
				    case 5:
						j=ListLength(L);
						if(j>=0)
							printf("���Ա���Ϊ %d ��\n",j);
						else
							printf("���Ա����ڣ����������\n");    
					 	getchar();
						printf("---���������---\n");
						getchar();
					 	break;
				   	case 6:
					 	printf("���������Ԫ�ص�λ�ã�");
					 	scanf("%d",&i); 
					 	j=GetElem(L,i,e);
					    if(j==OK)
					    	printf("�� %d λԪ���� %d ��\n",i,e);
					    else if(j==ERROR)
					    	printf("��ѡ���Ԫ��λ�ò��Ϸ�������С��1��������Ա��ȣ�\n");
					    else if(j==INFEASIBLE)
					    	printf("���Ա����ڣ����ܽ���Ԫ�ػ�ȡ��\n");
					 	getchar();
						printf("---���������---\n"); 
						getchar();
						break;
				   	case 7:
					 	printf("�����������Ԫ�أ�");
					 	scanf("%d",&e);
						j=LocateElem(L,e);
						if(j>0)
							printf("������Ԫ�� %d �����Ա��еĵ� %d λ��\n",e,j);
						else if(j==ERROR)
							printf("����Ԫ��ʧ�ܣ���Ԫ�ز������Ա��У�\n");
						else if(j==INFEASIBLE)
							printf("���Ա����ڣ����ܽ���Ԫ�ز��ң�\n");
						getchar();
						printf("---���������---\n"); 
						getchar();
						break;
				   	case 8:
						printf("�����������Ԫ���Ի�ȡ��ǰ��Ԫ�أ�");
						scanf("%d",&e);
						j=PriorElem(L,e,pre);
						if(j==OK)
							printf("Ԫ�� %d ��ǰ��Ԫ���� %d ��\n",e,pre);
						else if(j==ERROR)
							printf("Ԫ�� %d û��ǰ��Ԫ�أ�\n",e);
						else if(j==INFEASIBLE)
							printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");	     
					 	getchar();
						printf("---���������---\n"); 
						getchar();
					 	break;
				   	case 9:
						printf("�����������Ԫ���Ի�ȡ����Ԫ�أ�");
						scanf("%d",&e);
						j=NextElem(L,e,next);
						if(j==OK)
							printf("Ԫ�� %d �ĺ��Ԫ���� %d ��\n",e,next);
						else if(j==ERROR)
							printf("Ԫ�� %d û�к��Ԫ�أ�\n",e);
						else if(j==INFEASIBLE)
							printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");	   
					 	getchar();
						printf("---���������---"); 
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
							printf("����λ�ò���ȷ��\n");
						else if(j==INFEASIBLE)
							printf("���Ա����ڣ����ܽ��в��������\n");   
					 	getchar();
						printf("---���������---"); 
						getchar();
					 	break;
				   	case 11:
					 	printf("��������Ҫɾ����Ԫ�ص�λ�ã�");
						scanf("%d",&i); 
						j=ListDelete(L,i,e);
						if(j==OK)
							printf("ɾ��Ԫ�سɹ�����ɾ��Ԫ��Ϊ %d ��\n",e);
						else if(j==ERROR)
							printf("ɾ��λ�ò���ȷ��\n");
						else if(j==INFEASIBLE)
							printf("���Ա����ڣ����ܽ���ɾ��������\n");
					 	getchar();
						printf("---���������---"); 
						getchar();
					 	break;
				   	case 12:
					   	j=ListTraverse(L);
					 	if(j==OK)
						 	printf("\n���Ա�����ɹ���\n");
						else if(j==ERROR)
							printf("\n���Ա�����Ԫ�أ�\n");
						else if(j==INFEASIBLE)
							printf("\n���Ա����ڣ�\n");
						getchar(); 
						printf("---���������---"); 
						getchar();
					 	break;
					case 13:
						printf("������������ļ�·�������ƣ�");
						scanf("%s",FileName);
						j=SaveList(L,FileName);
						if(j==OK)
							printf("���Ա��������ѳɹ�д��ָ���ļ��У�\n");
						else if(j==INFEASIBLE)
							printf("���Ա����ڣ�\n");
						getchar(); 
						printf("---���������---"); 
						getchar();
						break;
					case 14:
						printf("������������ļ�·�������ƣ�");
						scanf("%s",FileName);
						j=LoadList(L,FileName);
						if(j==OK)
							printf("�ļ��������ѳɹ�д�����Ա��У�\n");
						else if(j==INFEASIBLE)
							printf("���Ա��Ѵ��ڣ�ֱ��д��ᵼ�±���ԭ���ݶ�ʧ��\n");
						getchar(); 
						printf("---���������---"); 
						getchar();
						break;	
					case 0:
			         	break;
				}//end of switch
			}//end of while
		}//end of if	
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

//�˵�����ѡ�� 1 ��ʼ�����Ա� 
status InitList(SqList& L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem==NULL)
    {//ʹ��malloc����Ϊ˳����ٿռ䣬��ΪLIST_INIT_SIZE
        L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L.length=0;
        L.listsize=LIST_INIT_SIZE;
		return OK;
    }
    else
        return INFEASIBLE;	//���Ա��Ѵ��ڣ����ܹ���ձ�
}

//�˵�����ѡ�� 2 �������Ա� 
status DestroyList(SqList& L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    if(L.elem)//ͨ��˳����׵�ַ��ָ���Ƿ�Ϊ���ж����Ա��Ƿ����
    {
        L.elem=NULL;
        free(L.elem);
        L.length=0;	//�����ٺ����Ա���Ϳռ��С����Ϊ0
        L.listsize=0;
        return OK;
    }
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 3 ������Ա� 
status ClearList(SqList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    if(L.elem)
    {
        L.length=0;	//������Ա�ֻ������Ա���Ԫ�أ������ٱ�ͷ
        return OK;
    }
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 4 ���Ա��п�
status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem)
    {
        if(L.length==0)	//ͨ�����Ա���ж����Ա��Ƿ�Ϊ��
            return TRUE;
        else
            return FALSE;
    }
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 5 �����Ա���
status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    if(L.elem)
        return L.length;	//���Ա��ȿ�ֱ����L.length��ӳ
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 6 ��ȡԪ��
status GetElem(SqList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{ 
    if(L.elem)
    {
	    if(i<1||i>L.length)	//����ȡԪ�������Ա���λ�ò��Ϸ�
	        return ERROR;
		e=L.elem[i-1];	//iΪ�߼�˳��i-1Ϊ����˳��
        return OK;
    }
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 7 ����Ԫ�� 
int LocateElem(SqList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE����-1����
{
    int i,flag=1;
    if(L.elem) 
    {
        for(i=0;i<L.length;i++)	//�������Ա�
        {
            if(e==L.elem[i])	//��ȡ���Ա����������Ԫ����ͬ�Ľ��
            {
                flag=0;	//flag�����Ա�����Ա����Ƿ����������Ԫ����ͬ�Ľ�㣨��flagҲ�ɣ�
                return i+1;	//����ֵΪ�߼����
            }
        }
        if(flag)
            return ERROR;	//������eԪ����ͬ�Ľ��ʧ��
    }
    else
        return INFEASIBLE;	//���Ա�����
}
 
//�˵�����ѡ�� 8 ��ȡǰ��Ԫ�� 
status PriorElem(SqList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    int i;
    if(L.elem)
    {
        for(i=1;i<L.length;i++)
        {//�������Ա�
            if(e==L.elem[i])
            {//���ҵ���ӦԪ�غ󣬷�����ǰ��Ԫ��
                pre=L.elem[i-1];
                return OK;
            }
        }
        return ERROR;	//������eԪ����ͬ�Ľ��ʧ��
    }
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 9 ��ȡ���Ԫ��
status NextElem(SqList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    int i;
    if(L.elem)
    {
        for(i=0;i<L.length-1;i++)
        {//�������Ա�
            if(e==L.elem[i])
            {//���ҵ���ӦԪ�غ󣬷�������Ԫ��
                next=L.elem[i+1];
                return OK;
            }
        }
        return ERROR;	//������eԪ����ͬ�Ľ��ʧ��
    }
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 10 ����Ԫ�� 
status ListInsert(SqList &L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    int j;
    if(L.elem)
    {	
		if(i<=L.length+1&&i>0&&L.length<L.listsize)	//iλ�úϷ������Ա�δ��
        {
	        for(j=L.length;j>=i-1;j--)	//����i��λ�ã��߼�λ�ã����Ԫ��ȫ������һλ����������Ԫ�ز��뵽i��Ӧλ��
	            L.elem[j]=L.elem[j-1];
	        L.elem[i-1]=e;
			L.length++;	//���Ա�������
            return OK;
        }
        else if(i<=L.length+1&&i>0&&L.length>=L.listsize)	//iλ�úϷ������Ա�����
        {
            L.elem=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));	//Ϊ���Ա����ӿռ��Դ����������Ԫ��
            L.listsize+=LISTINCREMENT;	//���Ա�ռ�����
        	for(j=L.length;j>=i-1;j--)
	            L.elem[j]=L.elem[j-1];
	        L.elem[i-1]=e;
			L.length++;
            return OK;
		}
        else
            return ERROR;	//iλ�ò��Ϸ�
    }
    else
        return INFEASIBLE;	//���Ա�����
} 

//�˵�����ѡ�� 11 ɾ��Ԫ��
status ListDelete(SqList &L,int i,ElemType &e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem)
    {
        if(L.length>0&&i<L.length&&i>0)	//iλ�úϷ�
        {
            e=L.elem[i-1];	//����i��λԪ�أ���������e��
			for(;i<L.length;i++)	//��iλ��֮���Ԫ�������Ա���ǰ��һλ
                L.elem[i-1]=L.elem[i];
            L.length--;	//����1
            return OK;
        }
        else
            return ERROR;	//iλ�ò��Ϸ�
    }
    else
        return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 12 �������Ա� 
status ListTraverse(SqList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    if(L.elem)
    {
        if(!L.length)	//���Ա�Ϊ��
        	return ERROR;
		for(int i=0;i<L.length;i++)
        {
            if(i!=L.length-1)	//�������Ա�ﵽĩλ
                printf("%d ",L.elem[i]);
            else
                printf("%d",L.elem[i]);
        }    
        return OK;
    }
    else
        return INFEASIBLE;	//���Ա�����
} 

//�˵�����ѡ�� 13 ���Ա�浵 
status  SaveList(SqList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    FILE *fp;
    int i=0;
	if(L.elem)
	{
		fp=fopen(FileName,"wb");
		if(!fp)	//�ļ���ʧ��
			return ERROR;
		while(i<L.length)
		{
			fprintf(fp,"%d ",L.elem[i]);	//�����Ա�������д���ļ�
			i++;
		}
		fclose(fp);
		return OK;
	}
	else
		return INFEASIBLE;	//���Ա�����
}

//�˵�����ѡ�� 14 ���Ա���� 
status  LoadList(SqList &L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	FILE *fp;
    int i=0; 
	if(L.elem)
		return INFEASIBLE;	//���Ա��Ѵ��ڣ�������ʹԪ��ʧȥ
	else
	{
		L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);	//��ʼ�����Ա�
        L.length=0;
       	L.listsize=LIST_INIT_SIZE;
		if((fp=fopen(FileName,"rb"))!=NULL)
		{
			while((fscanf(fp,"%d ",&L.elem[i]))!=EOF)	//�ļ�δ��ȡ���
            {
                if(L.length<L.listsize-1)	//���Ա�δ����ֱ�Ӷ�������
                {
	                L.length++;
	                i++;
				}
				else	//���Ա����������·���ռ��ٶ�������
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
			Lists.elem[Lists.length].L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));	//Ϊ���Ա��ٿռ��ʼ���ռ��С�ͳ���
			Lists.elem[Lists.length].L.listsize=LIST_INIT_SIZE;	//��ʼ���ռ��С�ͳ���
			Lists.elem[Lists.length].L.length=0;
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
	if(flag)	//���ҳɹ�
	{
		for(;i<Lists.length-1;i++)	//�����ҵ������Ա������Ա�˳��ǰ��һλ
			Lists.elem[i]=Lists.elem[i+1];
		Lists.elem[Lists.length-1].name[0]='\0';	//��ԭ����ĩλ�����Ա����ƺ�������Ϊ��
		Lists.elem[Lists.length-1].L.elem=NULL;
		Lists.elem[Lists.length-1].L.length=0;
		Lists.elem[Lists.length-1].L.listsize=0;
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

//�������������Ա���������
status InitInput(SqList &L)
// ѡ���Ƿ������Ա����������ݣ��������û�������0Ϊ������־��һ�����ݣ�����OK�����򷵻�0��
{
	int ord, temp; 
	printf("��������ѡ��1������ѡ��0��\n");
	scanf("%d",&ord);
	if(ord==0)	//��0Ϊ������־
		return 0;
	else
	{
		printf("������һ�����ݣ�0Ϊ������־��\n");
		scanf("%d",&temp);
		while(temp != 0)	//Ԫ�������ֹ�ı�־
		{
			ListInsert(L,L.length+1,temp);	//���ò��뺯�������Ա�β������Ԫ��
			scanf("%d",&temp);
		}
		printf("����ɹ���\n");
		return OK;
	}
}

//������������������˵�
void SecondaryTable(SqList &L,int op)
// ����ѡ�Ķ����Ա����еĴ��������Ա��ݽ�������˵��У�ʵ�ֶԵ����Ա�Ļ���������
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
		printf("     ��ѡ����Ĳ���[-1��1~14]:");
		scanf("%d",&op);
		switch(op){
			case 1:
				j=InitList(L);
				if(j==OK)
				{
					printf("���Ա����ɹ���\n");
					InitInput(L);
				}	
				else if(j==ERROR)
					printf("���Ա���ʧ�ܣ�\n");
				else if(j==INFEASIBLE)
					printf("���Ա��Ѵ��ڣ����ܽ������Ա��ʼ��������\n");
				getchar();
				printf("---���������---\n");
				getchar();
				break;
			case 2:
				j=DestroyList(L);
				if(j==OK)
					printf("���Ա����ٳɹ���\n");
				else if(j==ERROR)
					printf("���Ա�����ʧ�ܣ�\n");
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ����ܽ������Ա����ٲ�����\n");
			 	getchar();
				printf("---���������---\n"); 
				getchar();
			 	break;
		   	case 3:
				if(ClearList(L)==OK)
					printf("���Ա���ճɹ���\n");
				else
					printf("���Ա����ڣ����ܽ������Ա���ղ�����\n");    
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
				else if(j==INFEASIBLE)
					printf("���Ա�����,���ܽ������Ա��пղ�����\n");    
				getchar();
				printf("---���������---\n");
				getchar();
				break;
			case 5:
				j=ListLength(L);
				if(j>=0)
					printf("���Ա���Ϊ %d ��\n",j);
				else
					printf("���Ա����ڣ����������\n");    
				getchar();
				printf("---���������---\n");
				getchar();
				break;
			case 6:
				printf("���������Ԫ�ص�λ�ã�");
				scanf("%d",&i); 
				j=GetElem(L,i,e);
				if(j==OK)
					printf("�� %d λԪ���� %d ��\n",i,e);
				else if(j==ERROR)
					printf("��ѡ���Ԫ��λ�ò��Ϸ�������С��1��������Ա��ȣ�\n");
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ����ܽ���Ԫ�ػ�ȡ��\n");
				getchar();
				printf("---���������---\n"); 
				getchar();
				break;
			case 7:
				printf("�����������Ԫ�أ�");
				scanf("%d",&e);
				j=LocateElem(L,e);
				if(j>0)
					printf("������Ԫ�� %d �����Ա��еĵ� %d λ��\n",e,j);
				else if(j==ERROR)
					printf("����Ԫ��ʧ�ܣ���Ԫ�ز������Ա��У�\n");
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ����ܽ���Ԫ�ز��ң�\n");
				getchar();
				printf("---���������---\n"); 
				getchar();
				break;
			case 8:
				printf("�����������Ԫ���Ի�ȡ��ǰ��Ԫ�أ�");
				scanf("%d",&e);
				j=PriorElem(L,e,pre);
				if(j==OK)
					printf("Ԫ�� %d ��ǰ��Ԫ���� %d ��\n",e,pre);
				else if(j==ERROR)
					printf("Ԫ�� %d û��ǰ��Ԫ�أ�\n",e);
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");	     
				getchar();
				printf("---���������---\n"); 
				getchar();
				break;
			case 9:
				printf("�����������Ԫ���Ի�ȡ����Ԫ�أ�");
				scanf("%d",&e);
				j=NextElem(L,e,next);
				if(j==OK)
					printf("Ԫ�� %d �ĺ��Ԫ���� %d ��\n",e,next);
				else if(j==ERROR)
					printf("Ԫ�� %d û�к��Ԫ�أ�\n",e);
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ����ܻ�ȡԪ�أ�\n");	   
				getchar();
				printf("---���������---"); 
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
					printf("����λ�ò���ȷ��\n");
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ����ܽ��в��������\n");   
				getchar();
				printf("---���������---"); 
				getchar();
				break;
			case 11:
				printf("��������Ҫɾ����Ԫ�ص�λ�ã�");
				scanf("%d",&i);
				j=ListDelete(L,i,e);
				if(j==OK)
					printf("ɾ��Ԫ�سɹ�����ɾ��Ԫ��Ϊ %d ��\n",e);
				else if(j==ERROR)
					printf("ɾ��λ�ò���ȷ��\n");
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ����ܽ���ɾ��������\n");
				getchar();
				printf("---���������---"); 
				getchar();
				break;
			case 12:
				j=ListTraverse(L);
				if(j==OK)
					printf("\n���Ա�����ɹ���\n");
				else if(j==ERROR)
					printf("\n���Ա�����Ԫ�أ�\n");
				else if(j==INFEASIBLE)
					printf("\n���Ա����ڣ�\n");
				getchar(); 
				printf("---���������---"); 
				getchar();
				break;
			case 13:
				printf("������������ļ�·�������ƣ�");
				scanf("%s",FileName);
				j=SaveList(L,FileName);
				if(j==OK)
					printf("���Ա��������ѳɹ�д��ָ���ļ��У�\n");
				else if(j==INFEASIBLE)
					printf("���Ա����ڣ�\n");
				getchar(); 
				printf("---���������---"); 
				getchar();
				break;
			case 14:
				printf("������������ļ�·�������ƣ�");
				scanf("%s",FileName);
				j=LoadList(L,FileName);
				if(j==OK)
					printf("�ļ��������ѳɹ�д�����Ա��У�\n");
				else if(j==INFEASIBLE)
					printf("���Ա��Ѵ��ڣ�ֱ��д��ᵼ�±���ԭ���ݶ�ʧ��\n");
				getchar(); 
				printf("---���������---"); 
				getchar();
				break;	
			case -1:
				break;
		}//end of switch
	}//end of while
}