#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ifstream in("file.in");
ofstream out("file.out");

int n, a, b, c;

string str;

int pointer, bound;

bool readd = 0;

struct operation{
    string type;
    int a, b, c;
};

int v[10];

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
    pointer = 0;
    //0 10551292 3 457027 457027
    v[0] = 0;
    v[1] = 10551292;
    v[2] = 3;
    v[3] = 10551292;
    v[4] = 10551292;
    v[5] = 1;
    /*
     if we generate the output we will see a cycle o the form
     0 10551292 2 457025 0 1 p: 3
     0 10551292 3 457025 457025 1 p: 4
     0 10551292 4 457025 0 1 p: 5
     0 10551292 5 457025 0 1 p: 6
     0 10551292 7 457025 0 1 p: 8
     0 10551292 8 457026 0 1 p: 9
     0 10551292 9 457026 0 1 p: 10
     0 10551292 10 457026 0 1 p: 11
     so when the pointer is 4 the value on the 4th position will be equal with the one on the 3rd
     position, but the 3rd position is incremented with 1 so at one point on the 4th position
     will be equal with the one at the 1st position
     because the 4th operation is exactly eqrr 4 1 4 when we get to that point something special
     happens. The position 0 is incremented with 1 and this cycle rebegins, but with a difference.
     On the 4th position is not the value from the 3rd position, is the double of it like:
     1 10551292 3 9 18 2 p: 4
     so now, only if 2 divides our big number a value will be added to the position 0. The thing
     is, the value added is equal to 2. This cycle goes on with 3, 4, etc like:
     1 10551292 3 9 27 2 p: 4
     ....
     1 10551292 3 10 30 2 p: 4
     ......
     and is clear that on the 0 position
     will be exactly the SUM OF DE DIVISORS of the big number and after we get after that value
     the cycle will not be able to affect the value from the position 0 because will never
     be equal with it again(because it will only get bigger than our number)
    */
    pointer = 4;
    while(ok){
        execute(pointer);
        if(pointer >= op.size())
            break;
        afis();
    }
    out<<v[0];
    return 0;
}
