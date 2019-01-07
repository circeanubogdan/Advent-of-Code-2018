#include <fstream>
#include <string>
#include <deque>
#define DIM 8002
#define MOD 20183
#define INF 1e9;

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

string str;

int n, depth, targetx, targety;
long long mat[DIM][DIM], erosion[DIM][DIM];

struct region{
    int none, torch, climb;
};

region dp[DIM][DIM];

char c;

bool viz[DIM][DIM];

deque<pair<int, int> > q;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool check(int x, int y){
    return x >= 0 && y >= 0 && x <= 7 * targetx && y <= 7 * targety;
}

bool diffferent(region a, region b){
    return (a.torch != b.torch) || (a.climb != b.climb) || (a.none != b.none);
}

int main(int argc, const char * argv[]) {
    in>>str;
    in>>depth;
    in>>str;
    in>>targetx>>c>>targety;
    for(int i = 0; i <= 7 * targetx + 1; ++ i)
        for(int j = 0; j <= 7 * targety + 1; ++ j)
            mat[i][j] = -1;
    mat[targetx][targety] = mat[0][0] = 0;
    int sum = 0;
    for(int i = 0; i <= 7 * targetx + 1; ++ i)
        for(int j = 0; j <= 7 * targety + 1; ++ j){
            if(mat[i][j] == -1){
                if(i == 0)
                    erosion[i][j] = (1LL * j * 48271) % MOD;
                if(j == 0)
                    erosion[i][j] = (1LL * i * 16807) % MOD;
                if(i != 0 && j != 0)
                    erosion[i][j] = (1LL * erosion[i - 1][j] * erosion[i][j - 1]) % MOD;
                
            }
            erosion[i][j] = (erosion[i][j] + depth) % MOD;
            mat[i][j] = erosion[i][j] % 3;
            
            
           
        }

//    PART 1
//
    for(int i = 0; i <= targetx; ++ i)
        for(int j = 0; j <= targety; ++ j)
             sum += mat[i][j];
    out<<"PART 1"<<sum<<"\n\n";
    
    for(int i = 0; i <= 7 * targetx + 1; ++ i)
        for(int j = 0; j <= 7 * targety + 1; ++ j)
            dp[i][j].climb = dp[i][j].none = dp[i][j].torch = INF;
    
    dp[0][0].torch = 0;
    if(mat[0][0] != 2)
        dp[0][0].climb = 7;
    if(mat[0][0] != 0)
        dp[0][0].none = 7;
    
    q.push_back({0, 0});
    viz[0][0] = true;
    
    while(!q.empty()){
        int xcur = q.front().first;
        int ycur = q.front().second;
        q.pop_front();
        viz[xcur][ycur] = 0;
        
        for(int i = 0; i < 4; ++ i){
            int x = xcur + dx[i];
            int y = ycur + dy[i];
            if(!check(x, y))
                continue;
            region start = dp[x][y];
            if(mat[x][y] != 2)
                dp[x][y].climb = min(dp[x][y].climb, dp[xcur][ycur].climb + 1);
            if(mat[x][y] != 1)
                dp[x][y].torch = min(dp[x][y].torch, dp[xcur][ycur].torch + 1);
            if(mat[x][y] != 0)
                dp[x][y].none = min(dp[x][y].none, dp[xcur][ycur].none + 1);
            
            if(mat[x][y] != 2)
                dp[x][y].climb = min(dp[x][y].climb, min(dp[x][y].none + 7, dp[x][y].torch + 7));
            if(mat[x][y] != 1)
                dp[x][y].torch = min(dp[x][y].torch, min(dp[x][y].none + 7, dp[x][y].climb + 7));
            if(mat[x][y] != 0)
                dp[x][y].none = min(dp[x][y].none, min(dp[x][y].climb + 7, dp[x][y].torch + 7));
            if(diffferent(start, dp[x][y])){
                if(viz[x][y] == false){
                    viz[x][y] = true;
                    q.push_back({x, y});
                }
            }
        }
        
    }
    
//    for(int i = 0; i <= targetx + 10; ++ i, out<<'\n')
//        for(int j = 0; j <= targety + 10; ++ j)
//            out<<min(dp[i][j].torch, min(dp[i][j].climb, dp[i][j].none))<<" ";
            
    out<<"PART 2:"<<min(dp[targetx][targety].torch, min(dp[targetx][targety].climb + 7, dp[targetx][targety].none + 7))<<" ";
    
    
    return 0;
}
