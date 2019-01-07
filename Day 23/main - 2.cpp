#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#define DIM 4002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

long long n, x, y, z, r;
int viz[DIM];
int mat[DIM][DIM];

char c;

struct nanorobot{
    long long x, y, z, r;
};

nanorobot MakeNano(long long x, long long y, long long z, long long r){
    nanorobot aux;
    aux.x = x;
    aux.y = y;
    aux.z = z;
    aux.r = r;
    return aux;
}

vector<nanorobot> robots;

string str;
int maxsizex;

int binarySRC(int item){
    int st = 1, dr = n;
    while(st <= dr){
        int mid = (st + dr) / 2;
        if(robots[mid].r == item)
            return mid;
    }
    return st;
}

bool check(nanorobot a, nanorobot b){
    long long dist = abs(a.x - b.x);
    dist += abs(a.y - b.y);
    dist += abs(a.z - b.z);
    return  dist <= a.r;
}

bool check(int option){
    for(int i = 1; i < robots.size(); ++ i)
        if(robots[i].x == maxsizex)
            return true;
    return false;
}

int main(int argc, const char * argv[]) {
    while(getline(in, str)){
        int i = 5;
        x = 0;
        int minus = 1;
        if(str[i] == '-'){
            minus = -1;
            ++ i;
        }
        while(str[i] >= '0'&& str[i] <= '9'){
            x = x * 10 + str[i] - '0';
            ++ i;
        }
        x = x * minus;
        
        y = 0;
        ++ i;
        minus = 1;
        if(str[i] == '-'){
            minus = -1;
            ++ i;
        }
        while(str[i] >= '0'&& str[i] <= '9'){
            y = y * 10 + str[i] - '0';
            ++ i;
        }
        y = y * minus;
        
        z = 0;
        ++ i;
        minus = 1;
        if(str[i] == '-'){
            minus = -1;
            ++ i;
        }
        while(str[i] >= '0'&& str[i] <= '9'){
            z = z * 10 + str[i] - '0';
            ++ i;
        }
        z = z * minus;
        
        i += 5;
        r = 0;
        minus = 1;
        if(str[i] == '-'){
            minus = -1;
            ++ i;
        }
        while(i < str.size() && str[i] >= '0'&& str[i] <= '9'){
            r = r * 10 + str[i] - '0';
            ++ i;
        }
        r = r * minus;
        robots.push_back(MakeNano(x, y, z, r));
    }
    
    maxsizex = (n / 2) * 21;

    long long maxim = -1, pos;
    
    for(int i = 0; i < robots.size(); ++ i){
        if(robots[i].r > maxim){
            maxim = robots[i].r;
            pos = i;
        }
    }
    maxim = 0;
    for(int j = 0; j < robots.size(); ++ j){
        if(check(robots[pos], robots[j])){
            maxim ++;
        }
    }
    
    out<<maxim<<'\n';
    
    
    int raza = 1;
    while(true){
        ++ raza;
        int option = binarySRC(raza);
        if(check(option)){
            out<<option * n * n;
            return 0;
        }
        
    }
    
    return 0;
}
