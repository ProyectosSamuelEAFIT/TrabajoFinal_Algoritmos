#include <bits/stdc++.h>
using namespace std;
 
int solve_programacion_dinamica(const vector<vector<int>>& a){
    int n = (int)a.size();
    const int INF = INT_MAX/4;
    vector<vector<int>> dp(n, vector<int>(n, INF));
    dp[0][0] = a[0][0];
    // este for doble llena la tabla dp con los costos minimos para llegar a cada celda y luego devuelve el costo minimo para llegar a la esquina inferior derecha
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==0 && j==0) continue;
            int best = INF;
            if(i>0) best = min(best, dp[i-1][j]);
            if(j>0) best = min(best, dp[i][j-1]);
            dp[i][j] = a[i][j] + best;
        }
    }
    return dp[n-1][n-1];
}
