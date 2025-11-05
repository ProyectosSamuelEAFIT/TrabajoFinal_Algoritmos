#include <bits/stdc++.h>
using namespace std;

// aca usamos Dijkstra para encontrar el camino de costo minimo desde la esquina superior izquierda hasta la esquina inferior derecha
int solve_dijkstra(const vector<vector<int>>& a){
    int n = (int)a.size();
    const int INF = INT_MAX/4;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    // esto es el costo y la posicion (i,j)
    using State = pair<int, pair<int,int>>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[0][0] = a[0][0];
    pq.push({dist[0][0], {0,0}});
    // esto es para verificar si una posicion (i,j) esta dentro de los limites de la matriz
    // usamos una lambda function porque es otra opcion de C++, aunque podria ser una funcion normal
    auto inside = [&](int i, int j){ return i>=0 && i<n && j>=0 && j<n; };
    // esto es para movernos hacia abajo o hacia la derecha
    int di[2] = {1, 0}; 
    int dj[2] = {0, 1};

    // ahora, en dijkstra usamos una cola de prioridad y vamos explorando los nodos con menor costo acumulado
    while(!pq.empty()){
        auto [d, ij] = pq.top(); pq.pop();
        auto [i,j] = ij;
        if(d!=dist[i][j]) continue;
        if(i==n-1 && j==n-1) break;
        for(int k=0;k<2;k++){
            int ni=i+di[k], nj=j+dj[k];
            if(!inside(ni,nj)) continue;
            int nd = d + a[ni][nj];
            if(nd < dist[ni][nj]){
                dist[ni][nj] = nd;
                pq.push({nd,{ni,nj}});
            }
        }
    }
    return dist[n-1][n-1];
}
