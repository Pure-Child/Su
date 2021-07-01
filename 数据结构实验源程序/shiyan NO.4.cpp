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
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
        int adjvex;              //����λ�ñ�� 
        struct ArcNode  *nextarc;	   //��һ������ָ��
} ArcNode;
typedef struct VNode{				//ͷ��㼰���������Ͷ���
        VertexType data;       	//������Ϣ
        ArcNode *firstarc;      	 //ָ���һ����
} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;     	 //ͷ�������
    int vexnum,arcnum;   	  //������������
    GraphKind  kind;        //ͼ������
} ALGraph;
typedef struct{  //����ͼ�Ĺ������
    struct { char name[30]; //����ͼ���� 
     		ALGraph G;	
    } elem[10]; //�������ͼ�ļ��� 
    int length; //����ͼ���ϵĳ��� 
    int listsize; //����ͼ���Ϸ���Ŀռ� 
}LISTS; 

typedef int ElemType;   //ջ�Ͷ��еĶ���
typedef struct stack
{
    ElemType elem[MAX_VERTEX_NUM];
    int p;
} stack; //ջ�Ķ���
typedef struct QUEUE
{
    ElemType elem[MAX_VERTEX_NUM];
    int front, length;
} QUEUE; //ѭ������

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
	}//��ʼ�� 
	while(op!=-3){
        system("cls");	printf("\n\n");
        printf("          Menu for Linear Table On Sequence Structure \n");
        printf("--------------------------------------------------------------\n");
        printf("         -1.MainTable/MultiGraph     -2.SingleGraph\n");
        printf("    	 -3.Exit\n");
        printf("--------------------------------------------------------------\n");
        printf("     ��ѡ�����ڵĲ˵��㼶��\n");
        printf("     -1�����˵�ʵ�ֶ�����ͼ����-2����ʱ������ͼ����������\n");
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
                        printf("\t����ͼ%d��δ����            \t����ͼ%d��δ����",i+1,i+6);
                    else if(Lists.elem[i].G.vexnum==0&&Lists.elem[i+5].G.vexnum!=0)
                        printf("\t����ͼ%d��δ����            \t����ͼ%d��%s",i+1,i+6,Lists.elem[i+5].name);
                    else if(Lists.elem[i].G.vexnum!=0&&Lists.elem[i+5].G.vexnum==0)
                        printf("\t����ͼ%d��%s                \t����ͼ%d��δ����",i+1,Lists.elem[i].name,i+6);
                    else
                        printf("\t����ͼ%d��%s                \t����ͼ%d��%s",i+1,Lists.elem[i].name,i+6,Lists.elem[i+5].name);
                    printf("\n");
                }
                printf("     ��ѡ����Ĳ���[0��15~18]:");
				scanf("%d",&op);
				switch(op){
                    case 15:
                        printf("���������ӵ�����ͼ���ƣ�");
                        scanf("%s",Name);
                        j=AddGraph(Lists,Name);
                        if(j==OK)
                            printf("����ͼ��ӳɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("����ͼ���ʧ�ܣ�������ͼ�Ѵ��ڣ�\n");
                        else if(j==OVERFLOW)
                            printf("����ͼ���ʧ�ܣ�����ͼ����������\n");
                        else if(j==ERROR)
                            printf("��������ͼʧ�ܣ�����ͼΪ�ջ������������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 16:
                        printf("�������ɾ��������ͼ���ƣ�");
						scanf("%s",Name);
						j=RemoveGraph(Lists,Name);
						if(j==OK)
							printf("����ͼɾ���ɹ���\n");
						else if(j==ERROR)
							printf("����ͼɾ��ʧ�ܣ��������޴�����ͼ��\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
                    case 17:
                        printf("����������ҵ�����ͼ���ƣ�");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							printf("������ͼλ�ڼ����е� %d λ��\n",j);
						else
							printf("����ͼ����ʧ�ܣ��������޴�����ͼ��\n");
						getchar();
						printf("---���������---\n");
						getchar();
						break;
                    case 18:
                        printf("�����������������ͼ���ƣ�");
						scanf("%s",Name);
						j=LocateGraph(Lists,Name);
						if(j>0)
							SecondaryTable(Lists.elem[j-1].G,op);
						else
						{
							getchar();
							printf("����ͼ�������ڼ����У����ܽ��뵥����ͼ������\n");
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
                printf("     ��ѡ����Ĳ���[0~15]:");
                scanf("%d",&op);
                switch(op){
                    case 1:
                        i=0;
                        VertexType V[30];
                        KeyType VR[100][2];
                        printf("������ͼ�����ж���ؼ��ֺ��ַ��������루-1��null����ֹ��\n");
                        do {
                            scanf("%d%s",&V[i].key,V[i].others);
                        } while(V[i++].key!=-1);
                        i=0;
                        printf("������ͼ�����л������루-1��-1����ֹ��\n");
                        do {
                            scanf("%d%d",&VR[i][0],&VR[i][1]);
                        } while(VR[i++][0]!=-1);
                        j=CreateGraph(G,V,VR);
                        if(j==OK)
                            printf("��������ͼ�ɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("����ͼ���ʧ�ܣ�������ͼ�Ѵ��ڣ�\n");
                        else if(j==ERROR)
                            printf("��������ͼʧ�ܣ�����ͼ�����������\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 2:
                        j=DestroyGraph(G);
                        if(j==OK)
                            printf("��������ͼ�ɹ���\n");
                        else
                            printf("��������ͼʧ�ܣ�����ͼ�����ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 3:
                        printf("����������Ҷ���ؼ��֣�");
                        scanf("%d",&u);
                        j=LocateVex(G,u);
                        if(j==INFEASIBLE)
                            printf("�ؼ���Ϊ %d ���㲻���ڣ�����ʧ�ܣ�\n",u);
                        else
                            printf("���Ҷ���ɹ����ؼ���Ϊ %d �Ķ������ڽӱ������йؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 4:
                        printf("��������Ҫ���¸�ֵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&u);
                        printf("�������¸�ֵ�Ķ���ؼ��ֺ��ַ�����");
                        scanf("%d%s",&value.key,value.others);
                        j=PutVex(G,u,value);
                        if(j==OK)
                            printf("��ֵ�ɹ���\n");
                        else if(j==ERROR)
                            printf("��ֵʧ�ܣ������Ǵ����¸�ֵ�Ĺؼ��ֲ����ڣ���ֵ������ͼ�йؼ����ظ���\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 5:
                        printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&u);
                        j=FirstAdjVex(G,u);
                        if(j==OVERFLOW)
                            printf("��ȡʧ�ܣ��ö������ڽӶ��㣡\n");
                        else if(j==INFEASIBLE)
                            printf("��ȡʧ�ܣ�����ͼ���޴˶��㣡\n");
                        else
                            printf("��ȡ�ɹ����ؼ���Ϊ %d �Ķ���ĵ�һ�ڽӶ���ؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 6:
                        printf("��������Ҫ��ȡ�ڽӵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&u);
                        printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                        scanf("%d",&w);
                        j=NextAdjVex(G,u,w);
                        if(j==ERROR)
                            printf("��ȡʧ�ܣ�w����һ�ڽӶ��㣡\n");
                        else if(j==INFEASIBLE)
                            printf("��ȡʧ�ܣ�v��������ͼ�У�\n");
                        else
                            printf("��ȡ�ɹ�������v���ڽӶ��������w����һ�ڽӶ���Ĺؼ��ֺ��ַ���Ϊ %d %s ��\n",G.vertices[j].data.key,G.vertices[j].data.others);
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 7:
                        printf("��������붥��Ĺؼ��ֺ��ַ�����");
                        scanf("%d%s",&value.key,value.others);
                        j=InsertVex(G,value);
                        if(j==OK)
                            printf("���붥��ɹ���\n");
                        else if(j==OVERFLOW)
                            printf("���붥��ʧ�ܣ����㼯������\n");
                        else if(j==ERROR)
                            printf("���붥��ʧ�ܣ��²��붥��Ĺؼ��������ж���ؼ����ظ���\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 8:
                        printf("������ɾ������Ĺؼ��֣�");
                        scanf("%d",&u);
                        j=DeleteVex(G,u);
                        if(j==OK)
                            printf("ɾ������ɹ���\n");
                        else
                            printf("ɾ������ʧ�ܣ�����ͼΪ�ջ��޴˶��㣡\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 9:
                        printf("����������뻡���������㣺");
                        scanf("%d%d",&u,&w);
                        j=InsertArc(G,u,w);
                        if(j==OK)
                            printf("���뻡�ɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("���뻡ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                        else if(j==ERROR)
                            printf("���뻡ʧ�ܣ�����Ļ��Ѵ��ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 10:
                        printf("�������ɾ�������������㣺");
                        scanf("%d%d",&u,&w);
                        j=DeleteArc(G,u,w);
                        if(j==OK)
                            printf("ɾ�����ɹ���\n");
                        else if(j==INFEASIBLE)
                            printf("ɾ����ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                        else if(j==ERROR)
                            printf("ɾ����ʧ�ܣ���ɾ���Ļ������ڣ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 11:
                        j=DFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n�����������ͼ�ɹ���\n");
                        else
                            printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 12:
                        j=BFSTraverse(G,visit);
                        if(j==OK)
                            printf("\n�����������ͼ�ɹ���\n");
                        else
                            printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 13:
                        printf("������������ļ�·�������ƣ�");
                        scanf("%s",FileName);
                        j=SaveGraph(G,FileName);
                        if(j==OK)
                            printf("����ͼ�浵�ɹ���\n");
                        else if(j==ERROR)
                            printf("����/���ļ�ʧ�ܣ�\n");
                        else
                            printf("����ͼ�浵ʧ�ܣ�����ͼΪ�գ�\n");
                        getchar();
                        printf("---���������---\n");
                        getchar();
                        break;
                    case 14:
                        printf("������������ļ�·�������ƣ�");
                        scanf("%s",FileName);
                        j=LoadGraph(G,FileName);
                        if(j==OK)
                            printf("����ͼ�����ɹ���\n");
                        else if(j==ERROR)
                            printf("���ļ�ʧ�ܣ�\n");
                        else
                            printf("����ͼ����ʧ�ܣ�����ͼ�Ѵ��ڣ�������ʹԭ����ͼ������ʧȥ��\n");
                        getchar();
                        printf("---���������---\n");
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
						printf("---���������---\n");
						getchar();
						break;
                    case 0:
                        break;
                }//end of switch
            }//end of while
        }//end of if
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}

//ջ�ĺ���
void iniStack(stack &S)
//�ú�����ʼ��ջS
{
    S.p = 0;
}
int isEmptyStack(stack &S)
//�ж��ǲ��ǿ�ջ�����򷵻�1�������򷵻�0
{
    if (S.p)
        return 0;
    else
        return 1;
}
int push(stack &S, ElemType e)
//�ú�����Ԫ�ؽ�ջ���ɹ��򷵻�1��ʧ�ܷ���0
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
//�ú�����Ԫ�س�ջ�����س�ջ��Ԫ��ֵ
{
    if (S.p == 0)
        return ERROR;
    else
        return S.elem[S.p--];
}

//���еĺ���
void iniQueue(QUEUE &Q)
//�ú���ʵ�ֳ�ʼ��Q
{
    Q.front = 0;
    Q.length = 0;
}
int isEmptyQueue(QUEUE &Q)
//�ж϶����Ƿ�Ϊ�գ���Ϊ�շ���1�����򷵻�0
{
    if (Q.length)
        return 0;
    else
        return 1;
}
int enQueue(QUEUE &Q, ElemType e)
//��Ԫ��e���Q���ɹ���ջ����1�����򷵻�0
{
    if (Q.length == MAX_VERTEX_NUM)
        return 0;
    Q.elem[(Q.front + Q.length++) % MAX_VERTEX_NUM] = e;
    return 1;
}
int deQueue(QUEUE &Q, ElemType &e)
//��Q����Ԫ�س��ӣ���ֵ��e���ɹ����ӷ���1�����򷵻�0
{
    if (Q.length == 0)
        return 0;
    e = Q.elem[(Q.front++) % MAX_VERTEX_NUM];
    Q.length--;
    return 1;
}

//�˵�����ѡ�� 1 ��������ͼ
status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2]) 
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR���������ͬ�Ĺؼ��֣�����ERROR��*/
{
    int i,j,flag[MAX_KEY]={0};
    ArcNode *tmp;
    if(G.vexnum)
        return INFEASIBLE;
    G.vexnum=G.arcnum=0;
    G.kind=UDG;     //��ʼ������ͼ
    if(V[0].key==-1)
        return ERROR;       //����ͼΪ��
    for(i=0;V[i].key!=-1;i++)
    { //��flag�����Ǵ��ڵĶ���
        if(flag[V[i].key])
        {
            G.vexnum=G.arcnum=0;
            return ERROR;   //�ظ�������ؼ���
        }
        flag[V[i].key]=1;
        G.vexnum++;
        if(G.vexnum>20)
        {//�������������ֵ
            G.vexnum=0;
            return ERROR;
        }   
    }
    for(i=0;V[i].key!=-1;i++)
    {   //Ϊ���㸳ֵ
        G.vertices[i].data.key=V[i].key;
        strcpy(G.vertices[i].data.others,V[i].others);
        G.vertices[i].firstarc=NULL;
    }
    for(i=0;VR[i][0]!=-1;i++)
    {   //�����ڽӱ�
        if(!flag[VR[i][0]]||!flag[VR[i][1]])
        {   //����ıߵĶ��㲻����
            G.vexnum=G.arcnum=0;
            return ERROR;
        }   
        if(VR[i][0]==VR[i][1])
            continue;   //����ı�Ϊ�Ի�
        for(j=0;j<G.vexnum;j++)
        {
            int f[MAX_VERTEX_NUM]={0};
            ArcNode *t=G.vertices[j].firstarc;           
            if(G.vertices[j].data.key==VR[i][0])    //����ߵĶ���˳���������������������մ����ڽӱ�Ľ����һ����
            {
                for(;t;t=t->nextarc)    //����Ѿ������ı�               
                    f[t->adjvex]=1;       
                int k=0;
                while (G.vertices[k].data.key!=VR[i][1])    //�ҵ���һ��������               
                    k++;          
                if(!f[k])
                {//�˱�δ����ʱ���ײ巨������
                    tmp=G.vertices[j].firstarc;
                    G.vertices[j].firstarc=(ArcNode *)malloc(sizeof(ArcNode));
                    G.vertices[j].firstarc->adjvex=k;
                    G.vertices[j].firstarc->nextarc=tmp;
                    G.arcnum++; //����ֻ��Ҫ�ڶ���˳���ĳһ�����������
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

//�˵�����ѡ�� 2 ��������ͼ
status DestroyGraph(ALGraph &G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    if(!G.vexnum)
        return INFEASIBLE;
    ArcNode *tmp1,*tmp2=NULL;
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        tmp1=G.vertices[i].firstarc;
        if(tmp1)    //����һ���㣬��û�б���������������Ҫ����ɾ���߲���
            tmp2=G.vertices[i].firstarc->nextarc;
        for(;tmp1;)
        {//����ɾ��ͷ�����ı�
            //ͨ����������ָ����ƶ�ʵ��ѭ��ɾ���߶���
            G.vertices[i].firstarc=tmp2;
            free(tmp1);
            tmp1=NULL;
            tmp1=tmp2;
            if(tmp2)
                tmp2=tmp2->nextarc;
        }
    }
    G.vexnum=G.arcnum=0;    //���������ͱ�����Ϊ0
    return OK;
}

//�˵�����ѡ�� 3 ���Ҷ���
int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�INFEASIBLE
{
    int i,flag=0;
    for(i=0;i<G.vexnum;i++)
    {//�����������飬�����ҵ������Ҷ���ʱ��ǲ��˳�ѭ��
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

//�˵�����ѡ�� 4 ���㸳ֵ
status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK���������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    int i,v[MAX_KEY]={0};
    for(i=0;i<G.vexnum;i++)
    {//����ѳ��ֹ��Ķ���ؼ���
        v[G.vertices[i].data.key]=1;
    }
    for(i=0;i<G.vexnum;i++)
    {//������������
        if(u==G.vertices[i].data.key)
        {//���ҵ����޸Ķ���
            if(value.key==u||!v[value.key])
            {//���¹ؼ��ֲ������йؼ����ظ������¹ؼ�������޸Ķ���ؼ�����ͬʱ�����и�ֵ����
                G.vertices[i].data.key=value.key;
                strcpy(G.vertices[i].data.others,value.others);
                return OK;
            }
        }
    }
    return ERROR;
}

//�˵�����ѡ�� 5 ��ȡ��һ�ڽӵ�
int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�����������ڽӶ��㣬����ERROR�������㲻��ͼ�У�����INFEASIBLE��
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {//�����������飬���ҵ���u�ؼ�����ͬ�Ķ���
        if(u==G.vertices[i].data.key&&G.vertices[i].firstarc)   //�������ڽӶ���
            return G.vertices[i].firstarc->adjvex;
        else if(u==G.vertices[i].data.key)  //�������ڽӶ���
            return OVERFLOW;
    }
    return INFEASIBLE;
}

//�˵�����ѡ�� 6 ��ȡ��һ�ڽӵ�
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����v��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲����ڽӶ���ʧ�ܷ���ERROR�����Ҷ���ʧ�ܷ���INFEASIBLE
{
    for(int i=0;i<G.vexnum;i++)
    {
        if(v==G.vertices[i].data.key)
        {
            ArcNode *tmp=G.vertices[i].firstarc;
            for(;tmp;tmp=tmp->nextarc)
                if(w==G.vertices[tmp->adjvex].data.key&&tmp->nextarc)
                    return tmp->nextarc->adjvex;
            return ERROR;  //�����ڽӶ���ʧ��
        }
    }
    return INFEASIBLE;  //���Ҷ���ʧ��
}

//�˵�����ѡ�� 7 ���붥��
status InsertVex(ALGraph &G,VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    int i,flag[MAX_KEY]={0};
    if(G.vexnum==MAX_VERTEX_NUM)
        return OVERFLOW;   //���㼯����
    for(i=0;i<G.vexnum;i++)
    {//��ǳ��ֹ��Ĺؼ���
        flag[G.vertices[i].data.key]=1;
    }
    if(!flag[v.key])
    {//�ؼ��ֲ��ظ������������㣬���򱨴�
        G.vertices[i].data.key=v.key;
        strcpy(G.vertices[i].data.others,v.others);
        G.vertices[i].firstarc=NULL;
        G.vexnum++;
        return OK;
    }
    else
        return ERROR;
}

//�˵�����ѡ�� 8 ɾ������
status DeleteVex(ALGraph &G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    int a=-1,flag[MAX_KEY]={0};
    for(int i=0;i<G.vexnum;i++)
        flag[G.vertices[i].data.key]=1;
    if(!flag[v]||!G.vexnum)
        return ERROR;//ͼ���޶��㣨��ͼ�����޶�Ӧ�ؼ��ֵĶ���ʱ������ERROR
    else
    {
        for(int i=0;i<G.vexnum;i++)
        {
            if(v==G.vertices[i].data.key)
            {//���ҵ��ؼ��ֶ�Ӧ�Ķ���ʱ�������ڽӱ��еĻ�ȫ��ɾ��
                for(ArcNode *tmp1=G.vertices[i].firstarc;tmp1;)
                {
                    G.vertices[i].firstarc=tmp1->nextarc;
                    ArcNode *tmp2=tmp1;
                    tmp1=tmp1->nextarc;
                    free(tmp2);
                    tmp2=NULL;
                    G.arcnum--;
                }
                a=i;    //a���ڼ�¼��ɾ�������λ�򣬱��ں����޸��ڽӱ�
            }
            else
            {//���ǹؼ��ֶ�Ӧ�Ķ���ʱ�������ڽӱ�����ؼ��ֶ�����صĻ���ɾ��
                for(ArcNode *tmp1=G.vertices[i].firstarc;tmp1;tmp1=tmp1->nextarc)
                {//����ͼͷ��㣬�ؼ��ֶ�Ӧ�ڵ�һ�ڽӵ��������ʱҪ�ֿ�����
                    //ʹ��tmp1��tmp2��������ָ����ж���ɾ������
                    ArcNode *tmp2;
                    if(G.vertices[G.vertices[i].firstarc->adjvex].data.key==v)
                    {//�ؼ��ֶ�Ӧ�ڵ�һ�ڽӵ�
                        tmp2=G.vertices[i].firstarc;
                        G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
                        free(tmp2);
                        tmp2=NULL;
                        break;
                    }
                    else if(tmp1->nextarc&&G.vertices[tmp1->nextarc->adjvex].data.key==v)
                    {//�ؼ��ֶ�Ӧ�ڳ���һ�ڽӵ������������
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
        {//�ڶ���������ɾ�����㣬���޸����λ��Ķ������ڽӱ��е�λ��ֵ
            if(v==G.vertices[i].data.key)
            {
                for(int j=i;j<G.vexnum-1;j++)
                    G.vertices[j]=G.vertices[j+1];
                for(ArcNode *t=G.vertices[i].firstarc;t;t=t->nextarc)
                {//�ڶ�����������λ��Ҫ�Բ��䵽ԭɾ������λ�õĶ�����ڽӱ�����޸�
                    if(t->adjvex>a)
                        t->adjvex-=1;   //ɾ���������λ��Ķ������ڽӱ���λ���һ
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

//�˵�����ѡ�� 9 ���뻡
status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int i,a,b,flag[MAX_KEY]={0};
    for(i=0;i<G.vexnum;i++)
    {//���ͼ�����ж��㣻��a��b��¼�����뻡����������
        flag[G.vertices[i].data.key]=1;
        if(G.vertices[i].data.key==v)
            a=i;
        if(G.vertices[i].data.key==w)
            b=i;
    }
    if(a==b)    //�����뻡Ϊ�Ի�ʱ�������в���
        return OK;
    if(!flag[v]||!flag[w])  //�����뻡����һ���㲻��ͼ��ʱ������ERROR
        return INFEASIBLE;
    for(i=0;i<G.vexnum;i++)
    {//�ֱ����v��w��Ӧ�Ķ��㣬�����ڽӱ����ײ巨���뻡
        if(v==G.vertices[i].data.key)
        {
            ArcNode *tmp=G.vertices[i].firstarc;
            for(;tmp;tmp=tmp->nextarc)  //�жϴ�����Ļ��Ƿ��Ѿ����ڣ������򷵻�ERROR
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

//�˵�����ѡ�� 10 ɾ����
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int i,a,b,flag[MAX_KEY]={0};
    for(i=0;i<G.vexnum;i++)
    {//���ͼ�����ж��㣻��a��b��¼��ɾ��������������
        flag[G.vertices[i].data.key]=1;
        if(v==G.vertices[i].data.key)
            a=i;
        if(w==G.vertices[i].data.key)
            b=i;
    }
    if(!flag[v]||!flag[w])  //��ɾ��������һ���㲻��ͼ��ʱ������ERROR
        return INFEASIBLE;
    for(i=0;i<G.vexnum;i++)
    {
        if(v==G.vertices[i].data.key)
        {//�ֱ����v��w��Ӧ�Ķ��㣬�����ڽӱ��н���ɾ��������
            ArcNode *tmp1=G.vertices[i].firstarc;
            int pt=0;   //pt���ڱ�Ǵ�ɾ�����Ƿ���ڣ��������򷵻�ERROR
            for(;tmp1;tmp1=tmp1->nextarc)
                if(tmp1->adjvex==b)
                {
                    pt=1;
                    break;
                }    
            if(pt)
            {//����ͼͷ��㣬�ؼ��ֶ�Ӧ�ڵ�һ�ڽӵ��������ʱҪ�ֿ�����
                //ʹ��tmp1��tmp2��������ָ����л�ɾ������
                if(G.vertices[i].firstarc->adjvex==b)
                {//�ؼ��ֶ�Ӧ�ڵ�һ�ڽӵ�
                    tmp1=G.vertices[i].firstarc->nextarc;
                    ArcNode *tmp2=G.vertices[i].firstarc;
                    G.vertices[i].firstarc=tmp1;
                    free(tmp2);
                    tmp2=NULL;
                }
                else
                {//�ؼ��ֶ�Ӧ�ڳ���һ�ڽӵ������������
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

//���ѵĸ������������ڵݹ����
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
//�˵�����ѡ�� 11 ���������������
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    if(!G.vexnum)//��ͼ
        return ERROR;
    int visited[MAX_VERTEX_NUM]={0};
    for(int i=0;i<G.vexnum;i++)
        if(!visited[i])
            DFS(G.vertices,i,visited,visit); 
    return OK;
}

//�˵�����ѡ�� 12 ���������������
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    if (G.vexnum==0) //��ͼ
        return ERROR;
    QUEUE Q;
    int visited[G.vexnum]={0};  //�����Ǹ������Ƿ񱻷��ʹ�
    iniQueue(Q);
    for(int i=0;i<G.vexnum;i++)
    {//������ȱ���ÿһ����ͨ��ͼ
        if(!visited[i])
        {//�����ǰ���㲻�ڱ�����������ͨ��ͼ��
            visited[i]=1;
            visit(G.vertices[i].data);
            enQueue(Q,i);
            while(!isEmptyQueue(Q))
            {//���зǿ�ʱѭ��
                deQueue(Q,i);
                ArcNode *q=G.vertices[i].firstarc;
                for(;q!=NULL;q=q->nextarc)
                {//���ν���ǰ���������δ���ʹ����ڽӵ�����У������Ϊ�ѷ���
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

//�˵�����ѡ�� 13 ����ͼ�浵
status SaveGraph(ALGraph G, char FileName[])
//��ͼ������д�뵽�ļ�FileName��
{
    FILE *fp;
    if(!G.vexnum)
        return INFEASIBLE;
    if (!(fp = fopen(FileName, "wb")))
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    { //д��ÿһ������
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc)
        { //˳��д��ö����ÿһ���ڽӵ��λ��
            fprintf(fp, "%d ", p->adjvex);
        }
        fprintf(fp, "%d ", -1); //�ڽӵ��β��д��-1
    }
    fprintf(fp, "%d %s ", -1, "nil"); //�����β��д��-1
    fclose(fp);
    return OK;
}

//�˵�����ѡ�� 14 ����ͼ����
status LoadGraph(ALGraph &G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
//����������ջ�����ݽṹ�����������
{
    if (G.vexnum > 0)
        return  INFEASIBLE;
    FILE *fp;
    if (!(fp = fopen(FileName, "rb")))
        return ERROR;
    G.vexnum = G.arcnum = 0;
    KeyType key;          //�洢���ļ��ж�ȡ����keyֵ����ʱ����
    int ConnectVerLocate; //�洢��ȡ�Ķ����ڽӵ��λ�õ���ʱ����
    char others[20];      //�洢��ȡ�Ķ����data��others��������ʱ����
    stack S;              //����ջ
    iniStack(S);
    fscanf(fp, "%d ", &key);
    fscanf(fp, "%s ", others);
    for (int i = 0; key != -1 && G.vexnum < MAX_VERTEX_NUM; i++)
    { //��������
        G.vertices[i].data.key = key;
        strcpy(G.vertices[i].data.others, others);
        G.vertices[i].firstarc = NULL;
        fscanf(fp, "%d ", &ConnectVerLocate);
        for (; ConnectVerLocate != -1;)
        { //����������ڽӱ�
            //ͨ����ջ��ջ��˳���ã�ȷ����ȡ�󶥵��ڽӱ�˳����ԭͼ��ͬ
            push(S, ConnectVerLocate);
            fscanf(fp, "%d ", &ConnectVerLocate);
        }
        for (ArcNode *p; !isEmptyStack(S);)
        {                              //ջ��Ϊ��ʱѭ��
            ConnectVerLocate = pop(S); //��ջ
            //���ڽӱ�ͷ�������ڽӵ���
            p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = ConnectVerLocate;
            p->nextarc = G.vertices[i].firstarc;
            G.vertices[i].firstarc = p;
            G.arcnum++; //ͼ�ı�������
        }
        G.vexnum++;                        //ͼ�Ķ���������
        fscanf(fp, "%d %s", &key, others); //��ȡ��һ����
    }
    G.arcnum/=2;
    fclose(fp);
    return OK;
}

//�˵�����ѡ�� 15 ������ͼ����֮��������ͼ 
status AddGraph(LISTS &Lists,char ListName[])
// ��Lists������һ������ΪListName������ͼ��
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
            VertexType V[30];   //����ͼΪ��ʱ�൱��ͼ�����ڣ�����ͼʱ����ͼ������Ԫ��
            KeyType VR[100][2];
            int i=0,j;
            printf("������ͼ�����ж���ؼ��ֺ��ַ��������루-1��null����ֹ��\n");
            do {
                scanf("%d%s",&V[i].key,V[i].others);
            } while(V[i++].key!=-1);
            i=0;
            printf("������ͼ�����л������루-1��-1����ֹ��\n");
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

//�˵�����ѡ�� 16 ������ͼ����֮ɾ������ͼ 
status RemoveGraph(LISTS &Lists,char ListName[])
// ��Lists��ɾ��һ������ΪListName������ͼ�� 
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

//�˵�����ѡ�� 17 ������ͼ����֮��������ͼ 
int LocateGraph(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName������ͼ�����ҳɹ������߼���ţ����򷵻�ERROR�� 
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

//��������������ͼ����
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

//������������������˵�
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
        printf("     ��ѡ����Ĳ���[0~15]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                i=0;
                VertexType V[30];
                KeyType VR[100][2];
                printf("������ͼ�����ж���ؼ��ֺ��ַ��������루-1��null����ֹ��\n");
                do {
                    scanf("%d%s",&V[i].key,V[i].others);
                } while(V[i++].key!=-1);
                i=0;
                printf("������ͼ�����л������루-1��-1����ֹ��\n");
                do {
                    scanf("%d%d",&VR[i][0],&VR[i][1]);
                } while(VR[i++][0]!=-1);
                j=CreateGraph(G,V,VR);
                if(j==OK)
                    printf("��������ͼ�ɹ���\n");
                else if(j==INFEASIBLE)
                    printf("����ͼ���ʧ�ܣ�������ͼ�Ѵ��ڣ�\n");
                else if(j==ERROR)
                    printf("��������ͼʧ�ܣ�����ͼ�����������\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 2:
                j=DestroyGraph(G);
                if(j==OK)
                    printf("��������ͼ�ɹ���\n");
                else
                    printf("��������ͼʧ�ܣ�����ͼ�����ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 3:
                printf("����������Ҷ���ؼ��֣�");
                scanf("%d",&u);
                j=LocateVex(G,u);
                if(j==INFEASIBLE)
                    printf("�ؼ���Ϊ %d ���㲻���ڣ�����ʧ�ܣ�\n",u);
                else
                    printf("���Ҷ���ɹ����ؼ���Ϊ %d �Ķ������ڽӱ������йؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 4:
                printf("��������Ҫ���¸�ֵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&u);
                printf("�������¸�ֵ�Ķ���ؼ��ֺ��ַ�����");
                scanf("%d%s",&value.key,value.others);
                j=PutVex(G,u,value);
                if(j==OK)
                    printf("��ֵ�ɹ���\n");
                else if(j==ERROR)
                    printf("��ֵʧ�ܣ������Ǵ����¸�ֵ�Ĺؼ��ֲ����ڣ���ֵ������ͼ�йؼ����ظ���\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 5:
                printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&u);
                j=FirstAdjVex(G,u);
                if(j==OVERFLOW)
                    printf("��ȡʧ�ܣ��ö������ڽӶ��㣡\n");
                else if(j==INFEASIBLE)
                    printf("��ȡʧ�ܣ�����ͼ���޴˶��㣡\n");
                else
                    printf("��ȡ�ɹ����ؼ���Ϊ %d �Ķ���ĵ�һ�ڽӶ���ؼ��ֺ��ַ���Ϊ %d %s ��\n",u,G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 6:
                printf("��������Ҫ��ȡ�ڽӵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&u);
                printf("��������Ҫ��ȡ��һ�ڽӵ�Ķ���Ĺؼ��֣�");
                scanf("%d",&w);
                j=NextAdjVex(G,u,w);
                if(j==ERROR)
                    printf("��ȡʧ�ܣ�w����һ�ڽӶ��㣡\n");
                else if(j==INFEASIBLE)
                    printf("��ȡʧ�ܣ�v��������ͼ�У�\n");
                else
                    printf("��ȡ�ɹ�������v���ڽӶ��������w����һ�ڽӶ����λ��Ϊ %d %s ��\n",G.vertices[j].data.key,G.vertices[j].data.others);
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 7:
                printf("��������붥��Ĺؼ��ֺ��ַ�����");
                scanf("%d%s",&value.key,value.others);
                j=InsertVex(G,value);
                if(j==OK)
                    printf("���붥��ɹ���\n");
                else if(j==OVERFLOW)
                    printf("���붥��ʧ�ܣ����㼯������\n");
                else if(j==ERROR)
                    printf("���붥��ʧ�ܣ��²��붥��Ĺؼ��������ж���ؼ����ظ���\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 8:
                printf("������ɾ������Ĺؼ��֣�");
                scanf("%d",&u);
                j=DeleteVex(G,u);
                if(j==OK)
                    printf("ɾ������ɹ���\n");
                else
                    printf("ɾ������ʧ�ܣ�����ͼΪ�ջ��޴˶��㣡\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 9:
                printf("����������뻡���������㣺");
                scanf("%d%d",&u,&w);
                j=InsertArc(G,u,w);
                if(j==OK)
                    printf("���뻡�ɹ���\n");
                else if(j==INFEASIBLE)
                    printf("���뻡ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                else if(j==ERROR)
                    printf("���뻡ʧ�ܣ�����Ļ��Ѵ��ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 10:
                printf("�������ɾ�������������㣺");
                scanf("%d%d",&u,&w);
                j=DeleteArc(G,u,w);
                if(j==OK)
                    printf("ɾ�����ɹ���\n");
                else if(j==INFEASIBLE)
                    printf("ɾ����ʧ�ܣ�����Ļ����㲻������ͼ�У�\n");
                else if(j==ERROR)
                    printf("ɾ����ʧ�ܣ���ɾ���Ļ������ڣ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 11:
                j=DFSTraverse(G,visit);
                if(j==OK)
                    printf("\n�����������ͼ�ɹ���\n");
                else
                    printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 12:
                j=BFSTraverse(G,visit);
                if(j==OK)
                    printf("\n�����������ͼ�ɹ���\n");
                else
                    printf("\n����ͼʧ�ܣ�ͼΪ�գ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 13:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=SaveGraph(G,FileName);
                if(j==OK)
                    printf("����ͼ�浵�ɹ���\n");
                else if(j==ERROR)
                    printf("����/���ļ�ʧ�ܣ�\n");
                else
                    printf("����ͼ�浵ʧ�ܣ�����ͼΪ�գ�\n");
                getchar();
                printf("---���������---\n");
                getchar();
                break;
            case 14:
                printf("������������ļ�·�������ƣ�");
                scanf("%s",FileName);
                j=LoadGraph(G,FileName);
                if(j==OK)
                    printf("����ͼ�����ɹ���\n");
                else if(j==ERROR)
                    printf("���ļ�ʧ�ܣ�\n");
                else
                    printf("����ͼ����ʧ�ܣ�����ͼ�Ѵ��ڣ�������ʹԭ����ͼ������ʧȥ��\n");
                getchar();
                printf("---���������---\n");
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
                printf("---���������---\n");
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
}