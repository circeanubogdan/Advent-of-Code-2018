#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n;

string str;
string mat[200], matAnt[200];

int di[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dj[] = {1, -1, 0, 0, 1, 1, -1, -1};

void afis(){
    for(int i = 1; i <= n; ++ i, cout<<'\n')
        for(int j = 1; j < mat[i].size() - 1; ++ j)
            cout<<mat[i][j];
    cout<<"\n\n\n";
}

void Copy(){
    for(int i = 0; i <= n + 1; ++ i){
        for(int j= 0; j < mat[i].size(); ++ j)
            matAnt[i][j] = mat[i][j];
    }
}

int main(int argc, const char * argv[]) {
    
    while(in>>str){
        ++ n;
        mat[n].push_back(0);
        for(auto it : str)
            mat[n].push_back(it);
        mat[n].push_back(0);
    };
    for(int i = 0; i < mat[1].size(); ++ i){
        mat[0].push_back(0);
        mat[n + 1].push_back(0);
    }
    for(int i = 0; i <= n + 1; ++ i)
        for(int j = 0; j < mat[i].size(); ++ j)
            matAnt[i].push_back(mat[i][j]);
    
    afis();
    for(int minute = 1; minute <= 10000; ++ minute){
        for(int i = 1; i <= n; ++ i){
            
            for(int j = 1; j < mat[i].size() - 1; ++ j){
                int trees = 0, lumber = 0, open = 0;
                for(int it = 0; it < 8; ++ it){
                    int ii = i + di[it];
                    int jj = j + dj[it];
                    switch(matAnt[ii][jj]){
                        case '|': ++ trees; break;
                        case '.': ++ open; break;
                        case '#': ++ lumber; break;
                    }
                }
                if(matAnt[i][j] == '.'){
                    if(trees >= 3)
                        mat[i][j] = '|';
                }
                if(matAnt[i][j] == '|'){
                    if(lumber >= 3)
                        mat[i][j] = '#';
                }
                if(matAnt[i][j] == '#'){
                    if(lumber < 1 || trees < 1)
                        mat[i][j] = '.';
                }
            }
        }
        Copy();
        int totalTrees = 0, totalLumber = 0;
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j < mat[i].size() - 1; ++ j){
                if(mat[i][j] == '|')
                    totalTrees ++;
                if(mat[i][j] == '#')
                    totalLumber ++;
            }
        out<<totalLumber * totalTrees<<'\n';
    }
    afis();
    int totalTrees = 0, totalLumber = 0;
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j < mat[i].size() - 1; ++ j){
            if(mat[i][j] == '|')
                totalTrees ++;
            if(mat[i][j] == '#')
                totalLumber ++;
        }
    out<<totalLumber * totalTrees;
    
    /*
     line 9962
     199076
     206375
     210576
     208658
     212520
     213395
     216660
     210368
     203794
     195510
     180873
     177126
     176320
     167862
     169218
     170428
     172898
     169470
     165780
     169260
     169524
     168935
     173952
     179622
     180299
     188155
     195776
     192198
     
     28 cases
     iterating through them
     */
    int current = 9962;
    while(current < 1000000000)
        current += 28;
    cout<<current;
    /*
     current has value 1000000002
     so the case number 27 will be the right one (195776)
    */
    
    return 0;
}
