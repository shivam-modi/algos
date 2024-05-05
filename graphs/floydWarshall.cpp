// give shortest distance from every node to every node

// can be used to detect negative edge cycle if while calculating the distance 
// if the same node distance becomes negative we have a negative edge cycle

#include <bits/stdc++.h>

int floydWarshall(int n, int m, int src, int dest, vector<vector<int>> &edges) {
    vector<vector<int>> grid(n+1, vector<int>(n+1, 1e9));``

    for(auto &edge: edges) {
       int u = edge[0];
       int v = edge[1];
       int wt = edge[2];

        grid[u][v] = wt; 
    }

    for(int i=1; i<=n; i++){
        grid[i][i] = 0;
    }

    for(int via = 1; via <=n; via++){
        for(int i = 1; i<=n; i++) {
            for(int j = 1; j<=n; j++) {
                if(grid[i][via] != 1e9 && grid[via][j] != 1e9)
                grid[i][j] = min(grid[i][j], grid[i][via] + grid[via][j]);
            }
        }
    }

    // for(int i = 1; i<=n; i++) {
    //     for(int j = 1; j<=m; j++) {
    //         cout<<grid[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

   return grid[src][dest];
}