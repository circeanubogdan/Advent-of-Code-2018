#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define DIM 500

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

const int dim = 400;

int x, y, id;
int MatType[DIM][DIM], MatDist[DIM][DIM];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

struct node{
    int x, y, id;
};

node MakeNode(int x, int y, int id){
    node aux;
    aux.x = x;
    aux.y = y;
    aux.id = id;
    return aux;
}

queue<node> q;
vector<node> v;

bool matCheck[DIM][DIM];

bool Check(node n){
    return (n.x > 0 && n.x < dim && n.y > 0 && n.y < dim);
}

int viz[100];

char c;

int main(int argc, const char * argv[]) {
    
    for(int i = 1; i <= dim; ++ i)
        for(int j = 1; j <= dim; ++ j)
            MatDist[i][j] = 1e9;
    while(in>>y>>c>>x){
        ++ id;
        MatType[x][y] = id;
        MatDist[x][y] = 0;
        q.push(MakeNode(x, y, id));
        v.push_back(MakeNode(x, y, id));
    }
    //    PART 1
    
        while(!q.empty()){
            node currNode = q.front();
            q.pop();
            node nextNode;
            nextNode.id = currNode.id;
            for(int i = 0; i < 4; ++ i){
                nextNode.x = currNode.x + dx[i];
                nextNode.y = currNode.y + dy[i];
                if(abs(MatDist[nextNode.x][nextNode.y]) == abs(MatDist[currNode.x][currNode.y]) + 1 && MatType[nextNode.x][nextNode.y] != currNode.id){
                    MatDist[nextNode.x][nextNode.y] = -MatDist[nextNode.x][nextNode.y];
                    MatType[nextNode.x][nextNode.y] = -1;
                }
                if(abs(MatDist[nextNode.x][nextNode.y]) > abs(MatDist[currNode.x][currNode.y]) + 1 && Check(nextNode)){
                    MatDist[nextNode.x][nextNode.y] = abs(MatDist[currNode.x][currNode.y]) + 1;
                    MatDist[currNode.x][currNode.y] = abs(MatDist[currNode.x][currNode.y]);
                    MatType[nextNode.x][nextNode.y] = nextNode.id;
                    q.push(nextNode);
                }
            }
        }
    
        for(int i = 1; i < dim; ++ i){
            viz[MatType[1][i]] = -1;
            viz[MatType[i][1]] = -1;
            viz[MatType[dim - 1][i]] = -1;
            viz[MatType[i][dim - 1]] = -1;
        }
    
        int maxim = -1;
        for(int i = 1; i < dim; ++ i){
            for(int j = 1; j < dim; ++ j){
                if(viz[MatType[i][j]] != -1)
                    ++ viz[MatType[i][j]];
                if(viz[MatType[i][j]] > maxim)
                    maxim = viz[MatType[i][j]];
            }
        }
    
    out<<maxim;
    
    
    
    
    return 0;
}
