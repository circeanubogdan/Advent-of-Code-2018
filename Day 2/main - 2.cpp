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
        for(auto box : boxes){
            int cnt = 0;
            for(int i = 0; i < s.size(); ++ i){
                if(s[i] != box[i]){
                    ++ cnt;
                }
            }
            if(cnt == 1){
                for(int i = 0; i < s.size(); ++ i){
                    if(s[i] == box[i])
                        sol.push_back(s[i]);
                }
                out<<sol;
                return 0;
            }
        }
        boxes.push_back(s);
        
    }
    out<<cntLetters[2] * cntLetters[3];
    return 0;
}
