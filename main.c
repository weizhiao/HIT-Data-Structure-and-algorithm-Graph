#include<stdio.h>
#include<stdlib.h>

int visited[20];//��¼�����Ƿ񱻷���
int dfn[20];//���������Ż����ȹ���
int count;
FILE* fp1, * fp2;//���ڴ洢������

//ͼ���ڽӾ���洢�ṹ
struct mtgraph
{
    int type;
    int n, e;//�������ͱ���
    int* edge;//�ڽӾ���
    char* verlist;
};

//�߱���
struct edgenode
{
    int adjvex;//�������
    struct edgenode* next;
};

//�������
struct vertexnode
{
    char vertex;
    struct edgenode* firstedge;//�߱�
};

//ͼ���ڽӱ�洢�ṹ
struct adjgraph
{
    int n, e;
    int type;//����
    struct vertexnode* vexlist;//�����
};

//ջ
struct stack
{
    int data;
    struct stack* next;
};

//���н��
struct queuenode
{
    int data;
    struct queuenode* next;
};

//����
struct queue
{
    struct queuenode* front;//ͷָ��
    struct queuenode* rear;//βָ��
};

//������
typedef struct mtgraph* MTGraph;
typedef struct adjgraph* AdjGraph;
typedef struct edgenode* EdgeNode;
typedef struct stack* Stack;
typedef struct queue* Queue;
typedef struct queuenode* Queuenode;

void PrintMTGraphDfn(MTGraph G);//��ӡ�ڽӾ���ı������
void PrintAdjGraphDfn(AdjGraph G);//��ӡ�ڽӱ�ı������
void ShowMenu();//��ʾ�˵�
Stack MakeStackNull();//������ջ
void Push(int i, Stack S);//ѹջ
void Pop(Stack S);//��ջ
int Top(Stack S);//����ջ��Ԫ��
int IsEmptyStack(Stack S);//�ж�ջ�Ƿ�Ϊ��
Queue MakeQueueNull();//�����ն���
void EnQueue(int i, Queue Q);//���
void DeQueue(Queue Q);//����
int Front(Queue Q);//���ض���Ԫ��
int IsEmptyQueue(Queue Q);//�ж϶����Ƿ�Ϊ��
void DFSAdjGraph(int i, AdjGraph G);//�ڽӱ�����ѵ��Ӻ���
void DFSMTGraph(int i, MTGraph G);//�ڽӾ�������ѵ��Ӻ���
void DFSMTGraphTraverse(MTGraph G);//�ڽӾ������ѵ����㷨
void DFSAdjGraphTraverse(AdjGraph G);//�ڽӱ����ѵ����㷨
void BFSAdjGraph(int i, AdjGraph G);//�ڽӱ���ѵ��Ӻ���
void BFSMTGraph(int i, MTGraph G);//�ڽӾ�����ѵ��Ӻ���
void BFSMTGraphTraverse(MTGraph G);//�ڽӾ�����ѵ����㷨
void BFSAdjGraphTraverse(AdjGraph G);//�ڽӱ���ѵ����㷨
void CreateMTGraph(MTGraph G);//����ͼ���ڽӾ���
void CreateAdjGraph(AdjGraph G);//����ͼ���ڽӱ�
AdjGraph MTGraphToAdjGraph(MTGraph G);//���ڽӾ���ת��Ϊ�ڽӱ�
MTGraph AdjGraphToMTGraph(AdjGraph G);//���ڽӱ�ת��Ϊ�ڽӾ���
int FindMTCode(char ch, char* str);//�ҵ��ڽӾ���Ķ�����
int FindAdjCode(char ch, AdjGraph G);//�ҵ��ڽӱ�Ķ�����

