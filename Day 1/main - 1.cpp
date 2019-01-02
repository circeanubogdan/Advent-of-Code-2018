#include <fstream>
#include <vector>
#define DIM 1000002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int sum, x, sgn;
char c;
bool frequency[DIM];
int value = 500000;
bool ok = false;

vector<int> op;

int main(int argc, const char * argv[]) {
    
    while(in>>c){
        if(c == '+' || c == '-'){
            if(ok)
                op.push_back(x * sgn);
            ok = true;
            x = 0;
            switch (c){
                case '+': sgn = 1;  break;
                case '-': sgn = -1; break;
            }
        }
        else
            x = x * 10 + c - '0';
    }
    op.push_back(x * sgn);
    int i = 0;
    ok = true;
    sum = 0;
    for(int i = 0; i < op.size(); ++ i){
        sum += op[i];
    }
    out<<sum;
   
    return 0;
}
