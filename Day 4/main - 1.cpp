#include <fstream>
#include <vector>
#define DIM 10000

using namespace std;

ifstream in ("file.in");
ofstream out("file.out");

char c;
string str;

int id;
int minute, start, finish, maxim = -1, sum, maxGuard, maxSum;
vector<pair<int, int> > guards[DIM];

struct operation{
    int minute, hour, day, month, year;
    string type;
    int id;
};
//
//1 (12, 35)
//2 (4, 49)
//3
//4

operation MakeOp(int id, int minute, int hour, int day, int month, int year, string type){
    operation aux;
    aux.id = id;
    aux.minute = minute;
    aux.hour = hour;
    aux.day = day;
    aux.month = month;
    aux.year = year;
    aux.type = type;
    return aux;
}

vector<operation> op;

bool cmp(operation a, operation b){
    if(a.year == b.year){
        if(a.month == b.month){
            if(a.day == b.day){
                if(a.hour == b.hour){
                    return a.minute < b.minute;
                }
                return a.hour < b.hour;
            }
            return a.day < b.day;
        }
        return a.month < b.month;
    }
    return a.year < b.year;
}

int main(int argc, const char * argv[]) {
    
    while(in>>c){
        in>>str;
        int year = (str[0] - '0') * 1000 + (str[1] - '0') * 100 + (str[2] - '0') * 10 + str[3] - '0';
        int month = (str[5] - '0') * 10 + str[6] - '0';
        int day = (str[8] - '0') * 10 + str[9] - '0';
        in>>str;
        int hour = (str[0] - '0') * 10 + str[1] - '0';
        int minute = (str[3] - '0') * 10 + str[4] - '0';
        
        in>>str;
        string type = str;
        if(str == "Guard"){
            in>>str;
            id = 0;
            for(int i = 1; i < str.size(); ++ i)
                id = id * 10 + str[i] - '0';
            if(id > maxim)
                maxim = id;
            in>>str;
            in>>str;
        }
        if(str == "falls"){
            in>>str;
            start = minute;
        }
        if(str == "wakes"){
            in>>str;
            finish = minute;
            //guards[id].push_back({start, finish});
        }
        
        op.push_back(MakeOp(id, minute, hour, day, month, year, type));
    }
    
    sort(op.begin(), op.end(), cmp);
    
    for(int i = 0; i < op.size(); ++ i){
        if(op[i].type == "Guard"){
            id = op[i].id;
        }
        if(op[i].type == "falls"){
            start = op[i].minute;
        }
        if(op[i].type == "wakes"){
            finish = op[i].minute;
            guards[id].push_back({start, finish});
        }
    }
    
//    PART 1
//
    for(int i = 1; i <= maxim; ++ i){
        sum = 0;
        for(auto it : guards[i]){
            sum += it.second - it.first;
        }
        if(sum > maxSum){
            maxGuard = i;
            maxSum = sum;
        }
    }

    int maxNrMin = -1, maxMinute = -1;
    for(int i = 0; i <= 60; ++ i){
        int nr = 0;
        for(auto it : guards[maxGuard]){
            if(i >= it.first && i < it.second){
                ++ nr;
            }
        }
        if(nr > maxNrMin){
            maxNrMin = nr;
            maxMinute = i;
        }
    }
    out<<maxGuard * maxMinute;
    
//    int maxNrMin = -1, maxMinute = -1;
//    for(int i = 1; i <= maxim; ++ i){
//        for(int Min = 0; Min <= 60; ++ Min){
//            int nr = 0;
//            for(auto it : guards[i]){
//                if(Min >= it.first && Min < it.second){
//                    ++ nr;
//                }
//            }
//            if(nr > maxNrMin){
//                maxNrMin = nr;
//                maxGuard = i;
//                maxMinute = Min;
//            }
//        }
//    }
//
//    out<<maxGuard * maxMinute;
    
    return 0;
}
