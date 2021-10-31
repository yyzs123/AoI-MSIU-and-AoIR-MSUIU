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
    freopen("Zero-wait.txt", "w", stdout);
    if(argc < 5){
        cout << "Please input ns(the set size of SNs) and cs(the set size of Content)." << endl;
        return 0;
    }
    int ns = stoi(string(argv[1])), cs = stoi(string(argv[2])), cacnt = stoi(string(argv[3]));
    double alpha = stod(string(argv[4]));
    int sumvmc = .0, summxt = .0;
    for(int ca = 1; ca <= cacnt; ++ca){
        vector<Content>cvec;
        vector<int>r, count(ns, 0), upted(cs, 0), mxt(ns, -1), vmc(ns, 0);
        readData(ns, cs, ca, cacnt, cvec, r);

        sortContentByTime(cvec, true);
        vector<vector<Content> >ccvec;  //choosed content vec
        ccvec.resize(ns);
        for(int i = 0, sz = cvec.size(), nxt; i < sz; i = nxt){
            for(nxt = i + 1; nxt < sz && cvec[nxt].gett() == cvec[i].gett(); ++nxt);
            /*sort(cvec.begin() + i, cvec.begin() + nxt, [&](const Content &x, const Content &y){
                return x.getvmc() > y.getvmc();
            });*/
            for(int j = i; j < nxt; ++j){
                int cid = cvec[j].getid(), sn = cvec[j].getsn();
                if(upted[cid] || count[sn] >= r[sn]) continue;
                upted[cid] = 1, ++count[sn];
                cvec[j].setused(1);
                vmc[sn] += cvec[j].getvmc();
                mxt[sn] = max(mxt[sn], cvec[j].gett());
                ccvec[sn].push_back(cvec[j]);
            }
        }
        cout << "Case: " << ca << endl;
        for(int i = 0; i < ns; ++i){
            cout << "Vmc = " << vmc[i] << ", maxt = " << mxt[i] << endl;
            if(mxt[i] < 0) continue;
            sumvmc += vmc[i];
            summxt += mxt[i];
            //cout<< "i = " << i << " " <<summxt <<' '<< mxt[i] <<endl;
            printContentVec(ccvec[i]);
        }
    }
    ofstream out((string("../Results/") + to_string(ns) + string("_") + to_string(cs) + "_" + to_string(cacnt) + "_" + to_string(alpha) + "_Zero-wait.txt").c_str(), ios::out);
    if(!out.is_open()){
        cout << "(3) Error while opening file." << endl;
        exit(0);
    }
    cout<<"sumvmc = " << sumvmc << ", summxt = " << summxt << endl;
    double avgf = ((double)sumvmc - alpha * summxt) / cacnt;
    cout << "avgf = " << ((double)sumvmc - alpha * summxt)  << endl;
    out << avgf << " " << time(0) <<endl;
    cout << avgf << " " << time(0) <<endl;
    out.close();
    return 0;
}