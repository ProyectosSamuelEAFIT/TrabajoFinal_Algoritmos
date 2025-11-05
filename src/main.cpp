#include <bits/stdc++.h>

using namespace std;

extern int solve_backtracking(const vector<vector<int>>& a);
extern int solve_dijkstra(const vector<vector<int>>& a);
extern int solve_programacion_dinamica(const vector<vector<int>>& a);

static inline bool is_comment_or_empty(const string& s){
    for(char c: s){
        if(!isspace((unsigned char)c)){
            return c=='#';
        }
    }
    return true;
}

static vector<vector<vector<int>>> read_cases(istream& in){
    vector<vector<vector<int>>> cases;
    string line;
    while(true){
        // saltar comentarios o lineas vacías
        while (std::getline(in,line)){
            if(!is_comment_or_empty(line)) break;
        }
        if(!in) break;
        stringstream ss(line);
        int n; 
        if(!(ss>>n)) break;
        vector<vector<int>> a(n, vector<int>(n));
        for(int i=0;i<n;i++){
            for(;;){
                if(!std::getline(in, line)){
                    cerr<<"Formato invalido: faltan filas\n";
                    exit(1);
                }
                if(is_comment_or_empty(line)) continue;
                stringstream s2(line);
                for(int j=0;j<n;j++){
                    if(!(s2>>a[i][j])){
                        cerr<<"Formato invalido: fila "<<i<<" columna "<<j<<"\n";
                        exit(1);
                    }
                }
                break;
            }
        }
        cases.push_back(move(a));
    }
    return cases;
}

static long long now_ms(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if(argc < 4){
        cerr<<"Uso: ./caminos <algoritmo> <input_path> <csv_out>\n";
        cerr<<"algoritmo: bt | dijkstra | dp | all\n";
        return 1;
    }
    string alg = argv[1];
    string in_path = argv[2];
    string out_path = argv[3];

    ifstream fin(in_path);
    if(!fin){
        cerr<<"No se pudo abrir input\n";
        return 1;
    }
    auto cases = read_cases(fin);

    bool do_bt = (alg=="bt" || alg=="all");
    bool do_dj = (alg=="dijkstra" || alg=="all");
    bool do_dp = (alg=="dp" || alg=="all");

    bool write_header = false;
    {
        ifstream test(out_path);
        if(!test.good()) write_header = true;
    }
    ofstream fout(out_path, ios::app);
    if(!fout){
        cerr<<"No se pudo abrir CSV de salida\n";
        return 1;
    }
    if(write_header){
        fout<<"case_id,n,algorithm,cost,time_ms\n";
    }

    int case_id = 0;
    for(const auto& a : cases){
        int n = (int)a.size();
        if(do_bt){
            long long t0 = now_ms();
            int cost = solve_backtracking(a);
            long long t1 = now_ms();
            fout<<case_id<<","<<n<<","<<"bt"<<","<<cost<<","<<(t1-t0)<<"\n";
            cout<<"Case "<<case_id<<" bt cost="<<cost<<" time_ms="<<(t1-t0)<<"\n";
        }
        if(do_dj){
            long long t0 = now_ms();
            int cost = solve_dijkstra(a);
            long long t1 = now_ms();
            fout<<case_id<<","<<n<<","<<"dijkstra"<<","<<cost<<","<<(t1-t0)<<"\n";
            cout<<"Case "<<case_id<<" dijkstra cost="<<cost<<" time_ms="<<(t1-t0)<<"\n";
        }
        if(do_dp){
            long long t0 = now_ms();
            int cost = solve_programacion_dinamica(a);
            long long t1 = now_ms();
            fout<<case_id<<","<<n<<","<<"dp"<<","<<cost<<","<<(t1-t0)<<"\n";
            cout<<"Case "<<case_id<<" dp cost="<<cost<<" time_ms="<<(t1-t0)<<"\n";
        }
        case_id++;
    }

    return 0;
}
