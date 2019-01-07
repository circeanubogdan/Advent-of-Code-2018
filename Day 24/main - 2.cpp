/*
 
 for this to work you have to generate the input in the following way:
 the number n followed by n groups for the immune ssytem and then the number m followed by m groups
 for the group the transformation goes as:
 
 2913 units each with 30594 hit points (weak to radiation; immune to cold, fire) with an attack that does 20 fire damage at initiative 1
 
 2913 30594           //  (number of units) (hit points)
 1 radiation          //  (number of weaknesses -0 if none- ) (weakness1, weakness2...)
 2 cold fire          //  (number of immunities -0 if none- ) (immunity1, immunity2...)
 20 1 fire            //  (attack)  (number of types -most of the times is just 1-) (type)
 1                    //  (initiative)
 
 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <deque>

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

struct group{
    int attack;
    int hp;
    int troops;
    int initiative;
    string attackType;
    string type;
    vector <string> immune;
    vector <string> weak;
};

int ok = 0;

group MakeGroup(string type, int attack, int hp, int troops, int initiative, string attackType, vector<string> weak, vector<string> immune){
    group aux;
    aux.type = type;
    aux.attack = attack;
    aux.hp = hp;
    aux.troops = troops;
    aux.initiative = initiative;
    aux.attackType = attackType;
    aux.weak = weak;
    aux.immune = immune;
    return aux;
}

bool cmp(group a, group b){
    if(a.attack * a.troops == b.attack * b.troops)
        return a.initiative > b.initiative;
    return a.attack * a.troops > b.attack * b.troops;
}

vector <group> groups, initGroups, initialState;

bool cmpQueue(pair<int, int> a, pair<int, int> b){
    return groups[a.first].initiative > groups[b.first].initiative;
}

int n, nr, hp, attack, k, initiative;
string attackType;
char c;
string str, type;
bool viz[100];

deque<pair<int, int> > attackQueue;

bool check(){
    int nrImune = 0, nrInfection = 0;
    for(int i = 0; i < groups.size(); ++ i){
        if(groups[i].type == "immune" && groups[i].troops > 0)
            nrImune += groups[i].troops;
        if(groups[i].type == "infection" && groups[i].troops > 0)
            nrInfection += groups[i].troops;
    }
    return (nrImune != 0) && (nrInfection != 0);
}

bool equals(group a, group b){
    return a.attack == b.attack && a.type == b.type && a.hp == b.hp && a.troops == b.troops;
}

int main(int argc, const char * argv[]) {
    in>>n;
    vector<string> weak, immune;
    for(int i = 1; i <= n; ++ i){
        weak.clear();
        immune.clear();
        in>>nr>>hp;
        in>>k;
        for(int j = 1; j <= k; ++ j){
            in>>str;
            weak.push_back(str);
        }
        in>>k;
        for(int j = 1; j <= k; ++ j){
            in>>str;
            immune.push_back(str);
        }
        in>>attack;
        in>>k;
        for(int j = 1; j <= k; ++ j)
            in>>attackType;
        in>>initiative;
        groups.push_back(MakeGroup("immune", attack, hp, nr, initiative, attackType, weak, immune));
        initGroups.push_back(MakeGroup("immune", attack, hp, nr, initiative, attackType, weak, immune));
    }
    
    in>>n;
    for(int i = 1; i <= n; ++ i){
        weak.clear();
        immune.clear();
        in>>nr>>hp;
        in>>k;
        for(int j = 1; j <= k; ++ j){
            in>>str;
            weak.push_back(str);
        }
        in>>k;
        for(int j = 1; j <= k; ++ j){
            in>>str;
            immune.push_back(str);
        }
        in>>attack;
        in>>k;
        for(int j = 1; j <= k; ++ j)
            in>>attackType;
        in>>initiative;
        groups.push_back(MakeGroup("infection", attack, hp, nr, initiative, attackType, weak, immune));
        initGroups.push_back(MakeGroup("infection", attack, hp, nr, initiative, attackType, weak, immune));
    }
    
    int debugaici, add = 0;
    while(true){
        ++ add;
        groups.clear();
        for(auto it : initGroups){
            groups.push_back(it);
            if(groups.back().type == "immune"){
                groups.back().attack += add;
            }
        }
        while(check()){
            for(int i = 0; i < groups.size(); ++ i)
                viz[i] = false;
            sort(groups.begin(), groups.end(), cmp);
            initialState.clear();
            for(auto it : groups){
                initialState.push_back(it);
            }
            for(int i = 0; i < groups.size(); ++ i){
                if(groups[i].troops <= 0)
                    continue;
                int maximDmg = -1, maximPower = -1, maximInit = -1, toAttack = -1;
                for(int j = 0; j < groups.size(); ++ j){
                    if(groups[j].troops <= 0)
                        continue;
                    if(i == j)
                        continue;
                    if(groups[i].type == groups[j].type)
                        continue;
                    if(viz[j] == true)
                        continue;
                    
                    int multiplier = 1;
                    for(auto it : groups[j].weak){
                        if(groups[i].attackType == it)
                            multiplier = 2;
                    }
                    for(auto it : groups[j].immune){
                        if(groups[i].attackType == it)
                            multiplier = 0;
                    }
                    int dmg = multiplier * groups[i].troops * groups[i].attack;
                    if(dmg == 0)
                        continue;
                    int power = groups[j].troops * groups[j].attack;
                    int init = groups[j].initiative;
                    if(dmg == maximDmg){
                        if(power == maximPower){
                            if(init > maximInit){
                                maximInit = init;
                                toAttack = j;
                            }
                        }
                        if(power > maximPower){
                            maximPower = power;
                            maximInit = init;
                            toAttack = j;
                        }
                    }
                    if(dmg > maximDmg){
                        maximDmg = dmg;
                        maximPower = power;
                        maximInit = init;
                        toAttack = j;
                    }
                }
                if(toAttack >= 0){
                    attackQueue.push_back({i, toAttack});
                    viz[toAttack] = true;
                }
            }
            sort(attackQueue.begin(), attackQueue.end(), cmpQueue);
            while (!attackQueue.empty()) {
                int i = attackQueue.front().first;
                int j = attackQueue.front().second;
                attackQueue.pop_front();
                if(groups[i].troops <= 0 || groups[j].troops <= 0)
                    continue;
                int multiplier = 1;
                for(auto it : groups[j].weak){
                    if(groups[i].attackType == it)
                        multiplier = 2;
                }
                for(auto it : groups[j].immune){
                    if(groups[i].attackType == it)
                        multiplier = 0;
                }
                int dmg = multiplier * groups[i].troops * groups[i].attack;
                int troopsKilled = dmg / groups[j].hp;
                groups[j].troops -= troopsKilled;
            }
            ok = 0;
            for(int i = 0; i < groups.size(); ++ i)
                if(!equals(groups[i],initialState[i]))
                    ok = 1;
            if(ok == 0){
                break;
            }
        }
        
        if(ok == 0)
            continue;
        
        int nrImune = 0, nrInfection = 0;
        for(int i = 0; i < groups.size(); ++ i){
            if(groups[i].type == "immune" && groups[i].troops > 0)
                nrImune += groups[i].troops;
            if(groups[i].type == "infection" && groups[i].troops > 0)
                nrInfection += groups[i].troops;
        }
        if(nrImune > 0){
            out<<nrImune;
            break;
        }
    }
    
  

    
    return 0;
}
