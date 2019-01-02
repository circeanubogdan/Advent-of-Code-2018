#include <fstream>
#include <vector>
#define DIM 2002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, sol;
int mat[DIM][DIM];

char c;

struct OP{
    int up, left, right, down, id;
};

vector<OP> op;

OP MakeOp(int id, int left, int up, int right, int down){
    OP aux;
    aux.down = down;
    aux.up = up;
    aux.left = left;
    aux.right = right;
    aux.id = id;
    return aux;
}

int main(int argc, const char * argv[]) {
    in>>c;
    while(true){
        int id = 0, up = 0, left = 0, right = 0, down = 0;
        while(in>>c){
            if(c < '0'|| c > '9')
                break;
            id = id * 10 + c - '0';
        }
        while(in>>c){
            if(c < '0'|| c > '9')
                break;
            left = left * 10 + c - '0';
        }
        ++ left;
        
        while(in>>c){
            if(c < '0'|| c > '9')
                break;
            up = up * 10 + c - '0';
        }
        ++ up;
        
        while(in>>c){
            if(c < '0'|| c > '9')
                break;
            right = right * 10 + c - '0';
        }
        right = right + left - 1;
        
        int ok = 0;
        while(in>>c){
            if(c < '0'|| c > '9'){
                ok = 1;
                break;
            }
            down = down * 10 + c - '0';
        }
        down = down + up - 1;
        
        for(int i = up; i <= down; ++ i){
            for(int j = left; j <= right; ++ j){
                if(mat[i][j] == 0){
                    mat[i][j] = id;
                }
                else{
                    mat[i][j] = -1;
                }
            }
        }
        
        op.push_back(MakeOp(id, left, up, right, down));
        
        if(ok == 0){
            break;
        }
        
    }
    
    sol = 0;
    
    for(int i = 0; i < 1000; ++ i)
        for(int j = 0; j < 1000; ++ j)
            if(mat[i][j] == -1)
                ++ sol;
    
    out<<sol;
    

    
    
    
    
    
    return 0;
}
