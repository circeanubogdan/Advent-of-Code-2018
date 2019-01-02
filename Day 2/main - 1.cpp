#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int cntLetters[4];

string s, sol;

vector<string> boxes;

void check(string s, int appearance){
    int cnt;
    for(int i = 'a'; i <= 'z'; ++ i){
        cnt = 0;
        for(auto it : s){
            if(it == i)
                ++ cnt;
        }
        if(cnt == appearance){
            ++cntLetters[appearance];
            break;
        }
    }
}

int main(int argc, const char * argv[]) {
    while(in>>s){
        check(s, 2);
        check(s, 3);
    }
    
    out<<cntLetters[2] * cntLetters[3];
    return 0;
}
