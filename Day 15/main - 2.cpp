#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#define DIM 1002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, round;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

string str;
int mat[DIM][DIM];
int leeMat[DIM][DIM];

deque<pair<int, int> > q;

struct troop{
    char type;
    int x, y;
    int HP = 200;
    int attack = 3;
    bool alive = true;
};

troop MakeTroop(char type, int x, int y){
    troop aux;
    aux.type = type;
    aux.x = x;
    aux.y = y;
    return aux;
}

vector<troop> troops, inittroops;

bool cmp(troop a, troop b){
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

void initialize(){
    for(int i = 1; i <= 100; ++ i){
        for(int j = 1; j <= 100; ++ j){
            leeMat[i][j] = mat[i][j];
        }
    }
    for(auto it : troops)
        if(it.alive)
            leeMat[it.x][it.y] = -1;
}

vector<pair<int, int> > coords;

pair<int, int> FindClosest(int x, int y, char type){
    pair<int, int> sol;
    int minDist = 1e9;
    int minx = 1e9, miny = 1e9, stepx = 0, stepy = 0;
    initialize();
    coords.clear();
    for(auto it : troops){
        if(it.type != type){
            if(it.alive){
                int xc, yc;
                for(int i = 0; i < 4; ++ i){
                    xc = it.x + dx[i];
                    yc = it.y + dy[i];
                    if(leeMat[xc][yc] == 0){
//                        q.push_back(make_pair(xc, yc));
                        coords.push_back(make_pair(xc, yc));
//                        mat[xc][yc] = 1;
                    }
                }
            }
        }
    }
    for(auto it : coords){
        initialize();
        q.push_back(it);
        leeMat[it.first][it.second] = 1;
        while(!q.empty()){
            int xstart = q.front().first;
            int ystart = q.front().second;
            q.pop_front();
            for(int i = 0; i < 4; ++ i){
                int xc = xstart + dx[i];
                int yc = ystart + dy[i];
                if((leeMat[xc][yc] > 0 && leeMat[xc][yc] > leeMat[xstart][ystart] + 1) || leeMat[xc][yc] == 0){
                    leeMat[xc][yc] = leeMat[xstart][ystart] + 1;
                    q.push_back(make_pair(xc, yc));
                }
            }
        }
        for(int i = 0; i < 4; ++ i){
            int xc = x + dx[i];
            int yc = y + dy[i];
            if(leeMat[xc][yc] > 0){
                if(leeMat[xc][yc] == minDist){
                    if(it.first < minx || (it.first == minx && it.second < miny)){
                        minDist = leeMat[xc][yc];
                        minx = it.first;
                        miny = it.second;
                        stepx = xc;
                        stepy = yc;
                    }
                    else{
                        if(it.first == minx && it.second == miny &&(stepx > xc || (stepx == xc && stepy > yc))){
                            minDist = leeMat[xc][yc];
                            minx = it.first;
                            miny = it.second;
                            stepx = xc;
                            stepy = yc;
                        }
                    }
                }
                if(leeMat[xc][yc] < minDist){
                    minDist = leeMat[xc][yc];
                    minx = it.first;
                    miny = it.second;
                    stepx = xc;
                    stepy = yc;
                }
            }
        }
    }
    
    sol.first = stepx;
    sol.second = stepy;
    
    
    return sol;
}

int CheckForAttack(int x, int y, char type){
    int minim = 1e9;
    int sol = -1;
    int minx = 1e9, miny = 1e9;
    for(int i = 0; i < troops.size(); ++ i){
        if(troops[i].type != type && troops[i].alive){
            for(int j = 0; j < 4; ++ j){
                if(troops[i].x + dx[j] == x && troops[i].y + dy[j] == y){
                    if(troops[i].HP == minim){
                        if(troops[i].x < minx || (troops[i].x == minx && troops[i].y < miny)){
                            minim = troops[i].HP;
                            sol = i;
                            minx = troops[i].x;
                            miny = troops[i].y;
                        }
                    }
                    if(troops[i].HP < minim){
                        minim = troops[i].HP;
                        sol = i;
                        minx = troops[i].x;
                        miny = troops[i].y;
                    }
                }
            }
        }
    }
    return sol;
}

char MatAfis[100][100];

void afis(){
    for(int i = 1; i <= 9; ++ i)
        for(int j = 1; j <= 9; ++ j){
            if(mat[i][j] == 0)
                MatAfis[i][j] = '.';
            if(mat[i][j] == -1)
                MatAfis[i][j] = '#';
        }
    for(auto it : troops)
        if(it.alive)
            MatAfis[it.x][it.y] = it.type;
    for(int i = 1; i <= 9; ++ i, cout<<'\n')
        for(int j = 1; j <= 9; ++ j)
            cout<<MatAfis[i][j]<<" ";
    for(auto it : troops){
        cout<<it.type<<" "<<it.HP<<'\n';
    }
}

int main(int argc, const char * argv[]) {
    int i = 0;
    while(in>>str){
        ++ i;
        int j = 0;
        for(auto it : str){
            ++ j;
            if(it == '#')
                mat[i][j] = -1;
            if(it == 'G' || it == 'E'){
                inittroops.push_back(MakeTroop(it, i, j));
                troops.push_back(MakeTroop(it, i, j));
//                mat[i][j] = -2;
            }
        }
    }
    
    
//    for(int i = 1; i <= 20; ++ i, out<<'\n')
//        for(int j = 1; j <= 20; ++ j)
//            out<<mat[i][j]<<" ";
    
    for(int attack = 4; attack <= 1000; ++ attack){
        troops.clear();
        for(int i = 0; i < inittroops.size(); ++ i)
            troops.push_back(inittroops[i]);
        for(int i = 0; i < troops.size(); ++ i)
            if(troops[i].type == 'E')
                troops[i].attack = attack;
        round = 0;
        int ok = 1;
        while(ok){
            int cnt = 0;
            ok = 0;
            ++ round;
            sort(troops.begin(), troops.end(), cmp);
            for(auto troopIt : troops){
                
                if(troopIt.alive == 0){
                    ++ cnt;
                    continue;
                }
                int found = CheckForAttack(troopIt.x, troopIt.y, troopIt.type);
                if(found == -1){
                    pair<int, int> coord = FindClosest(troopIt.x, troopIt.y, troopIt.type);
                    if(coord.first != 0 || coord.second != 0){
                        ok = 1;
                        troops[cnt].x = coord.first;
                        troops[cnt].y = coord.second;
                    }
                }
                found = CheckForAttack(troops[cnt].x, troops[cnt].y, troopIt.type);
                if(found != -1){
                    ok = 1;
                    troops[found].HP -= troopIt.attack;
                    if(troops[found].HP < 0)
                        troops[found].alive = false;
                }
                ++ cnt;
            }
//            cout<<round<<'\n';
//            afis();
        }
        ok = 1;
        int SOL = 0;
        for(auto it : troops){
            if(it.type == 'E' && it.alive == 0)
                ok = 0;
            if(it.alive)
                SOL += it.HP;
        }
        if(ok){
            out<<(round - 2) * SOL;
            return 0;
        }
        
    }
    return 0;
}
