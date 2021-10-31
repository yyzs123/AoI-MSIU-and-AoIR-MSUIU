#include<bits/stdc++.h>
using namespace std;
const int MAXNS = 100;
const int MAXCS = 100;
int vmc_vec[MAXNS][MAXCS];
int t_vec[MAXNS][MAXCS];
int y_vec[MAXNS][MAXCS];
int r_vec[MAXNS];
const string DIR = "../../Data/";
void outmatrix(ofstream &out, int row, int col, string pname, int vec[][MAXCS])
{
    out << "param " << pname.c_str() << ":";      
    if(col > 1){
        for(int j = 1; j <= col; ++j) out << " " << j;
        out << ":";
    }
    out << "="; out << "\n";
    for(int i = 0; i < row; ++i){
        out << i + 1;
        for(int j = 0; j < col; ++j){
            out << " " << vec[i][j];
        }
        if(i == row - 1) out << ";";
        out << "\n";
    }
}
void outmatrix(ofstream &out, int row, string pname, int vec[])
{
    out << "param " << pname.c_str() << ":=\n";  
    for(int i = 0; i < row; ++i){
        out << i + 1 << " " << vec[i];
        if(i == row - 1) out << ";";
        out << "\n";
    }
}

int main(int argc, char *argv[])
{
    if(argc < 4){
        cout << "Please input ns(the set size of SNs) and cs(the set size of Content)." << endl;
        return 0;
    }
    //cout << argv[1] << ' ' << argv[2]<<' '<<argv[3]<<endl;
    int ns = stoi(string(argv[1])), cs = stoi(string(argv[2])), ca = stoi(string(argv[3]));
    cout << ns << ' ' << ' ' << cs << ' ' << ca <<endl;
    string path = DIR + to_string(ns) + "_" + to_string(cs) + "_" + to_string(ca) + "/";
    for(int i = 1; i <= ca; ++i){
        memset(vmc_vec, 0, sizeof(vmc_vec));
        memset(t_vec, 0, sizeof(t_vec));
        memset(y_vec, 0, sizeof(y_vec));
        memset(r_vec, 0, sizeof(r_vec));

        ifstream in((path + to_string(i) + ".txt").c_str(), ios::in);
        if(!in.is_open()){
            cout << "(1) Error while opening file." << endl;
            exit(0);
        }



        int snid = 0;
        while(!in.eof()){
            int D = 0, tmpr = 0;
            in >> D >> tmpr;
            r_vec[snid] = tmpr;
            for(int i = 0; i < D; ++i){
                int cid, t, vmc, used, sn;
                if(in.eof()){
                    cout<< "(2) Error while read file." << endl;
                    in.close();
                    exit(0);
                }
                in >> cid >> t >> vmc >> used >> sn;
                if(sn != snid){
                    cout << "(3) Data error." << endl;
                    in.close();
                    exit(0);
                }
                y_vec[sn][cid] = 1;
                t_vec[sn][cid] = t;
                vmc_vec[sn][cid] = vmc;
            }
            ++snid;
        }
        in.close();

        ofstream out((path + to_string(i) + "_ampl.dat").c_str(), ios::out);
        out << "param m:=" << ns << ";"; out << "\n";
        out << "param n:=" << cs << ";"; out << "\n";
        out << "param alpha:=0.5;"; out << "\n";
        outmatrix(out, ns, cs, "y", y_vec);     
        outmatrix(out, ns, cs, "v", vmc_vec);     
        outmatrix(out, ns, cs, "t", t_vec);     
        outmatrix(out, ns, "r", r_vec);
        out.close();
    }
    return 0;
}