#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define DIM 1002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int v[6];

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

string str;
char c;
int type, A, B, C;
int result[6], init[6], F[20];
int totalSol;

vector< vector<string>::iterator > toErase;

int readNum(){
    //in>>c;
    int aux = 0;
    while(in>>c){
        if(c < '0' || c > '9')
            break;
        aux = aux * 10 + c - '0';
    }
    return aux;
}

void initialize(){
    for(int i = 0; i < 4; ++ i)
        v[i] = init[i];
}

bool check(){
    for(int i = 0; i < 4; ++ i)
        if(v[i] != result[i])
            return 0;
    return 1;
}

vector <string> op[100];
string o[18];

int main(int argc, const char * argv[]) {
    while(in>>str){
        if(str == "-")
            break;
        in>>c;
        for(int i = 0; i < 4; ++ i)
            init[i] = v[i] = readNum();
        
        in>>type>>A>>B>>C;
        in>>str;
        in>>c;
        int debugaici;
        for(int i = 0; i < 4; ++ i)
            result[i] = readNum();
        if(type == 1){
            debugaici = 12;
            for(int i = 0; i < 4; ++ i)
                cout<<v[i]<<" ";
            cout<<'\n';
            for(int i = 0; i < 4; ++ i)
                cout<<result[i]<<" ";
            cout<<'\n';
            debugaici = 12;
        }
        
        int sol = 0;
        
        int ok = 0;
        if(op[type].empty())
            ok = 1;
        
        for(int i = 0; i < 20; ++ i)
            F[i] = 0;
        
        initialize();
        addi(A, B, C);
        if(check()){
            //++ sol;
            int found = 0;
            
            if(ok){
                op[type].push_back("addi");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "addi"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        addr(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("addr");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "addr"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        muli(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("muli");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "muli"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        mulr(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("mulr");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "mulr"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        banr(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("banr");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "banr"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        bani(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("bani");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "bani"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        borr(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("borr");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "borr"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        bori(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("bori");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "bori"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        setr(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("setr");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "setr"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        seti(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("seti");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "seti"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        gtir(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("gtir");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "gtir"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        gtri(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("gtri");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "gtri"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        gtrr(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("gtrr");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "gtrr"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        eqir(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("eqir");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "eqir"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        eqri(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("eqri");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "eqri"){
                        F[i] = 1;
                    }
            }
        }
        
        initialize();
        eqrr(A, B, C);
        if(check()){
            //++ sol;
            if(ok){
                op[type].push_back("eqrr");
            }
            else{
                for(int i = 0; i < op[type].size(); ++ i)
                    if(op[type][i] == "eqrr"){
                        F[i] = 1;
                    }
            }
        }
        if(ok == 0){
            int i = 0;
            for(auto it = op[type].begin(); it != op[type].end(); ++ it, ++i){
                if(F[i] == 0){
                    if(type == 1){
                        debugaici = 20;
                    }
                    op[type][i] = "";
                }
            }
        }
        
//        for(i = 0; i < toErase.size(); ++ i){
//            op[type].erase(toErase[i]);
//        }
        
//      PART 1
//
//        if(sol >= 3)
//            totalSol ++;
        
    }
    //PART 1
    //out<<totalSol;
    v[1] = v[2] = v[3] = v[4] = 0;
    for(int i = 0; i <= 15; ++ i){
        int k = 0;
        for(auto it : op[i])
            if(it != ""){
                o[i] = it;
                ++ k;
            }
    }
    
    o[0] = "mulr";
    o[1] = "eqri";
    o[2] = "setr";
    o[3] = "eqrr";
    o[4] = "gtrr";
    o[5] = "muli";
    o[6] = "borr";
    o[7] = "bani";
    o[8] = "addr";
    o[9] = "banr";
    o[10] = "eqir";
    o[11] = "gtir";
    o[12] = "addi";
    o[13] = "gtri";
    o[14] = "seti";
    o[15] = "bori";
    int kk = 0;
    while(in>>type){
        in>>A>>B>>C;
        if(o[type] == "addr")
            addr(A, B, C);
        if(o[type] == "addi")
            addi(A, B, C);
        if(o[type] == "mulr")
            mulr(A, B, C);
        if(o[type] == "muli")
            muli(A, B, C);
        if(o[type] == "banr")
            banr(A, B, C);
        if(o[type] == "bani")
            bani(A, B, C);
        if(o[type] == "borr")
            borr(A, B, C);
        if(o[type] == "bori")
            bori(A, B, C);
        if(o[type] == "setr")
            setr(A, B, C);
        if(o[type] == "seti")
            seti(A, B, C);
        if(o[type] == "gtir")
            gtir(A, B, C);
        if(o[type] == "gtri")
            gtri(A, B, C);
        if(o[type] == "gtrr")
            gtrr(A, B, C);
        if(o[type] == "eqir")
            eqir(A, B, C);
        if(o[type] == "eqrr")
            eqrr(A, B, C);
        if(o[type] == "eqri")
            eqri(A, B, C);
        for(int i = 0; i < 4; ++ i)
            cout<<v[i]<<" ";
        cout<<"\n\n";
        int debugaici = 1;
        ++kk;
        if(kk == 899){
            debugaici = 10;
        }
    }
    
    out<<v[0];
    
    return 0;
}
