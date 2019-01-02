#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <forward_list>
#define DIM 100003

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

long long n, playersNum, turnsNum;
long long score[DIM];

string sir;

list<long long> table;

void Next(list<long long>::iterator &it){
    ++ it;
    int aux = *it;
    if(it == table.end())
        it = table.begin();
}

void Prev(list<long long>::iterator &it){
    if(it == table.begin())
        it = table.end();
    -- it;
}

int main(int argc, const char * argv[]) {
    in>>playersNum;
    in>>sir>>sir>>sir>>sir>>sir;
    in>>turnsNum;
    int currentTurn = 2;
    table.push_back(0);
    table.push_back(1);
    int currentMarble = 1;
    int currentPlayer = 3;
    auto lastIt = table.begin();
    lastIt ++;
    int aux = *lastIt;
    while(currentTurn <= turnsNum){
        if(currentTurn % 23 == 0){
            score[currentPlayer] += currentTurn;
            int positionToErase = currentMarble - 7;
            if(positionToErase < 0)
                positionToErase = table.size() + positionToErase;
            
            auto it = lastIt;
            for(int i = 1; i <= 7; ++ i)
                Prev(it);
            score[currentPlayer] += *it;
            lastIt = it;
            Next(lastIt);
            table.erase(it);
            
            
            
            if(positionToErase == table.size())
                currentMarble = 0;
            else
                currentMarble = positionToErase;
            ++ currentTurn;
            ++ currentPlayer;
            if(currentPlayer > playersNum)
                currentPlayer = 1;
            continue;
        }
        int positionToAdd = (currentMarble + 2) % table.size();
        if(positionToAdd == 0){
            table.push_back(currentTurn);
            positionToAdd = table.size() - 1;
        }
        else{
            auto it = lastIt;
            aux = *table.begin();
            aux = *it;
            Next(it);
            aux = *it;
            Next(it);
            aux = *it;
            table.insert(it, currentTurn);
        }
        currentMarble = positionToAdd;
        ++ currentTurn;
        ++ currentPlayer;
        Next(lastIt);
        Next(lastIt);
        aux = *lastIt;
        if(currentPlayer > playersNum)
            currentPlayer = 1;
    }
    
    long long maxim = -1;
    for(int i = 1; i <= playersNum; ++ i)
        if(score[i] > maxim)
            maxim = score[i];
    out<<maxim;
//    for(auto it : table)
//        out<<it<<" ";
    
    return 0;
}
