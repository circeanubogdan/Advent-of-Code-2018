#include <fstream>
#include <vector>
#define DIM 10002

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

int n, s, x;
vector<int> graf[DIM], meta[DIM];

void read(int father){
    ++ n;
    int nod = n;
    int numNodes, numMeta;
    in>>numNodes>>numMeta;
    for(int i = 1; i <= numNodes; ++ i){
        read(nod);
    }
    for(int i = 1; i <= numMeta; ++ i){
        in>>x;
        s += x;
        meta[nod].push_back(x);
    }
    graf[father].push_back(nod);
}

int calc(int nod){
    int localS = 0;
    if(graf[nod].size() == 0){
        for(auto it : meta[nod])
            localS += it;
        return localS;
    }
    
    for(int i = 0; i < meta[nod].size(); ++ i){
        if(graf[nod].size() >= meta[nod][i] && meta[nod][i] > 0){
            localS += calc(graf[nod][meta[nod][i] - 1]);
        }
    }
    return localS;
}

int main(int argc, const char * argv[]) {
    read(0);
    //PART 1
    out<<s;

    return 0;
}
