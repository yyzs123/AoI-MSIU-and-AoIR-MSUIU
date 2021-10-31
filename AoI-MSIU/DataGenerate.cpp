#include<bits/stdc++.h>
#include<direct.h>
#include "Content.h"
using namespace std;
const int CABNUM = 600;
const double EARTH_RADIUS = 6378.137;
const double PI = acos(-1.0);
const string CABPATH = "../cabspottingdata/_cabs.txt";
const string RECORDDIR = "../cabspottingdata/";
struct Cab
{
    string name;
    int uptcount;
    Cab();
    Cab(string _name, int _uptcount):name(_name), uptcount(_uptcount){};
};
vector<Cab>Cabvec;
struct Point
{
    double latitude, longitude;
    Point();
    Point(double _latitude, double _longitude):latitude(_latitude), longitude(_longitude){};
    static double rad(double d){
        return d * PI / 180.0;
    }
    double distance(const Point &p){
        double y = rad(longitude) - rad(p.longitude), x = rad(latitude) - rad(p.latitude);
        double z = 2 * asin(sqrt(pow(sin(x / 2), 2) + cos(rad(latitude)) * cos(rad(p.latitude)) * pow(sin(y / 2), 2)));
        z = z * EARTH_RADIUS * 1000;
        return z;   // meter
    }
};
struct Record
{
    Point p;
    int occupancy, time;
    Record();
    Record(double _latitude, double _longitude, int _occupancy, int _time):p(_latitude, _longitude), occupancy(_occupancy), time(_time){};
};
vector<Record>Recordvec[CABNUM];
struct ContentType
{
    Point p;
    double r;
    ContentType();
    ContentType(double _latitude, double _longitude, double _r):p(_latitude, _longitude), r(_r){};
};
void readCab()
{
    ifstream in(CABPATH.c_str(), ios::in);
    if(!in.is_open()){
        cout << "(1) Error while opening file." << endl;
        exit(0);
    }
    char buffer[256];
    while(!in.eof()){
        in.getline(buffer, 256);
        string str(buffer);
        int p1 = str.find("\""), p2 = str.find("\"", p1 + 1), p3 = str.find("\"", p2 + 1), p4 = str.find("\"", p3 + 1); 
        Cabvec.emplace_back(str.substr(p1 + 1, p2 - p1 - 1), stoi(str.substr(p3 + 1, p4 - p3 - 1)));
    }
    in.close();
}
void createDataset(int ns, int cs, int cacnt)
{
    vector<int>cabid(Cabvec.size(), 0);
    //cout<<Cabvec.size()<<endl;
    iota(cabid.begin(), cabid.end(), 0);
    for(int ca = 1; ca <= cacnt; ++ca){
        mt19937 gen1(ns * cs * ca + 1), gen2(ns * cs * ca + 2), gen3(ns * cs * ca + 3), gen4(ns * cs * ca + 4), gen5(ns * cs * ca + 5), gen6(ns * cs * ca + 6); //Standard mersenne_twister_engine seeded with rd()
        uniform_real_distribution<> latrand(37.6, 37.8), longrand(-122.5, -122.3);
        uniform_int_distribution<> trand(1, 20), vmcrand(10, 60), rrand(1, 10);

        shuffle(cabid.begin(), cabid.end(), default_random_engine(ns * cs * ca));
        vector<ContentType>ctvec;
        for(int i = 0; i < cs; ++i){
            double x = latrand(gen1), y = longrand(gen2); 
            ctvec.emplace_back(x, y, rrand(gen3) * 1000);
            //cout<< x<<' '<<y <<endl;
        }
        string dirpath = string("../Data/") + to_string(ns) + string("_") + to_string(cs) + string("_") + to_string(cacnt) + string("/");
        int ret = mkdir(dirpath.c_str());
        if(ret && errno != EEXIST){
            cout << "mkdir failed." << endl;
            exit(0);
        }
        ofstream out((dirpath + to_string(ca) + ".txt").c_str(), ios::out);
        //cout<<(dirpath + to_string(ca) + ".txt").c_str()<<endl;
        if(!out.is_open()){
            cout << "(2) Error while opening file." << endl;
            exit(0);
        }
        for(int i = 0; i < ns; ++i){
            int id = cabid[i];
            if(Recordvec[id].empty()){
                ifstream in((RECORDDIR + string("new_") + Cabvec[id].name + string(".txt")).c_str(), ios::in);
                //cout << (RECORDDIR + string("new_") + Cabvec[id].name + string(".txt")).c_str() << endl;
                if(!in.is_open()){
                    cout << "(3) Error while opening file." << endl;
                    exit(0);
                }
                while(!in.eof()){
                    double a, b; int c, d;
                    in >> a >> b >> c >> d;
                    Recordvec[id].emplace_back(a, b, c, d);
                }
                in.close();
            }
            vector<Content>cvec;
            shuffle(Recordvec[id].begin(), Recordvec[id].end(), default_random_engine(ns * cs *  ca + id));
            vector<int>cid(cs, 0), count(cs, 0);
            iota(cid.begin(), cid.end(), 0);
            shuffle(cid.begin(), cid.end(), default_random_engine(ns * cs * ca + i));
            for(int j = 0, k = 0; j < Recordvec[id].size() && k < cs; ++j){
                const Record &record = Recordvec[id][j];
                for(int o = k; o < cs; ++o){
                    if(ctvec[cid[o]].p.distance(record.p) < ctvec[cid[o]].r){
                        cvec.emplace_back(cid[o], trand(gen4), vmcrand(gen5), 0, i);
                        swap(cid[o], cid[k++]);
                        break;
                    }
                }
                //if(cvec.size() >= 3 * cs) break;
            }
            // cout<<cvec.size() <<endl;
            // dataset size of sn and max upload count of sn
            //sortContentById(cvec);
            out << cvec.size() << " " << (cvec.size() > 0 ? gen6() % cvec.size() + 1 : 0) << "\n"; 
            for(const Content &content : cvec){
                out << content.getid() << " " << content.gett() << " " << content.getvmc() << " " << content.getused() << " " << content.getsn() << "\n";
            }
        }
        out.close();
    }
}
int main(int argc, char *argv[])
{
    //Point x(37.75153, -122.39447), y(37.75149, -122.39447);
    //cout<<x.distance(y)<<endl;

    //return 0;
    if(argc < 4){
        cout << "Please input ns(the set size of SNs) and cs(the set size of Content)." << endl;
        return 0;
    }
    int ns = stoi(string(argv[1])), cs = stoi(string(argv[2])), cacnt = stoi(string(argv[3]));
    readCab();
    createDataset(ns, cs, cacnt);
    cout << ns << "_" << cs << "_" << cacnt <<" ok." << endl;
    return 0;
}