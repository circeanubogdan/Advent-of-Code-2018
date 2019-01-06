#include <fstream>
#include <algorithm>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, cartCnt = 1;

struct cart{
    int x, y;
    int dx, dy;
    int intersections;
    int crashed;
}cart[50];

string str, mat[1000];

pair<int, int> checkForCrash(){
    pair<int, int> sol;
    sol.first = 0;
    sol.second = 0;
    for(int i = 1; i < cartCnt; ++ i){
        if(cart[i].crashed)
            continue;
        for(int j = i + 1; j <= cartCnt; ++ j){
            if(cart[j].crashed)
                continue;
            if(cart[i].x == cart[j].x && cart[i].y == cart[j].y){
                sol.first = cart[i].x;
                sol.second = cart[i].y;
                cart[i].crashed = 1;
                cart[j].crashed = 1;
            }
                
        }
    }
    return sol;
}

bool cmp(struct cart a, struct cart b){
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

void turnLeft(struct cart &c){
    if(c.dx == 1){
        c.dx = 0;
        c.dy = 1;
    }
    else if(c.dx == -1){
        c.dx = 0;
        c.dy = -1;
    }
    else if(c.dy == 1){
        c.dy = 0;
        c.dx = -1;
    }
    else{
        c.dy = 0;
        c.dx = 1;
    }
    
}

void turnRight(struct cart &c){
    if(c.dx == 1){
        c.dx = 0;
        c.dy = -1;
    }
    else if(c.dx == -1){
        c.dx = 0;
        c.dy = 1;
    }
    else if(c.dy == 1){
        c.dy = 0;
        c.dx = 1;
    }
    else{
        c.dy = 0;
        c.dx = -1;
    }

}

int crashes = 0;

int main(int argc, const char * argv[]) {
    int k = 0;
    while(getline(in, str)){
        mat[++k] = str;
        for(int i = 0; i < str.size(); ++ i){
            switch (str[i]) {
                case '<':
                    cart[cartCnt].x = k;
                    cart[cartCnt].y = i;
                    cart[cartCnt].dx = 0;
                    cart[cartCnt++].dy = -1;
                    break;
                case '>':
                    cart[cartCnt].x = k;
                    cart[cartCnt].y = i;
                    cart[cartCnt].dx = 0;
                    cart[cartCnt++].dy = 1;
                    break;
                case 'v':
                    cart[cartCnt].x = k;
                    cart[cartCnt].y = i;
                    cart[cartCnt].dx = 1;
                    cart[cartCnt++].dy = 0;
                    break;
                case '^':
                    cart[cartCnt].x = k;
                    cart[cartCnt].y = i;
                    cart[cartCnt].dx = -1;
                    cart[cartCnt++].dy = 0;
                    break;
            }
        }
    }
    -- cartCnt;
    int okk = 1;
    while(okk){
        
        
        for(int i = 1; i <= cartCnt; ++ i){
            if(cart[i].crashed)
                continue;
            cart[i].x += cart[i].dx;
            cart[i].y += cart[i].dy;
            
            if(mat[cart[i].x][cart[i].y] == '+'){
                ++ cart[i].intersections;
                if(cart[i].intersections % 3 == 1)
                    turnLeft(cart[i]);
                if(cart[i].intersections % 3 == 0)
                    turnRight(cart[i]);
            }
            
            if(mat[cart[i].x][cart[i].y] == '/'){
                if(cart[i].dx == 0){
                    turnLeft(cart[i]);
                }
                else{
                    turnRight(cart[i]);
                }
            }
            
            if(mat[cart[i].x][cart[i].y] == '\\'){
                if(cart[i].dx == 0){
                    turnRight(cart[i]);
                }
                else{
                    turnLeft(cart[i]);
                }
            }
            
            pair<int, int> zero = {0, 0}, currentCrash = checkForCrash();
            
            if(currentCrash != zero){
                out<<currentCrash.second<<" "<<currentCrash.first - 1;
                return 0;
                crashes += 2;
                if(cartCnt - crashes == 1){
                    okk = 0;
                }
                    
            }
        }
        sort(cart + 1, cart + cartCnt + 1, cmp);
    }
    for(int i = 1; i <= cartCnt; ++ i){
        if(cart[i].crashed == 0){
           // out<<cart[i].y<<" "<<cart[i].x - 1;
            return 0;
        }
    }
    return 0;
}
