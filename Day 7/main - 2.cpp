#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#define DIM 300

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n;
int grad[DIM], w[10], Free[10], project[10];
string str;
char sir[100];
vector<int> graf[DIM];
vector<int> sol;

bool root[DIM], viz[DIM], exists[DIM];

deque<int> q;
vector<int> freeWorkers;

int main(int argc, const char * argv[]) {
    int cnt = 0;
    while(in>>str){
        ++ cnt;
        in>>str;
        int x = 0, y = 0;
        for(auto it : str){
            x = x * 10 + it - 'A';
        }
        in>>str>>str>>str>>str>>str>>str;
        for(auto it : str){
            y = y * 10 + it - 'A';
        }
        in>>str>>str;
        graf[x].push_back(y);
        exists[x] = true;
        exists[y] = true;
        ++ grad[y];
    }
   
    for(int i = 0; i <= 30; ++ i){
        if(exists[i])
            ++ n;
        if(!graf[i].empty()){
            sort(graf[i].begin(), graf[i].end());
        }
    }
    
    for(int i = 0; i <= 30; ++ i){
        if(grad[i] == 0 && exists[i] == true)
            q.push_back(i);
    }
//    PART 1
//
//    while(!q.empty()){
//        int nod = q.front();
//        q.pop_front();
//        sol.push_back(nod);
//        for(auto it : graf[nod]){
//            -- grad[it];
//            if(grad[it] == 0)
//                q.push_back(it);
//        }
//        sort(q.begin(), q.end());
//    }
//
//
//
//    for(auto it : sol)
//        out<<(char)(it + 'A');
 
    sort(q.begin(), q.end());
    for(int i = 1; i <= 5; ++ i){
        freeWorkers.push_back(i);
        Free[i] = 1;
    }
    int sum = 0;
    while(!q.empty() || freeWorkers.size() < 5){
        int last = q.back();
        int cnt = 0;
        for(int i = 0; !freeWorkers.empty() && i < q.size(); ++ i){
            ++ cnt;
            int nod = q[i];
            w[freeWorkers.back()] = 60 + q[i] + 1;
            project[freeWorkers.back()] = q[i];
            Free[freeWorkers.back()] = 0;
            freeWorkers.pop_back();
            if(nod == last)
                break;
        }
        while(cnt--)
            q.pop_front();
        int minim = 200;
        for(int i = 1; i <= 5; ++ i){
            if(Free[i] == 0 && w[i] < minim)
                minim = w[i];
        }
        for(int i = 1; i <= 5; ++ i){
            if(Free[i] == 0){
                w[i] -= minim;
                if(w[i] == 0){
                    Free[i] = 1;
                    freeWorkers.push_back(i);
                    for(auto it : graf[project[i]]){
                        -- grad[it];
                        if(grad[it] == 0)
                            q.push_back(it);
                    }
                }
            }
        }
        sum += minim;
        sort(q.begin(), q.end());
    }
    while(freeWorkers.size() < 5){
        int minim = 200;
        for(int i = 1; i <= 5; ++ i){
            if(Free[i] == 0 && w[i] < minim)
                minim = w[i];
        }
        for(int i = 1; i <= 5; ++ i){
            if(Free[i] == 0){
                w[i] -= minim;
                if(w[i] == 0){
                    Free[i] = 1;
                    freeWorkers.push_back(i);
                }
            }
        }
        sum += minim;
    }
    out<<sum;
    
    
    return 0;
    
}
