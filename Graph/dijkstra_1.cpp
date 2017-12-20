// 自己打得有点乱啊
// 要整理一下


#include <iostream>
using namespace std;
#define MAX 20
#define INF 99999

int main(){
    int adj[MAX][MAX];

    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            adj[i][j] = 0;
        }
    }

    int dimemsion;
    cin >> dimemsion;
    int v, w, p;
    while (cin >> v >> w >> p){
        adj[v][w] = p;
    }
    cin.get();
    cin >> v >> w;

    int final[MAX];
    for (int i = 0; i < dimemsion; i++){
        final[i] = 0;
    }

    int shortPath[MAX];
    for (int i = 0; i < dimemsion; i++){
        shortPath[i] = INF;
    }

    int path[MAX];
    for (int i = 0; i < dimemsion; i++){
        path[i] = 0;
    }
    
    for (int i = 0; i < dimemsion; i++){
        for (int j = 0; j < dimemsion; j++){
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
    
    shortPath[v] = 0;

    for (int i = 0; i < dimemsion; i++){
        int cur_short_v = 0;
        int cur_short = INF;

        for (int i = 0; i < dimemsion; i++){
            if (final[i] == 0 && shortPath[i] < cur_short){
                cout << cur_short_v << " :: ";
                cur_short_v = i;
                cur_short = shortPath[i];
            }
        }

        cout << cur_short_v << " : ";
        final[cur_short_v] = 1;

        for (int i = 0; i < dimemsion; i++){
            if (final[i] == 0 && adj[cur_short_v][i] != 0 && shortPath[cur_short_v] + adj[cur_short_v][i] < shortPath[i])
            {
                shortPath[i] = shortPath[cur_short_v] + adj[cur_short_v][i];
                path[i] = cur_short_v;
            }
        }

        // for (int i = 0; i < dimemsion; i++){
        //     cout << shortPath[i] << " ";
        // }
        // cout << endl;
    }



    for (int i = 0; i < dimemsion; i++){
        cout << i << " : " << shortPath[i] << ":: " << path[i] << endl;
    }


    return 0;
}


