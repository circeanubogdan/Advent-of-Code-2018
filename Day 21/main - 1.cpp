#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, a, b, c;

string str;

int pointer, bound;

bool readd = 0;

struct operation{
    string type;
    int a, b, c;
};

long long v[30];

vector<operation> op;

operation MakeOp(string s, int a, int b, int c){
    operation aux;
    aux.type = s;
    aux.a = a;
    aux.b = b;
    aux.c = c;
    return aux;
}

void addr(int a, int b, int c){
    v[c] = v[a] + v[b];
}

void addi(int a, int b, int c){
    v[c] = v[a] + b;
}

void mulr(int a, int b, int c){
    v[c] = v[a] * v[b];
}

void muli(int a, int b, int c){
    v[c] = v[a] * b;
}

void banr(int a, int b, int c){
    v[c] = (v[a] & v[b]);
}

void bani(int a, int b, int c){
    v[c] = (v[a] & b);
}

void borr(int a, int b, int c){
    v[c] = (v[a] | v[b]);
}

void bori(int a, int b, int c){
    v[c] = (v[a] | b);
}

void setr(int a, int b, int c){
    v[c] = v[a];
}

void seti(int a, int b, int c){
    v[c] = a;
}

void gtir(int a, int b, int c){
    v[c] = (a > v[b]);
}

void gtri(int a, int b, int c){
    v[c] = (v[a] > b);
}

void gtrr(int a, int b, int c){
    v[c] = (v[a] > v[b]);
}

void eqir(int a, int b, int c){
    v[c] = (a == v[b]);
}

void eqri(int a, int b, int c){
    v[c] = (v[a] == b);
}

void eqrr(int a, int b, int c){
    v[c] = (v[a] == v[b]);
}

void execute(int id){
    v[bound] = id;
    if(op[id].type == "addi"){
        addi(op[id].a, op[id].b, op[id].c);
    }
    if(op[id].type == "addr"){
        addr(op[id].a, op[id].b, op[id].c);
    }
    if(op[id].type == "seti"){
        seti(op[id].a, op[id].b, op[id].c);
    }
    if(op[id].type == "setr"){
        setr(op[id].a, op[id].b, op[id].c);
    }
    if(op[id].type == "mulr")
        mulr(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "muli")
        muli(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "banr")
        banr(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "bani")
        bani(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "borr")
        borr(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "bori")
        bori(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "gtir")
        gtir(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "gtri")
        gtri(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "gtrr")
        gtrr(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "eqir")
        eqir(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "eqrr")
        eqrr(op[id].a, op[id].b, op[id].c);
    if(op[id].type == "eqri")
        eqri(op[id].a, op[id].b, op[id].c);
    pointer = v[bound] + 1;
}

void afis(){
    for(int i = 0; i < 6; ++ i)
        out<<v[i]<<" ";
    out<<"p: "<<pointer;
    out<<"\n";
}

bool check(){
    for(int i = 0; i < 6; ++ i)
        if(v[i] < 0)
            return true;
    return false;
}

set <long long> s;

int main(int argc, const char * argv[]) {
    
    while(in>>str){
        if(readd == 0){
            in>>pointer;
            bound = pointer;
            readd = 1;
            continue;
        }
        in>>a>>b>>c;
        op.push_back(MakeOp(str, a, b, c));
    }
    int ok = 1;
    long long minim = 1e9, valuemin = -1, Max = -1e9, ant = -1;
    for(int i = 0; i <= 0; ++ i){
        v[0] = 0;
        v[1] = v[2] = v[3] = v[4] = v[5] = 0;
        pointer = 0;
        int found = 0;
        long long cnt  = 0;
        while(ok){
            if(pointer == 28){
                //task1
                out<<v[1];
                return 0;
                if(s.find(v[1]) != s.end()){
                    out<<ant;
                    return 0;
                }
                else
                    s.insert(v[1]);
                ant = v[1];
            }
            execute(pointer);
            ++ cnt;
        }
        if(found){
            if(cnt + 1 < minim){
                minim = cnt + 1;
                valuemin = i;
            }
        }
    }
    out<<Max;
    
    return 0;
}
