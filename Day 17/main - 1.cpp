#include <iostream>
#include <fstream>
#include <string>
#include <deque>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

char c;
int n, minim = 1e9, maxim = -1e9, maximx = -1e9;
string str;

char mat[2000][2000]; bool oki[2005][2005];

deque<pair<int, int> > q;

void f(int x, int y) {

}

int main(int argc, const char * argv[]) {
    while(getline(in, str)){
        int i = 0, n1 = 0, n2 = 0, n3 = 0, x, y;
        char start = str[i];
        ++i;++i;
        while(str[i] >= '0' && str[i] <= '9'){
            n1 = n1 * 10 + str[i] - '0';
            ++ i;
        }
        i += 4;
        while(str[i] >= '0' && str[i] <= '9' && i < str.size()){
            n2 = n2 * 10 + str[i] - '0';
            ++ i;
        }
        i += 2;
        while(str[i] >= '0' && str[i] <= '9' && i < str.size()){
            n3 = n3 * 10 + str[i] - '0';
            ++ i;
        }
        if(start == 'x'){
            y = n1;
            minim = min(y - 1, minim);
            maxim = max(y + 1, maxim);
            for(x = min(n2, n3); x <= max(n2, n3); ++ x)
                mat[x][y] = '#';
            maximx = max(n2, max(n3, maximx));
        }
        else{
            x = n1;
            minim = min(n2 - 1, min(n3 - 1, minim));
            maxim = max(n2 + 1, max(n3 + 1, maxim));
            for(y = min(n2, n3); y <= max(n2, n3); ++ y)
                mat[x][y] = '#';
            maximx = max(x, maximx);
        }
    }
    for(int i = 0; i <= maximx; ++ i){
        for(int j = minim; j <= maxim; ++ j)
            if(mat[i][j] == 0)
                mat[i][j] = '.';
    }
    //f(0, 500);
    deque<pair<int, int> > que;
    oki[0][500] = true;
    
    que.push_back(make_pair(0, 500)); 
    for (; que.size(); ) {
        int x = que.front().first, y = que.front().second; oki[x][y] = false;
        if (mat[x][y] == 's')
            continue;
        int xsaved = x, ysaved = y;
        while ((mat[x][y] == '.' or mat[x][y] == '|') && x <= maximx) {
            mat[x++][y] = '|';
        }
        x--;
        if(x == maximx)
            continue;
        
        int xx = x, yy = y;
        int Left = -1, Right = -1;
        for(int yy = y; yy >= minim; -- yy){
            if(mat[x + 1][yy] == '.'){
                Left = -yy;
                break;
            }
            if(mat[x][yy] == '#'){
                Left = yy + 1;
                break;
            }
        }
        for(int yy = y; yy <= maxim; ++ yy){
            if(mat[x + 1][yy] == '.'){
                Right = -yy;
                break;
            }
            if(mat[x][yy] == '#'){
                Right = yy - 1;
                break;
            }
        }
        if(Left > 0 and Right > 0){
            for(int yy = Left; yy <= Right; ++ yy)
                mat[x][yy] = 's';
            //f(xsaved, ysaved);
            if (x == xsaved - 1){
                if(oki[0][500] == false){
                    que.push_back(make_pair(0, 500));
                    oki[1 - 1][500] = true;
                }
            }
            else{
                if(oki[xsaved][ysaved] == false){
                    que.push_back(make_pair(xsaved, ysaved));
                    oki[xsaved][ysaved] = true;
                }
            }
        }
        else{
            for(int yy = abs(Left); yy <= abs(Right); ++ yy)
                mat[x][yy] = '|';
            if(Left < 0) {
                if(oki[x][-Left] == false){
                    que.push_back({x,-Left});
                    oki[x][-Left] = true;
                }
        
            }
            if(Right < 0) {
        
                if(oki[x][-Right] == false){
                    que.push_back({x,-Right});
                    oki[x][-Right] = true;
                }
    
            }
        }
    }
    int sol = 0;
    for(int i = 0; i <= maximx; ++ i, out<<'\n')
        for(int j = minim; j <= maxim; ++ j){
            out<<mat[i][j];
            if(mat[i][j] == 's' || mat[i][j] == '|')
                ++ sol;
        }
    
    out<<sol - 1;
    
    
    return 0;
}
