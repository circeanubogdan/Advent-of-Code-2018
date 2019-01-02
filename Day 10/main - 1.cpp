#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

ifstream in("file.in");
ofstream out("file.out");

int n, x, y, speedX, speedY;
char mat[2000][2000];
string sir;
char c;

struct PoL{
    int x, y, speedX, speedY;
};

PoL MakePoL(int x, int y, int speedX, int speedY){
    PoL aux;
    aux.x = x;
    aux.y = y;
    aux.speedX = speedX;
    aux.speedY = speedY;
    return aux;
}

vector<PoL> coord;

int GetDifference(){
    int maximX = -1, maximY = -1;
    for(int i = 0; i < coord.size(); ++ i){
        for(int j = 0; j < coord.size(); ++ j){
            maximX = max(maximX, abs(coord[i].x - coord[j].x));
            maximY = max(maximY, abs(coord[i].y - coord[j].y));
        }
    }
    return max(maximX, maximY);
}

int GetDifferencex(){
    int maximX = -1;
    for(int i = 0; i < coord.size(); ++ i){
        for(int j = 0; j < coord.size(); ++ j){
            maximX = max(maximX, abs(coord[i].x - coord[j].x));
        }
    }
    return maximX;
}

void cleanMat(){
    for(int i = 0; i <= 1000; ++ i)
        for(int j = 0; j <= 1000; ++ j)
            mat[i][j] = '.';
}

void afis(){
    for(int i = 100; i <= 200; ++ i){
        for(int j = 180; j <= 500; ++ j){
            out<<mat[i][j];
        }
        out<<'\n';
    }
}

int main(int argc, const char * argv[]) {
    while(in>>c){
        for(int i = 1; i <= 9; ++ i)
            in>>c;
        in>>y;
        in>>c;
        in>>x;
        in>>c;
        for(int i = 1; i <= 10; ++ i)
            in>>c;
        in>>speedY;
        in>>c;
        in>>speedX;
        in>>c;
        coord.push_back(MakePoL(x, y, speedX, speedY));
    }
    int cnt = 0;
    while(true){
        ++ cnt;
        int dx1 = GetDifferencex();
        for(int i = 0; i < coord.size(); ++ i){
            coord[i].x += coord[i].speedX;
            coord[i].y += coord[i].speedY;
        }
        int dx2 = GetDifferencex();
        if(dx2 > dx1){
            for(int i = 0; i < coord.size(); ++ i){
                coord[i].x -= coord[i].speedX;
                coord[i].y -= coord[i].speedY;
            }
//            PART 2
//
//            out<<cnt - 1;
//            return 0;
            break;
        }
        
    }
    
    int minimX = 0, minimY = 0;
    for(auto it : coord){
        if(it.x < 0)
            minimX = max(minimX, abs(it.x));
        if(it.y < 0)
            minimY = max(minimY, abs(it.y));
    }
    
    
    for(int i = 0; i < coord.size(); ++ i){
        coord[i].x += minimX;
        coord[i].y += minimY;
    }
    
    cleanMat();
    for(auto it : coord){
        mat[it.x][it.y] = '#';
    }
    for(int i = 0; i < coord.size(); ++ i){
        coord[i].x += coord[i].speedX;
        coord[i].y += coord[i].speedY;
    }
    afis();
    
    
    
    return 0;
}
