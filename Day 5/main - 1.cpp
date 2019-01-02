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
    in>>str[1];
    int t = 1;
    int ok = 1;
    while(ok){
        ok = 0;
        for(int i = 1; i < str[1].size(); ++ i){
            if(abs(str[1][i] - str[1][i - 1]) == 32){
                str[1].erase(i, 1);
                str[1].erase(i - 1, 1);
                ok = 1;
            }
        }
    }

    out<<str[1].size();
    
    
    
    
    
    
    return 0;
}
