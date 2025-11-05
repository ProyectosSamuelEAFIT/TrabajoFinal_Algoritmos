#include <bits/stdc++.h>
using namespace std;

// El best y n son variables que significan el mejor costo encontrado hasta ahora y el tamaño de la matriz
namespace {
int best;
int n;

// Aca usamos DFS para recorrer todas las rutas posibles desde la esquina superior izquierda hasta la esquina inferior derecha de la matriz
void dfs(const vector<vector<int>>& a, int i, int j, int acc){
    // aca usamos una poda, si el costo acumulado ya es mayor o igual al mejor encontrado, no se sigue explorando esa ruta
    if(acc >= best) return;
    // Si llegamos a la esquina inferior derecha, actualizamos el mejor costo si el acumulado es menor
    if(i==n-1 && j==n-1){
        best = min(best, acc + a[i][j]);
        return;
    }

    // esto es para poder movernos hacia abajo o hacia la derecha en la matriz
    if(i+1<n) dfs(a, i+1, j, acc + a[i][j]);
    if(j+1<n) dfs(a, i, j+1, acc + a[i][j]);
}
}
// y esta es la funcion principal que se llama desde main.cpp que inicializa las variables y llama a la funcion dfs
int solve_backtracking(const vector<vector<int>>& a){
    n = (int)a.size();
    best = INT_MAX/4;
    dfs(a, 0, 0, 0);
    return best;
}
