#include <fstream>
#define DIM 1000

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int serialNum;
int mat[DIM][DIM];

long long getValue(int y, int x){
    long long val = 0;
    val = x + 10;
    long long rackID = val;
    val *= y;
    val += serialNum;
    val *= rackID;
    val = (val / 100) % 10;
    val -= 5;
    return val;
}

int getMat(int x, int y, int k){
    int aux = 0;
    for(int i = x; i <= x + k - 1; ++ i)
        for(int j = y; j <= y + k - 1; ++ j)
            aux += mat[i][j];
    return aux;
}

int main(int argc, const char * argv[]) {
    in>>serialNum;
    for(int i = 1; i <= 300; ++ i){
        for(int j = 1; j <= 300; ++ j){
            mat[i][j] = getValue(i, j);
        }
        
    }
    
    int maxim = -1e9, xMax, yMax, kMax;

        for(int i = 1; i <= 300 - 3 + 1; ++ i){
            for(int j = 1; j <= 300 - 3 + 1; ++ j){
                
                int current = getMat(i, j, 3);
                if(current > maxim){
                    maxim = current;
                    xMax = j;
                    yMax = i;
                }
            }
        }

    
    out<<xMax<<" "<<yMax;
    return 0;
}
