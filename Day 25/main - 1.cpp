#include <iostream>
#include <fstream>
#include <vector>
#define DIM 2002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, x, y, z, t;
int father[DIM];

struct coord4D{
    int x, y, z, t;
};

coord4D MakeCoord(int x, int y, int z, int t){
    coord4D aux;
    aux.x = x;
    aux.y = y;
    aux.z = z;
    aux.t = t;
    return aux;
}

char c;

vector<coord4D> coords;

int rad(int x){
    while(father[x] > 0)
        x = father[x];
    return x;
}

int manhattan(int i, int j){
    return abs(coords[i].x - coords[j].x) + abs(coords[i].y - coords[j].y) + abs(coords[i].z - coords[j].z) + abs(coords[i].t - coords[j].t);
}

int main(int argc, const char * argv[]) {
    while(in>>x){
        in>>c>>y>>c>>z>>c>>t;
        coords.push_back(MakeCoord(x, y, z, t));
    }
    for(int i = 0; i <= coords.size(); ++ i)
        father[i] = -1;
    
    for(int i = 0; i < coords.size(); ++ i){
        for(int j = i + 1; j < coords.size(); ++ j){
            if(manhattan(i, j) <= 3){
                int rx = rad(i);
                int ry = rad(j);
                if(rx != ry)
                {
                    if(father[rx] < father[ry])
                    {
                        father[rx] += father[ry];
                        father[ry] = rx;
                    }
                    else
                    {
                        father[ry] += father[rx];
                        father[rx] = ry;
                    }
                }
            }
        }
    }
    
    int sol = 0;
    for(int i = 0; i < coords.size(); ++ i)
        if(father[i] < 0)
            ++ sol;
    
    out<<sol;
    
    
    return 0;
}