int main()
{
    AdjGraph G1 = malloc(sizeof(struct adjgraph));
    MTGraph G2 = malloc(sizeof(struct mtgraph));
    while (1) {
        int ch;
        ShowMenu();
        while (scanf("%d", &ch) != 1) {
            printf("����������������룡\n");
            fflush(stdin);
        }
        switch (ch) {//ʹ��switch�����й���ѡ��
        case 0:system("pause");
            return 0;
        case 1:
            CreateAdjGraph(G1);
            system("pause");
            system("cls");
            break;
        case 2:
            CreateMTGraph(G2);
            system("pause");
            system("cls");
            break;
        case 3:
            G2 = AdjGraphToMTGraph(G1);
            system("pause");
            system("cls");
            break;
        case 4:
            G1 = MTGraphToAdjGraph(G2);
            system("pause");
            system("cls");
            break;
        case 5:
            DFSAdjGraphTraverse(G1);
            PrintAdjGraphDfn(G1);
            system("pause");
            system("cls");
            break;
        case 6:
            DFSMTGraphTraverse(G2);
            PrintMTGraphDfn(G2);
            system("pause");
            system("cls");
            break;
        case 7:
            BFSAdjGraphTraverse(G1);
            PrintAdjGraphDfn(G1);
            system("pause");
            system("cls");
            break;
        case 8:
            BFSMTGraphTraverse(G2);
            PrintMTGraphDfn(G2);
            system("pause");
            system("cls");
            break;
        }
    }
}

void PrintAdjGraphDfn(AdjGraph G) {
    char* str = malloc(sizeof(char) * (G->n + 1));
    for (int i = 0; i < G->n; i++) {
        printf("���㣺%c ���ȱ�ţ�%d\n", G->vexlist[i].vertex, dfn[i]);
        str[dfn[i]] = G->vexlist[i].vertex;//����Ž���������ַ���
    }
    printf("��������Ϊ:");
    for (int i = 1; i <= G->n; i++) {
        printf("%c ", str[i]);
    }
    printf("\n");
}

void PrintMTGraphDfn(MTGraph G) {
    char* str = malloc(sizeof(char) * (G->n + 1));
    for (int i = 0; i < G->n; i++) {
        printf("���㣺%c ���ȱ�ţ�%d\n", G->verlist[i], dfn[i]);
        str[dfn[i]] = G->verlist[i];//����Ž���������ַ���
    }
    printf("��������Ϊ:");
    for (int i = 1; i <= G->n; i++) {
        printf("%c ", str[i]);
    }
    printf("\n");
}

//��ʾ�˵�
void ShowMenu() {
    printf("---------------------------------\n");
    printf("1������ͼ���ڽӱ�\n");
    printf("2������ͼ���ڽӾ���\n");
    printf("3����ͼ���ڽӱ�ת��Ϊ�ڽӾ���\n");
    printf("4����ͼ���ڽӾ���ת��Ϊ�ڽӱ�\n");
    printf("5���������ͼ(�ڽӱ�)\n");
    printf("6���������ͼ(�ڽӾ���)\n");
    printf("7���������ͼ(�ڽӱ�)\n");
    printf("8���������ͼ(�ڽӾ���)\n");
    printf("0���˳�\n");
    printf("---------------------------------\n");
}

//�ж϶����Ƿ�Ϊ��
int IsEmptyQueue(Queue Q)
{
    if (Q->front == Q->rear)
    {
        return 1;
    }
    return 0;
}

Queue MakeQueueNull()
{
    Queue Q = malloc(sizeof(struct queue));//����ͷ�ڵ�
    Q->front = malloc(sizeof(struct queuenode));
    Q->front->next = NULL;
    Q->rear = Q->front;
    return Q;
}

//�Ӷ�β����
void EnQueue(int i, Queue Q)
{
    Queuenode temp = malloc(sizeof(struct queuenode));
    temp->data = i;
    Q->rear->next = temp;
    Q->rear = temp;
}

//�Ӷ��׳���
void DeQueue(Queue Q)
{
    if (Q->rear == Q->front->next) {
        Q->rear = Q->front;
    }
    Queuenode temp = Q->front->next;
    Q->front->next = temp->next;
    free(temp);
}

int Front(Queue Q)
{
    return Q->front->next->data;
}

int IsEmptyStack(Stack S)
{
    if (S->next == NULL)
    {
        return 1;
    }
    return 0;
}

Stack MakeStackNull()
{
    Stack S = malloc(sizeof(struct stack));//��ͷ�ڵ�
    S->next = NULL;
    return S;
}

void Push(int i, Stack S)
{
    Stack temp = malloc(sizeof(struct stack));//ͷ�巨
    temp->data = i;
    temp->next = S->next;
    S->next = temp;
}

void Pop(Stack S)
{
    Stack temp = S->next;
    S->next = temp->next;
    free(temp);
}

int Top(Stack S)
{
    return S->next->data;
}

