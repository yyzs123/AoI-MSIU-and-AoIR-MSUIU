#include<bits/stdc++.h>
#include<direct.h>
#include "Content.h"
using namespace std;
const int CABNUM = 600;
const double EARTH_RADIUS = 6378.137;
const double PI = acos(-1.0);
const string CABPATH = "../cabspottingdata/_cabs.txt";
const string RECORDDIR = "../cabspottingdata/";
void readData(int ns, int cs, int ca, int cacnt, vector<Content> &cvec, vector<int> &r, vector<int> &D)
{
    ifstream in((string("../Data/") + to_string(ns) + string("_") + to_string(cs) + "_" + to_string(cacnt) + "/" + to_string(ca) + ".txt").c_str(), ios::in);
    if(!in.is_open()){
        cout << "(1) Error while opening file." << endl;
        exit(0);
    }
    while(!in.eof()){
        int tmpD = 0, tmpr = 0;
        in >> tmpD >> tmpr;
        D.emplace_back(tmpD);
        r.emplace_back(tmpr);
        for(int i = 0; i < tmpD; ++i){
            int cid, t, vmc, used, sn;
            if(in.eof()){
                cout<< "(2) Error while read file." << endl;
                in.close();
                exit(0);
            }
            in >> cid >> t >> vmc >> used >> sn;
            cvec.emplace_back(cid, t, vmc, used, sn);
        }
    }
    in.close();
}
int main(int argc, char *argv[])
{

    if(argc < 6){
        cout << "Please input ns(the set size of SNs) and cs(the set size of Content)." << endl;
        return 0;
    }
    int ns = stoi(string(argv[1])), cs = stoi(string(argv[2]));
    int cacnt = stoi(string(argv[3])), type = stoi(string(argv[4]));
    int step = stoi(string(argv[5]));
    if(type == 1){  //change ns
        for(int ca = 1; ca <= cacnt; ++ca){
            vector<Content>cvec;
            vector<int>r, D;
            readData(ns, cs, ca, cacnt, cvec, r, D);
            for(int n = step; n <= ns; n += step){
                string dirpath = string("../Data/") + to_string(n) + string("_") + to_string(cs) + string("_") + to_string(cacnt);
                int ret = mkdir(dirpath.c_str());
                if(ret && errno != EEXIST){
                    cout << "mkdir failed." << endl;
                    exit(0);
                }
                ofstream out((dirpath + string("/") + to_string(ca) + ".txt").c_str(), ios::out);
                if(!out.is_open()){
                    cout << "(1) Error while create file." << endl;
                    exit(0);
                }
                for(int i = 0, pos = 0; i < n; ++i){
                    out << D[i] << ' ' << r[i] << '\n';
                    for(int j = 0; j < D[i]; ++j){
                        out << cvec[pos + j].getid() << ' ' << cvec[pos + j].gett() << ' ' << cvec[pos + j].getvmc() << ' ' << cvec[pos + j].getused() << ' ' << cvec[pos + j].getsn() << '\n';
                    }
                    pos += D[i];
                }
                out.close();
            }
        }
    }
    else{   //change cs
        for(int ca = 1; ca <= cacnt; ++ca){
            vector<Content>cvec;
            vector<int>r, D;
            readData(ns, cs, ca, cacnt, cvec, r, D);
            for(int c = step; c <= cs; c += step){
                string dirpath = string("../Data/") + to_string(ns) + string("_") + to_string(c) + string("_") + to_string(cacnt) + string("/");
                int ret = mkdir(dirpath.c_str());
                if(ret && errno != EEXIST){
                    cout << "mkdir failed." << endl;
                    exit(0);
                }
                ofstream out((dirpath + string("/") + to_string(ca) + ".txt").c_str(), ios::out);
                if(!out.is_open()){
                    cout << "(1) Error while create file." << endl;
                    exit(0);
                }
                for(int i = 0, pos = 0; i < ns; ++i){
                    vector<Content>tmp_vec;
                    for(int j = pos; j < pos + D[i]; ++j){
                        if(cvec[j].getid() < c)
                            tmp_vec.push_back(cvec[j]);
                    }
                    out << (int)tmp_vec.size() << ' ' << r[i] << '\n';
                    for(const Content &content : tmp_vec){
                        out << content.getid() << ' ' << content.gett() << ' ' << content.getvmc() << ' ' << content.getused() << ' ' << content.getsn() << '\n';
                    }
                    pos += D[i];
                }
                out.close();
            }
        }

    }
    cout << "transform finish." << endl;
    return 0;
}