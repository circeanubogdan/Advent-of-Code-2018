#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#define DIM 2002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, i, minx = 1e9, miny = 1e9, maxx = -1e9, maxy = -1e9, MAXIM = -1e9;
char mat[DIM][DIM];
int dist[DIM][DIM];

string str;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

char c;

pair<int, int> generate(int x, int y){
    while(i < str.size()){
        minx = min(minx, x);
        miny = min(miny, y);
        maxx = max(maxx, x);
        maxy = max(maxy, y);
        if(str[i] == '('){
            deque<pair<int, int> > q;
            ++ i;
            q.push_back(generate(x, y));
            while(str[i] == '|'){
                ++ i;
                q.push_back(generate(x, y));
            }
            ++ i;
            int currentI = i;
            while(!q.empty()){
                i = currentI;
                generate(q.front().first, q.front().second);
                q.pop_front();
            }
        }
        if(i >= str.size())
            return {x, y};
        if(str[i] == '|')
            return {x, y};
        if(str[i] == ')')
            return {x, y};
        
        int antx = x, anty = y;
        
        if(str[i] == 'W'){
            -- y;
        }
        
        if(str[i] == 'E'){
            ++ y;
        }
        
        if(str[i] == 'N'){
            -- x;
        }
        
        if(str[i] == 'S'){
            ++ x;
        }
        //MAXIM = max(MAXIM, dist[x][y]);
        minx = min(minx, x);
        miny = min(miny, y);
        maxx = max(maxx, x);
        maxy = max(maxy, y);
        
        dist[x][y] = min(dist[antx][anty] + 1, dist[x][y]);
        ++ i;
    }
    return {x, y};
}

deque <pair<int, int> > q;

int leeMat[DIM][DIM];

int main(int argc, const char * argv[]) {
    int ok = 1;
    in>>c;
    for(int i = 1; i <= 2000; ++ i)
        for(int j = 1; j <= 2000; ++ j)
            dist[i][j] = 1e9;
    while(ok){
        in>>str;
        if(str.back() == '$'){
            str.pop_back();
            ok = 0;
        }
        i = 0;
        dist[1000][1000] = 0;
        generate(1000, 1000);
        mat[1000][1000] = 'X';
    }
    -- minx;
    -- miny;
    ++ maxx;
    ++ maxy;
    for(int i = minx; i <= maxx; ++ i, cout<<'\n')
        for(int j = miny; j <= maxy; ++ j){
            if(mat[i][j] == 0)
                mat[i][j] = '#';
            cout<<mat[i][j];
        }
    
    q.push_back({1000, 1000});
    dist[1000][1000] = 0;
    
    
    while(!q.empty()){
        int xc = q.front().first;
        int yc = q.front().second;
        q.pop_front();
        for(int i = 0; i < 4; ++ i){
            int xn = xc + dx[i];
            int yn = yc + dy[i];
            if(mat[xn][yn] != '#' && (leeMat[xn][yn] == 0 || leeMat[xn][yn] > leeMat[xc][yc] + 1)){
                leeMat[xn][yn] = leeMat[xc][yc] + 1;
                q.push_back({xn, yn});
            }
        }
    }
    
    int maxim = -1e9, sol = 0;
    for(int i = minx; i <= maxx; ++ i)
        for(int j = miny; j <= maxy; ++ j){
            if(dist[i][j] == 1e9)
                continue;
            if(dist[i][j] > 1000)
                ++ sol;
            MAXIM = max(MAXIM, dist[i][j]);
            
        }
    out<<MAXIM<<" "<<sol;
    
    return 0;
}
