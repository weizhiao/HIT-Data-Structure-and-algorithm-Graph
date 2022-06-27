#include<stdio.h>
#include<stdlib.h>

int visited[20];//记录顶点是否被访问
int dfn[20];//进行先深编号或者先广编号
int count;
FILE* fp1, * fp2;//用于存储生成树

//图的邻接矩阵存储结构
struct mtgraph
{
    int type;
    int n, e;//顶点数和边数
    int* edge;//邻接矩阵
    char* verlist;
};

//边表结点
struct edgenode
{
    int adjvex;//顶点序号
    struct edgenode* next;
};

//顶点表结点
struct vertexnode
{
    char vertex;
    struct edgenode* firstedge;//边表
};

//图的邻接表存储结构
struct adjgraph
{
    int n, e;
    int type;//类型
    struct vertexnode* vexlist;//顶点表
};

//栈
struct stack
{
    int data;
    struct stack* next;
};

//队列结点
struct queuenode
{
    int data;
    struct queuenode* next;
};

//队列
struct queue
{
    struct queuenode* front;//头指针
    struct queuenode* rear;//尾指针
};

//重命名
typedef struct mtgraph* MTGraph;
typedef struct adjgraph* AdjGraph;
typedef struct edgenode* EdgeNode;
typedef struct stack* Stack;
typedef struct queue* Queue;
typedef struct queuenode* Queuenode;

void PrintMTGraphDfn(MTGraph G);//打印邻接矩阵的遍历结果
void PrintAdjGraphDfn(AdjGraph G);//打印邻接表的遍历结果
void ShowMenu();//显示菜单
Stack MakeStackNull();//建立空栈
void Push(int i, Stack S);//压栈
void Pop(Stack S);//弹栈
int Top(Stack S);//返回栈顶元素
int IsEmptyStack(Stack S);//判断栈是否为空
Queue MakeQueueNull();//建立空队列
void EnQueue(int i, Queue Q);//入队
void DeQueue(Queue Q);//出队
int Front(Queue Q);//返回队首元素
int IsEmptyQueue(Queue Q);//判断队列是否为空
void DFSAdjGraph(int i, AdjGraph G);//邻接表的深搜的子函数
void DFSMTGraph(int i, MTGraph G);//邻接矩阵的深搜的子函数
void DFSMTGraphTraverse(MTGraph G);//邻接矩阵深搜的主算法
void DFSAdjGraphTraverse(AdjGraph G);//邻接表深搜的主算法
void BFSAdjGraph(int i, AdjGraph G);//邻接表广搜的子函数
void BFSMTGraph(int i, MTGraph G);//邻接矩阵广搜的子函数
void BFSMTGraphTraverse(MTGraph G);//邻接矩阵广搜的主算法
void BFSAdjGraphTraverse(AdjGraph G);//邻接表广搜的主算法
void CreateMTGraph(MTGraph G);//建立图的邻接矩阵
void CreateAdjGraph(AdjGraph G);//建立图的邻接表
AdjGraph MTGraphToAdjGraph(MTGraph G);//将邻接矩阵转换为邻接表
MTGraph AdjGraphToMTGraph(AdjGraph G);//将邻接表转换为邻接矩阵
int FindMTCode(char ch, char* str);//找到邻接矩阵的顶点编号
int FindAdjCode(char ch, AdjGraph G);//找到邻接表的顶点编号