int FindMTCode(char ch, char* str)
{
    for (int i = 0; str[i] != '\0'; i++)//���ַ���ɨ��һ��
    {
        if (ch == str[i])
        {
            return i;
        }
    }
    return -1;
}

int FindAdjCode(char ch, AdjGraph G)
{
    for (int i = 0; i < G->n; i++)
    {
        if (ch == G->vexlist[i].vertex)
        {
            return i;
        }
    }
    return -1;
}

void CreateMTGraph(MTGraph G)
{
    FILE* fp;
    fp = fopen("Graph.txt", "r");//�����ļ���ȡ
    char ch;
    char temp[10];
    int i;
    while ((ch = fgetc(fp)) != ',')
    {
        G->type = ch - '0';
    }
    if (G->type == 0) {
        printf("ͼ������Ϊ:����ͼ\n");
    }
    else {
        printf("ͼ������Ϊ:����ͼ\n");
    }
    for (i = 0; (ch = fgetc(fp)) != ','; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->n = atoi(temp);//���ַ���ת��Ϊ����
    printf("ͼ�Ķ�����Ϊ:%d\n", G->n);
    for (i = 0; (ch = fgetc(fp)) != '\n'; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->e = atoi(temp);//���ַ���ת��Ϊ����
    printf("ͼ�ı���Ϊ:%d\n", G->e);
    G->verlist = malloc(sizeof(char) * (G->n + 1));
    G->edge = malloc(sizeof(int) * G->n * G->n);
    for (int i = 0; i < G->n; i++)
    {
        for (int j = 0; j < G->n; j++)
        {
            G->edge[i * G->n + j] = 0;
        }
    }
    i = 0;
    printf("ͼ�Ķ���Ϊ:");
    while ((ch = fgetc(fp)) != '\n')
    {
        printf("%c ", ch);
        G->verlist[i++] = ch;
    }
    G->verlist[i] = '\0';
    if (i != G->n)//�жϽ����Ƿ���ȷ
    {
        printf("ͼ�Ķ�������ʵ�ʲ���!\n");
        exit(0);
    }
    printf("\n");
    printf("ͼ�ı�Ϊ:\n");
    for (int i = 0; i < G->e; i++)
    {
        int v[2];
        int k = 0;
        while ((ch = fgetc(fp)) != ')')//����")"����
        {
            if (ch != ',' && ch != '(')
            {
                v[k++] = FindMTCode(ch, G->verlist);
            }
        }
        printf("(%c,%c)\n", G->verlist[v[0]], G->verlist[v[1]]);//�����
        if (G->type == 0)//����ͼ
        {
            G->edge[v[0] * G->n + v[1]] = 1;
            G->edge[v[1] * G->n + v[0]] = 1;
        }
        else//����ͼ
        {
            G->edge[v[0] * G->n + v[1]] = 1;
        }
    }
    fclose(fp);//�ر��ļ�
}

void CreateAdjGraph(AdjGraph G)
{
    FILE* fp;
    fp = fopen("Graph.txt", "r");
    char ch;
    char temp[10];
    int i;
    while ((ch = fgetc(fp)) != ',')
    {
        G->type = ch - '0';
    }
    if (G->type == 0) {
        printf("ͼ������Ϊ:����ͼ\n");
    }
    else {
        printf("ͼ������Ϊ:����ͼ\n");
    }
    for (i = 0; (ch = fgetc(fp)) != ','; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->n = atoi(temp);//���ַ���ת��Ϊ����
    printf("ͼ�Ķ�����Ϊ:%d\n", G->n);
    for (i = 0; (ch = fgetc(fp)) != '\n'; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->e = atoi(temp);//���ַ���ת��Ϊ����
    printf("ͼ�ı���Ϊ:%d\n", G->e);
    G->vexlist = malloc(sizeof(struct vertexnode) * G->n);
    i = 0;
    printf("ͼ�Ķ���Ϊ:");
    while ((ch = fgetc(fp)) != '\n')
    {
        printf("%c ", ch);
        G->vexlist[i].firstedge = NULL;
        G->vexlist[i++].vertex = ch;
    }
    printf("\n");
    if (i != G->n)
    {
        printf("ͼ�Ķ�������ʵ�ʲ���!\n");
        exit(0);
    }
    printf("ͼ�ı�Ϊ:\n");
    for (int i = 0; i < G->e; i++)
    {
        int v[2];
        int k = 0;
        while ((ch = fgetc(fp)) != ')')
        {
            if (ch != ',' && ch != '(')
            {
                v[k++] = FindAdjCode(ch, G);
            }
        }
        printf("(%c,%c)\n", G->vexlist[v[0]].vertex, G->vexlist[v[1]].vertex);
        if (G->type == 0)//�˴�����ͷ�巨
        {
            EdgeNode tempnode1 = malloc(sizeof(struct edgenode));
            tempnode1->adjvex = v[1];
            tempnode1->next = G->vexlist[v[0]].firstedge;
            G->vexlist[v[0]].firstedge = tempnode1;
            EdgeNode tempnode2 = malloc(sizeof(struct edgenode));
            tempnode2->adjvex = v[0];
            tempnode2->next = G->vexlist[v[1]].firstedge;
            G->vexlist[v[1]].firstedge = tempnode2;
        }
        else
        {
            EdgeNode tempnode3 = malloc(sizeof(struct edgenode));
            tempnode3->adjvex = v[1];
            tempnode3->next = G->vexlist[v[0]].firstedge;
            G->vexlist[v[0]].firstedge = tempnode3;
        }
    }
    fclose(fp);//�ر��ļ�
}

AdjGraph MTGraphToAdjGraph(MTGraph G)
{
    AdjGraph G1 = malloc(sizeof(struct adjgraph));
    G1->e = G->e;
    G1->n = G->n;
    G1->type = G->type;
    G1->vexlist = malloc(sizeof(struct vertexnode) * G->n);
    for (int i = 0; i < G->n; i++)
    {
        G1->vexlist[i].vertex = G->verlist[i];
        G1->vexlist[i].firstedge = NULL;
        for (int j = 0; j < G->n; j++)
        {
            if (G->edge[i * G->n + j] == 1)//��ȡ�ڽӾ���
            {
                EdgeNode temp = malloc(sizeof(struct edgenode));
                temp->adjvex = j;
                temp->next = G1->vexlist[i].firstedge;
                G1->vexlist[i].firstedge = temp;
            }
        }
    }
    printf("ת���ɹ���\n");
    return G1;
}

MTGraph AdjGraphToMTGraph(AdjGraph G)
{
    MTGraph G1 = malloc(sizeof(struct mtgraph));
    G1->e = G->e;
    G1->n = G->n;
    G1->type = G->type;
    G1->verlist = malloc(sizeof(char) * G->n);
    G1->edge = malloc(sizeof(int) * G->n * G->n);
    for (int i = 0; i < G->n; i++)
    {
        for (int j = 0; j < G->n; j++)
        {
            G1->edge[i * G->n + j] = 0;
        }
    }
    for (int i = 0; i < G->n; i++)
    {
        G1->verlist[i] = G->vexlist[i].vertex;
        EdgeNode p = G->vexlist[i].firstedge;
        while (!p)
        {
            G1->edge[i * G->n + p->adjvex] = 1;//1�����б�
            p = p->next;
        }
    }
    printf("ת���ɹ���\n");
    return G1;
}

void DFSMTGraphTraverse(MTGraph G)
{
    for (int i = 0; i < G->n; i++)//���г�ʼ��
    {
        visited[i] = 0;
    }
    count = 1;//��Ŵ�1��ʼ
    for (int i = 0; i < G->n; i++)
    {
        if (visited[i] == 0)//�ж��Ƿ���ʹ�
        {
            visited[i] = 1;//���
            dfn[i] = count++;//���
            DFSMTGraph(i, G);
        }
    }
}

//��������ĵݹ��㷨
/*
void DFSAdjGraph(int i,AdjGraph G)
{
    printf("%c ",G->vexlist[i].vertex);
    EdgeNode p=G->vexlist[i].firstedge;
    while(p)
    {
        if(visited[p->adjvex]==0)
        {
            visited[p->adjvex]=1;
            dfn[p->adjvex]=count++;
            DFSAdjGraph(p->adjvex,G);
        }
        p=p->next;
    }
}
*/

//��������ĵݹ��㷨
void DFSAdjGraph(int i, AdjGraph G) {
    Stack S = MakeStackNull();
    Push(i, S);
    while (!IsEmptyStack(S)) {//��ջΪ��ʱ����
        int k = Top(S);
        EdgeNode p = G->vexlist[k].firstedge;
        while (p) {
            if (visited[p->adjvex] == 0) {//д���
                fprintf(fp2, "(%c,%c)\n", G->vexlist[k].vertex, G->vexlist[p->adjvex].vertex);
                Push(p->adjvex, S);
                visited[p->adjvex] = 1;
                dfn[p->adjvex] = count++;
                break;
            }
            p = p->next;
        }
        if (p == NULL) {
            Pop(S);
        }
    }
}

void DFSAdjGraphTraverse(AdjGraph G)
{
    fp2 = fopen("DFSTraverse.txt", "w");//��д�ķ�ʽ���ļ�
    fprintf(fp2, "����Ϊ:\n");
    for (int i = 0; i < G->n; i++) {
        fprintf(fp2, "%c ", G->vexlist[i].vertex);
    }
    fprintf(fp2, "\n");
    fprintf(fp2, "��Ϊ��\n");
    for (int i = 0; i < G->n; i++)
    {
        visited[i] = 0;
    }
    count = 1;
    for (int i = 0; i < G->n; i++)
    {
        if (visited[i] == 0)
        {
            visited[i] = 1;
            dfn[i] = count++;
            DFSAdjGraph(i, G);
        }
    }
    fclose(fp2);
}

//��ȱ����ĵݹ��㷨
/*
void DFSMTGraph(int i,MTGraph G)
{
    printf("%c ",G->verlist[i]);
    for(int j=0; j<G->n; j++)
    {
        if(G->edge[i*G->n+j]==1&&visited[j]==0)
        {
            visited[j]=1;
            dfn[j]=count++;
            DFSMTGraph(j,G);
        }
    }
}
*/

//��������ķǵݹ��㷨
void DFSMTGraph(int i, MTGraph G)
{
    Stack S = MakeStackNull();
    Push(i, S);
    int flag;//��������Ƿ񵽴����
    while (!IsEmptyStack(S))
    {
        int k = Top(S);
        flag = 0;
        for (int j = 0; j < G->n; j++)
        {
            if (G->edge[k * G->n + j] == 1 && visited[j] == 0)
            {
                visited[j] = 1;
                dfn[j] = count++;
                Push(j, S);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            Pop(S);
        }
    }
}

void BFSMTGraph(int i, MTGraph G) {
    Queue Q = MakeQueueNull();//ʹ�ö�����ʵ�ֹ���
    EnQueue(i, Q);
    while (!IsEmptyQueue(Q)) {
        int k = Front(Q);
        DeQueue(Q);//����
        for (int j = 0; j < G->n; j++) {
            if (visited[j] == 0 && G->edge[k * G->n + j] == 1) {
                visited[j] = 1;
                dfn[j] = count++;
                EnQueue(j, Q);
            }
        }
    }
}

void BFSMTGraphTraverse(MTGraph G) {
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;
    }
    count = 1;
    for (int i = 0; i < G->n; i++) {
        if (visited[i] == 0) {
            dfn[i] = count++;
            visited[i] = 1;
            BFSMTGraph(i, G);
        }
    }
}

void BFSAdjGraph(int i, AdjGraph G) {
    Queue Q = MakeQueueNull();//ʹ�ö�����ʵ�ֹ���
    EnQueue(i, Q);//���
    while (!IsEmptyQueue(Q)) {
        int k = Front(Q);
        DeQueue(Q);
        EdgeNode p = G->vexlist[k].firstedge;
        while (p) {
            if (visited[p->adjvex] == 0) {
                fprintf(fp1, "(%c,%c)\n", G->vexlist[i].vertex, G->vexlist[p->adjvex].vertex);
                visited[p->adjvex] = 1;
                dfn[p->adjvex] = count++;
                EnQueue(p->adjvex, Q);
            }
            p = p->next;
        }
    }
}

void BFSAdjGraphTraverse(AdjGraph G) {
    fp1 = fopen("BFSTraverse.txt", "w");
    fprintf(fp1, "����Ϊ:\n");//������д���ļ�
    for (int i = 0; i < G->n; i++) {
        fprintf(fp1, "%c ", G->vexlist[i].vertex);
    }
    fprintf(fp1, "\n");
    fprintf(fp1, "��Ϊ��\n");
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;
    }
    count = 1;
    for (int i = 0; i < G->n; i++) {
        if (visited[i] == 0) {
            visited[i] = 1;
            dfn[i] = count++;
            BFSAdjGraph(i, G);
        }
    }
    fclose(fp1);
}
