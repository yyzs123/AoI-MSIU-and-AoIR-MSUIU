#include<bits/stdc++.h>
#include"Content.h"
using namespace std;
void readData(int ns, int cs, int ca, int cacnt, vector<Content> &cvec, vector<int> &r)
{
    ifstream in((string("../Data/") + to_string(ns) + string("_") + to_string(cs) + string("_") + to_string(cacnt) + "/" + to_string(ca) + ".txt").c_str(), ios::in);
    if(!in.is_open()){
        cout << "(1) Error while opening file." << endl;
        exit(0);
    }
    while(!in.eof()){
        int D = 0, tmpr = 0;
        in >> D >> tmpr;
        r.emplace_back(tmpr);
        for(int i = 0; i < D; ++i){
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
    freopen("Periodical.txt", "w", stdout);
    if(argc < 5){
        cout << "Please input ns(the set size of SNs) and cs(the set size of Content)." << endl;
        return 0;
    }
    int ns = stoi(string(argv[1])), cs = stoi(string(argv[2])), cacnt = stoi(string(argv[3]));
    double alpha = stod(string(argv[4]));
    double sumvmc = .0, summxt = .0;
    for(int ca = 1; ca <= cacnt; ++ca){
        vector<Content>cvec;
        vector<int>r, count(ns, 0), upted(cs, 0), mxt(ns, -1), vmc(ns, 0);
        readData(ns, cs, ca, cacnt, cvec, r);

        sortContentById(cvec);
        vector<int>cid(cs, 0);
        iota(cid.begin(), cid.end(), 0);
        shuffle(cid.begin(), cid.end(), default_random_engine(ca * ns * cs));
        vector<vector<Content> >ccvec;  //choosed content vec
        ccvec.resize(ns);

        for(const int id : cid){
            int L = lower_bound(cvec.begin(), cvec.end(), Content(id), [&](const Content &x, const Content &y){
                return x.getid() < y.getid();
            }) - cvec.begin();
            int R = upper_bound(cvec.begin(), cvec.end(), Content(id), [&](const Content &x, const Content &y){
                return x.getid() < y.getid();
            }) - cvec.begin();
            sort(cvec.begin() + L, cvec.begin() + R, [&](const Content &x, const Content &y){
                //if(x.gett() == y.gett()) return x.getvmc() > y.getvmc();
                return x.gett() < y.gett();
            });
            cout << id << " " << L << " " << R << " " <<cvec[L].getid() << " " <<cvec[R - 1].getid() << endl;
            for(int i = L; i < R; ++i){
                int cid = cvec[i].getid(), sn = cvec[i].getsn();
                if(upted[cid] || count[sn] >= r[sn]) continue;
                upted[cid] = 1, ++count[sn];
                cvec[i].setused(1);
                vmc[sn] += cvec[i].getvmc();
                mxt[sn] = max(mxt[sn], cvec[i].gett());
                ccvec[sn].push_back(cvec[i]);
            }
            sort(cvec.begin() + L, cvec.begin() + R, [&](const Content &x, const Content &y){
                return x.getid() < y.getid();
            });
        }
        cout << "Case: " << ca << endl;
        for(int i = 0; i < ns; ++i){
            cout << "Vmc = " << vmc[i] << ", maxt = " << mxt[i] << endl;
            if(mxt[i] < 0) continue;
            sumvmc += vmc[i];
            summxt += mxt[i];
            printContentVec(ccvec[i]);
        }
        // cout << "Zero-wait's f = " << f <<endl;
        // for(int i = 0; i < ns; ++i) printContentVec(vec[i]);
        
    }
    ofstream out((string("../Results/") + to_string(ns) + string("_") + to_string(cs) + "_" + to_string(cacnt) + "_" + to_string(alpha) + "_Periodical.txt").c_str(), ios::out);
    if(!out.is_open()){
        cout << "(3) Error while opening file." << endl;
        exit(0);
    }
    double avgf = (sumvmc - alpha * summxt) / cacnt;
    out << avgf << " " << time(0) <<endl;
    out.close();
    return 0;
}