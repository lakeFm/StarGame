#ifndef STARGAME_SAVER_H
#define STARGAME_SAVER_H

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "shortCalls.h"

using namespace std;
fun save(int score){
    ofstream f;
    f.open("save.txt",ios::app);
    f << score << endl << " ";
    f.close();
}

vector<int> getScore(){
    vector<int> data;
    ifstream f;
    f.open("save.txt");
    string tmp;
    while(f >> tmp){
        int t = stoi(tmp);
        if(t > 20000)
            data.push_back(0);
        else
            data.push_back(t);
    }
    f.close();

    if(data.size() < 5){
        int d = 5 - data.size();
        while(d > 0){
            data.push_back(0);
            d--;
        }
    }

    sort(data.begin(),data.end(),greater<int>());

    ret vector<int>(data.begin(),data.begin()+5);
}

#endif //STARGAME_SAVER_H
