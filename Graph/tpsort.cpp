#include <iostream>  
#include <stack>  
#include <vector>  
#include <list>  
using namespace std;  
  
vector<list<int>> Adj; //邻接表  
vector<int> inDegree; //保存每个节点的入度  
stack<int> stk; //保存当前入度为0的节点编号 // 使用队列也可以 
  
void CreatGraph()  
{  
    int n, m, v1, v2;  
    cin >> n >> m;  
    Adj.assign(n, list<int>()); // 初始化 
    inDegree.assign(n, 0);  
    while (m--)  
    {  
        cin >> v1 >> v2;  
        Adj[v1].push_back(v2);  
        inDegree[v2]++;  
    }  
    for (int i = 0; i < n;i++)  
        if (inDegree[i] == 0) stk.push(i); // 搜索图中入度为0的点，并放入栈中。 
}  
void tpSort()  
{  
    vector<int> vec;  
    int v;  
    while (!stk.empty())  
    {  
        v = stk.top();  
        stk.pop();  
        //遍历与节点v相连的节点  
        for (auto it = Adj[v].begin(); it != Adj[v].end(); it++)  
        {  
            inDegree[*it]--;  
            if (inDegree[*it] == 0) stk.push(*it);  
        }  
        //Adj[v].clear(); //本行可以省略，以提升程序效率  
        vec.push_back(v);  
    }  
    if (vec.size() != inDegree.size())  
    {  
        cout << "图中存在环路，不能进行拓扑排序！\n";  
        return;  
    }  
    for (auto item : vec)  
        cout << item << " ";  
    cout << endl;  
}  
int main()  
{  
    CreatGraph();  
    tpSort();  
    return 0;  
}  


/*
 * 拓扑排序
 * 使用邻接矩阵表示图
 */

#include 

using namespace std;

#define N 9

/* global data */

//如果i是j的直接前驱,matrix[i][j] = true, 否则martix[i][j] = false;
//其中i表示行,j表示列
int matrix[N][N]=
{
    0,0,1,0,0,0,0,1,0,
    0,0,1,1,1,0,0,0,0,
    0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,1,1,0,0,
    0,0,0,0,0,1,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,
    0,0,0,0,0,0,1,0,0
};

int into[N];

/* functions declaration */
void get_into_degree(int n);
void toposort(int n);

int main(int argc, char* *argv)
{
    get_into_degree(N);
    toposort(N);
    system("pause");
    return 0;
}

/* functions definition */
void get_into_degree(int n)
{
    for(int j = 0; j < n; ++j)
    {
        into[j] = 0;
        for(int i = 0; i < n; ++i)
        {
            if(matrix[i][j] == 1)
            {
                into[j]++;
            }
        }
    }
}
void toposort(int n)
{
    //需要输出n个结点，排序结束
    for(int i = 1; i <= n; ++i)
    {
        int j = 0;
        while(j < n && into[j] != 0) j++;
        //找到度为0的点
        cout << j + 1 << " ";
        //更新度
        into[j] = N ;//设结点j为最大度，以免再次输出j
        for(int k = 0; k < n; ++k)
        {
            if(matrix[j][k] == 1)
            {
                into[k]--;
            }
        }
    }
}