int main()
{
    AdjGraph G1 = malloc(sizeof(struct adjgraph));
    MTGraph G2 = malloc(sizeof(struct mtgraph));
    while (1) {
        int ch;
        ShowMenu();
        while (scanf("%d", &ch) != 1) {
            printf("输入错误，请重新输入！\n");
            fflush(stdin);
        }
        switch (ch) {//使用switch语句进行功能选择
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
        printf("顶点：%c 优先编号：%d\n", G->vexlist[i].vertex, dfn[i]);
        str[dfn[i]] = G->vexlist[i].vertex;//按编号将顶点存入字符串
    }
    printf("先深序列为:");
    for (int i = 1; i <= G->n; i++) {
        printf("%c ", str[i]);
    }
    printf("\n");
}

void PrintMTGraphDfn(MTGraph G) {
    char* str = malloc(sizeof(char) * (G->n + 1));
    for (int i = 0; i < G->n; i++) {
        printf("顶点：%c 优先编号：%d\n", G->verlist[i], dfn[i]);
        str[dfn[i]] = G->verlist[i];//按编号将顶点存入字符串
    }
    printf("先深序列为:");
    for (int i = 1; i <= G->n; i++) {
        printf("%c ", str[i]);
    }
    printf("\n");
}

//显示菜单
void ShowMenu() {
    printf("---------------------------------\n");
    printf("1、建立图的邻接表\n");
    printf("2、建立图的邻接矩阵\n");
    printf("3、将图的邻接表转换为邻接矩阵\n");
    printf("4、将图的邻接矩阵转换为邻接表\n");
    printf("5、深度搜索图(邻接表)\n");
    printf("6、深度搜索图(邻接矩阵)\n");
    printf("7、广度搜索图(邻接表)\n");
    printf("8、广度搜索图(邻接矩阵)\n");
    printf("0、退出\n");
    printf("---------------------------------\n");
}

//判断队列是否为空
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
    Queue Q = malloc(sizeof(struct queue));//含有头节点
    Q->front = malloc(sizeof(struct queuenode));
    Q->front->next = NULL;
    Q->rear = Q->front;
    return Q;
}

//从队尾进队
void EnQueue(int i, Queue Q)
{
    Queuenode temp = malloc(sizeof(struct queuenode));
    temp->data = i;
    Q->rear->next = temp;
    Q->rear = temp;
}

//从队首出队
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
    Stack S = malloc(sizeof(struct stack));//有头节点
    S->next = NULL;
    return S;
}

void Push(int i, Stack S)
{
    Stack temp = malloc(sizeof(struct stack));//头插法
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
    for (int i = 0; str[i] != '\0'; i++)//将字符串扫描一遍
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
    fp = fopen("Graph.txt", "r");//进行文件读取
    char ch;
    char temp[10];
    int i;
    while ((ch = fgetc(fp)) != ',')
    {
        G->type = ch - '0';
    }
    if (G->type == 0) {
        printf("图的类型为:无向图\n");
    }
    else {
        printf("图的类型为:有向图\n");
    }
    for (i = 0; (ch = fgetc(fp)) != ','; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->n = atoi(temp);//将字符串转换为整型
    printf("图的顶点数为:%d\n", G->n);
    for (i = 0; (ch = fgetc(fp)) != '\n'; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->e = atoi(temp);//将字符串转换为整型
    printf("图的边数为:%d\n", G->e);
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
    printf("图的顶点为:");
    while ((ch = fgetc(fp)) != '\n')
    {
        printf("%c ", ch);
        G->verlist[i++] = ch;
    }
    G->verlist[i] = '\0';
    if (i != G->n)//判断建立是否正确
    {
        printf("图的顶点数与实际不符!\n");
        exit(0);
    }
    printf("\n");
    printf("图的边为:\n");
    for (int i = 0; i < G->e; i++)
    {
        int v[2];
        int k = 0;
        while ((ch = fgetc(fp)) != ')')//遇到")"结束
        {
            if (ch != ',' && ch != '(')
            {
                v[k++] = FindMTCode(ch, G->verlist);
            }
        }
        printf("(%c,%c)\n", G->verlist[v[0]], G->verlist[v[1]]);//输出边
        if (G->type == 0)//无向图
        {
            G->edge[v[0] * G->n + v[1]] = 1;
            G->edge[v[1] * G->n + v[0]] = 1;
        }
        else//有向图
        {
            G->edge[v[0] * G->n + v[1]] = 1;
        }
    }
    fclose(fp);//关闭文件
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
        printf("图的类型为:无向图\n");
    }
    else {
        printf("图的类型为:有向图\n");
    }
    for (i = 0; (ch = fgetc(fp)) != ','; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->n = atoi(temp);//将字符串转换为整型
    printf("图的顶点数为:%d\n", G->n);
    for (i = 0; (ch = fgetc(fp)) != '\n'; i++)
    {
        temp[i] = ch;
    }
    temp[i] = '\0';
    G->e = atoi(temp);//将字符串转换为整型
    printf("图的边数为:%d\n", G->e);
    G->vexlist = malloc(sizeof(struct vertexnode) * G->n);
    i = 0;
    printf("图的顶点为:");
    while ((ch = fgetc(fp)) != '\n')
    {
        printf("%c ", ch);
        G->vexlist[i].firstedge = NULL;
        G->vexlist[i++].vertex = ch;
    }
    printf("\n");
    if (i != G->n)
    {
        printf("图的顶点数与实际不符!\n");
        exit(0);
    }
    printf("图的边为:\n");
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
        if (G->type == 0)//此处采用头插法
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
    fclose(fp);//关闭文件
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
            if (G->edge[i * G->n + j] == 1)//读取邻接矩阵
            {
                EdgeNode temp = malloc(sizeof(struct edgenode));
                temp->adjvex = j;
                temp->next = G1->vexlist[i].firstedge;
                G1->vexlist[i].firstedge = temp;
            }
        }
    }
    printf("转换成功！\n");
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
            G1->edge[i * G->n + p->adjvex] = 1;//1代表有边
            p = p->next;
        }
    }
    printf("转换成功！\n");
    return G1;
}

