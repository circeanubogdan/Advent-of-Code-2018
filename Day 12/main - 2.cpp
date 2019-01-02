#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n;
string str, state[2], rule1, rule2;

vector<string> rulz;

int main(int argc, const char * argv[]) {
    in>>str>>str>>state[0];
    while(in>>rule1){
        in>>str;
        in>>rule2;
        rulz.push_back(rule1);
        rulz.back().push_back(rule2.back());
    }
    for(int i = 1; i <= 1100; ++ i){
        state[0].push_back('.');
        state[0].insert(state[0].begin(), '.');
    }
    state[1] = state[0];
    
    int t = 0;
    int Sol = 0;
    for(int i = 0; i < state[t].size(); ++ i){
        if(state[1 - t][i] == '#'){
            Sol += i - 1100;
        }
    }
    out<<Sol<<" ";
    for(int k = 1; k <= 1000; ++ k){
        
        //out<<state[t]<<'\n';
        state[1 - t][0] = state[1 - t][1] = '.';
        for(int i = 2; i <= state[t].size() - 3; ++ i){
            state[1 - t][i] = '.';
            for(int counter = 0; counter < rulz.size(); ++ counter){
                string it = rulz[counter];
                int ok = 1;
                for(int j = i - 2, rulcnt = 0; j <= i + 2; ++ j, ++ rulcnt){
                    if(state[t][j] != it[rulcnt]){
                        ok = 0;
                        break;
                    }
                }
                if(ok == 1){
                    state[1 - t][i] = it.back();
                }
            }
        }
        t = 1 - t;
        int sol = 0;
        for(int i = 0; i < state[1 - t].size(); ++ i){
            if(state[t][i] == '#'){
                sol += i - 1100;
            }
        }
        out<<sol<<'\n';
    }
    
    long long sol = 13287;
    long long steps = 50000000000 - 225;
    sol += steps * (long long)53;
    out<<sol;
    
    
    return 0;
}
