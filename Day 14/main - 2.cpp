#include <fstream>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, cnt, steps;
int v[70000000];
int sol[100];

void next(int &i){
    ++ i;
    if(i > n)
        i = 1;
}

int main(int argc, const char * argv[]) {
    //PART 1
    //
    in>>steps;
    for(int i = 1; i <= 6; ++ i)
        in>>sol[i];
    v[1] = 3;
    v[2] = 7;
    n = 2;
    int frst = 1;
    int scnd = 2;
    cnt = 0;
    while(n < 69900000){
        ++ cnt;
        int sum = v[frst] + v[scnd];
        if(sum < 10){
            v[++n] = sum;
        }
        else{
            v[++n] = sum / 10;
            v[++n] = sum % 10;
        }
        frst = frst + v[frst] + 1;
        frst %= n;
        if(frst == 0)
            frst = n;
        scnd = scnd + v[scnd] + 1;
        scnd %= n;
        if(scnd == 0)
            scnd = n;
    }
    for(int i = 1; i <= 69899990; ++ i){
        int ok = 1;
        for(int j = 1; j <= 6; ++ j){
            if(v[i + j - 1] != sol[j]){
                ok = 0;
                break;
            }
        }
        if(ok){
            out<<i - 1<<'\n';
            break;
        }
    }
//    for(int i = steps + 1; i <= steps + 10; ++ i)
//        out<<v[i];
    return 0;
}