void DFSMTGraphTraverse(MTGraph G)
{
    for (int i = 0; i < G->n; i++)//进行初始化
    {
        visited[i] = 0;
    }
    count = 1;//编号从1开始
    for (int i = 0; i < G->n; i++)
    {
        if (visited[i] == 0)//判断是否访问过
        {
            visited[i] = 1;//标记
            dfn[i] = count++;//编号
            DFSMTGraph(i, G);
        }
    }
}

//深度搜索的递归算法
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

//深度搜索的递归算法
void DFSAdjGraph(int i, AdjGraph G) {
    Stack S = MakeStackNull();
    Push(i, S);
    while (!IsEmptyStack(S)) {//当栈为空时结束
        int k = Top(S);
        EdgeNode p = G->vexlist[k].firstedge;
        while (p) {
            if (visited[p->adjvex] == 0) {//写入边
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
    fp2 = fopen("DFSTraverse.txt", "w");//以写的方式打开文件
    fprintf(fp2, "顶点为:\n");
    for (int i = 0; i < G->n; i++) {
        fprintf(fp2, "%c ", G->vexlist[i].vertex);
    }
    fprintf(fp2, "\n");
    fprintf(fp2, "边为：\n");
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

//深度遍历的递归算法
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

//深度搜索的非递归算法
void DFSMTGraph(int i, MTGraph G)
{
    Stack S = MakeStackNull();
    Push(i, S);
    int flag;//用来标记是否到达最深处
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
    Queue Q = MakeQueueNull();//使用队列来实现广搜
    EnQueue(i, Q);
    while (!IsEmptyQueue(Q)) {
        int k = Front(Q);
        DeQueue(Q);//出队
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
    Queue Q = MakeQueueNull();//使用队列来实现广搜
    EnQueue(i, Q);//入队
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
    fprintf(fp1, "顶点为:\n");//将顶点写入文件
    for (int i = 0; i < G->n; i++) {
        fprintf(fp1, "%c ", G->vexlist[i].vertex);
    }
    fprintf(fp1, "\n");
    fprintf(fp1, "边为：\n");
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
