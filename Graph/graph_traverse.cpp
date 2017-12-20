#include<iostream>
#include<vector>
#include <queue>
using namespace std;

const int MAX = 6;// 表示图的节点的序号从0-5且没有孤立节点
// 以下是使用邻接矩阵来表示图的深度优先遍历
int map[MAX][MAX]; 
/* map[i][j]代表vi->vj有一条直接路径 */
int visited[MAX];
void print(int index){
    cout << index << endl;
}
void traverse(int v_index, int n){
    for (int i = 0;i < n; i++){
        if (map[v_index][i] && !visited[i]){
            print(i);
            visited[i] = 1;
            traverse(i, n);
        }
    }
}
void depth_first(int n){// adj matrix
    for(int i = 0; i < n; i++){
       if(!visited[i]){
           print(i);
           traverse(i,n);
       } 
    }
}





int main(){
    int n;
    cin >> n;
    for (int i = 0 ;i < n; i++){
        int s, e;
        cin >> s >> e;
        map[s][e] = 1;
    }
    depth_first(MAX);
    return 0; 
}
