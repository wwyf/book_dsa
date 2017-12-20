// adjacency table
typedef struct Node  
{  
    int dest;                   //邻接边的弧头结点序号  
    int weight;                 //权值信息  
    struct Node *next;          //指向下一条邻接边  
}Edge;                          //单链表结点的结构体  
  
typedef struct  
{  
    DataType data;              //结点的一些数据，比如名字  
    int sorce;                  //邻接边的弧尾结点序号  
    Edge *adj;                  //邻接边头指针  
}AdjHeight;                     //数组的数据元素类型的结构体  
  
typedef struct  
{  
    AdjHeight a[MaxVertices];   //邻接表数组  
    int numOfVerts;             //结点个数  
    int numOfEdges;             //边个数  
}AdjGraph;                      //邻接表结构体  