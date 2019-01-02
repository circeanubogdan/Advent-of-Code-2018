#include <fstream>
#include <string>
#include <cmath>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n;
string str[3];

int main(int argc, const char * argv[]) {
//    PART 1
//
//    in>>str[1];
//    int t = 1;
//    int ok = 1;
//    while(ok){
//        ok = 0;
//        for(int i = 1; i < str[1].size(); ++ i){
//            if(abs(str[1][i] - str[1][i - 1]) == 32){
//                str[1].erase(i, 1);
//                str[1].erase(i - 1, 1);
//                ok = 1;
//            }
//        }
//    }
//
//    out<<str[1].size();
    
    
    
    in>>str[1];
    int t = 1;
    int ok = 1;
    int minim = 1e9;
    for(int letter = 'a'; letter <= 'z'; ++ letter){
        str[2].clear();
        for(int i = 0; i < str[1].size(); ++ i){
            if(str[1][i] != letter && str[1][i] != letter - 32)
                str[2].push_back(str[1][i]);
        }
        ok = 1;
        while(ok){
            ok = 0;
            for(int i = 1; i < str[2].size(); ++ i){
                if(abs(str[2][i] - str[2][i - 1]) == 32){
                    str[2].erase(i, 1);
                    str[2].erase(i - 1, 1);
                    ok = 1;
                }
            }
        }
        if(str[2].size() < minim){
            minim = str[2].size();
        }
    }

    out<<minim;
    
    
    
    return 0;
}
