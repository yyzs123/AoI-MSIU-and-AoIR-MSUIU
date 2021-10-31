#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>
#include<fstream>

using namespace std;
const int CONTENTS = 100;
const int SORTEDBYTIME = 1;
const int SORTEDBYVMC = 2;
const int SOURCES = 100;
int ns, cs, cacnt;// sn number and content number
double ALPHA;
const string DIR = "../Data/";
int D_0[SOURCES][CONTENTS] = { 0 };
int timeOfD0[SOURCES][CONTENTS] = { 0 };
int candiVMCSet[SOURCES][CONTENTS] = { 0 };
int candiTimeSet[SOURCES][CONTENTS] = { 0 };
int candiNoSet[SOURCES][CONTENTS] = { 0 };
double sumVMC;
double sumT;   
double totalVMC = 0;
double totalT = 0;
//int rj[SOURCES] = { 0 };
//double BStime[CONTENTS] = { 20,10,37,24,21,34,54,23,2,14 };
vector<vector<int>> node;
vector<vector<int>> Time;
vector<vector<int>> vmc;
vector<int> rj;

class Content {
private:
   int before_no, time,valueMinusCost,round,sources;
   bool inited;
public:
   Content() :before_no(-1), time(-1), valueMinusCost(-1),
      round(-1),sources(-1),inited(false) {}
   ~Content() {}
   //Content(int no, int t) :before_no(no), time(t) {}
   void iniObj(int no, int t,int vMc,int r,int s) {
      this->before_no = no;
      this->time = t;
      this->valueMinusCost = vMc;
      this->round = r;
      this->sources = s;
      inited = true;
   }
   int getTime() {
      if (!inited)
         return -2;
      return time;
   }
   int getNo() {
      if (!inited)
         return -1;
      return before_no;
   }
   int getVMC() {
      if (!inited)
         return -3;
      return valueMinusCost;
   }
   int getRound() {
      if (!inited)
         return -4;
      return round;
   }
   int getSource() {
      if (!inited)
         return -4;
      return sources;
   }
   void setNo(int n) {
      this->before_no = n;
   }
   void setTime(int t) {
      this->time = t;
   }
   void setRound(int r) {
      this->round = r;
   }
   void setSource(int s) {
      this->sources = s;
   }
   void setVMC(int vmc) {
      this->valueMinusCost = vmc;
   }
};

void sortVector(vector<Content> &vec,int flag,int s) {
   auto length = vec.size();
   int tempNo, tempTime,tempVMC,tempRound;
   if (flag == SORTEDBYTIME) {
      for (auto i = 0; i < length; ++i) {
         for (auto j = i + 1; j < length; ++j) {
            if (vec[i].getTime() > vec[j].getTime()) {
               tempNo = vec[j].getNo();
               tempTime = vec[j].getTime();
               tempVMC = vec[j].getVMC();
               tempRound = vec[j].getRound();
               vec[j].iniObj(vec[i].getNo(), vec[i].getTime(), vec[i].getVMC(),vec[i].getRound(),s);
               vec[i].iniObj(tempNo, tempTime, tempVMC,tempRound,s);
            }
         }

      }
   }
   else if (flag == SORTEDBYVMC) {
      for (auto i = 0; i < length; ++i) {
         for (auto j = i + 1; j < length; ++j) {
            if (vec[i].getVMC() < vec[j].getVMC()) {
               tempNo = vec[j].getNo();
               tempTime = vec[j].getTime();
               tempVMC = vec[j].getVMC();
               tempRound = vec[j].getRound();
               vec[j].iniObj(vec[i].getNo(), vec[i].getTime(), vec[i].getVMC(), vec[i].getRound(),s);
               vec[i].iniObj(tempNo, tempTime, tempVMC, tempRound,s);
            }
         }

      }
   }
}

void print(vector<Content> &vec) {
   auto length = vec.size();
   for (int i = 0; i <length; ++i) {
      cout << " id is: " << vec[i].getNo() <<
         " time is: " << vec[i].getTime() <<
         " VMC is: " << vec[i].getVMC() <<
         " Round is: " << vec[i].getRound() <<
         " Source is: " << vec[i].getSource() << endl;
   }
   cout <<"size is: " << vec.size() << endl;
}

void printInt(vector<int> vec) {
   cout << "optimal source is : " << endl;
   for (auto i = vec.begin(); i != vec.end(); ++i) {
      cout << *i << " ";
   }
   cout << endl;
}

void createSet(vector<Content> &D0, vector<Content> &optDj) {


   //update D0
   if (!optDj.empty()) {
      for (auto i = 0; i < D0.size(); ++i) {
         for (auto j = 0; j < optDj.size(); ++j) {
            if (optDj[j].getNo() == D0[i].getNo()) {
               D0.erase(D0.begin() + i);
               --i;
               break;
            }
         }
      }
      
   }
   else if (optDj.empty()) {
      //D0����
      for (int i = 0; i < cs; ++i) {

         Content c;
         c.iniObj(i, 0, 0, 0, 0);
         D0.push_back(c);
      }
   }
}

/*
����time��vmc��d����ѡ�����ݱ�ţ�

*/

void createInterSet(vector<Content> &candidateContent, vector<vector<int>> &Time,
	vector<vector<int>> &node, vector<vector<int>> &vmc, int s) {

	for (auto i = 0; i < node[s].size(); ++i) {
		Content tempC;
		tempC.iniObj(node[s][i], Time[s][i], vmc[s][i], 0, s);
		candidateContent.push_back(tempC);

	}
	//cout << "candidate numbers is: " << candidateContent.size() << endl;

}

//void createInterSet(vector<Content> D0, vector<Content> &candidateContent,
//    int s) {
//   //������ɺ�ѡ���ݸ���
//   srand((int)time(NULL));
//   int candidateNumbers = (rand() % D0.size()) + 1;
//   vector<int> tempIndex;
//   int index,tempNo;
//   tempIndex.push_back(-1);
//     
//   //��ѡ���ݼ���
//   for (auto i = 0; i < candidateNumbers; ++i) {
//
//      index = rand() % D0.size();
//      //��ֹ�ظ���index����
//      for (auto j = 0; j < tempIndex.size(); ++j) {
//         if (tempIndex[j] == index) {
//            index = rand() % D0.size();
//            j = 0;
//         }
//      }
//      tempIndex.push_back(index);
//      candidateContent.push_back(D0[index]);
//      candiVMCSet[s - 1][i] = D0[index].getVMC();
//      candiTimeSet[s - 1][i] = D0[index].getTime();
//      candiNoSet[s - 1][i] = D0[index].getNo();
//   }
//   
//
//
//   cout << "candidate numbers is: " << candidateNumbers << endl;
//   
//
//}


void algorithmOne(vector<Content> &candidateContent, vector<Content> &chosenContent,
   int maxUpLoadContent,int rounds,int s,int dSize) {
   sortVector(candidateContent, SORTEDBYTIME,s);
   vector<Content> tempCon;
   //sortVector(tempCon, SORTEDBYVMC);
   //��ʼ�㷨
   for (auto r = 1; r <= rounds; ++r) {
      candidateContent[r - 1].setRound(r);
      chosenContent.push_back(candidateContent[r - 1]);
      if (maxUpLoadContent >= r) {
         for (auto t = 0; t < r - 1; ++t) {
            candidateContent[t].setRound(0);
            chosenContent.push_back(candidateContent[t]);
         }
      }
      else {
         //vector<Content> tempCon;
         for (auto i = 0; i < r - 1; ++i) {
            tempCon.push_back(candidateContent[i]);
            
         }
		 sortVector(tempCon, SORTEDBYVMC, s); //��
         for (auto t = 1; t < maxUpLoadContent - 1; ++t) {
            tempCon[t-1].setRound(0);
            chosenContent.push_back(tempCon[t-1]);
         }
         tempCon.clear();
      }
   }
   //�������һ���յģ�bestRound����ô���
   Content tempC;
   tempC.iniObj(dSize + 1, 0, 0, rounds + 1, s);
   chosenContent.push_back(tempC);
   
}

void bestRound(vector<Content> &chosenContent, int &optimalRound, double &maxUti) {
   auto length = chosenContent.size();
   double tempTime = 0.0;
   int tempRound = 0;
   double tempNetU = 0;

   for (auto i = 1; i <= length; ++i) {
	   
      if (chosenContent[i - 1].getRound() != 0) {
         tempRound = chosenContent[i - 1].getRound();
		 
         if (maxUti < (double(tempNetU - ALPHA * tempTime))) {

            maxUti = double(tempNetU - ALPHA*tempTime);
            optimalRound = tempRound - 1;
         }
		 //if (BStime[chosenContent[i-1].getNo()-1] > chosenContent[i - 1].getTime()) {
			// //Ҫ�������ݵ�ʱ���bs�ϵ���
			// tempTime = BStime[chosenContent[i - 1].getNo() - 1]-chosenContent[i - 1].getTime();
		 //}
		 //else {
			// tempTime = 0;
		 //}
         tempTime = chosenContent[i - 1].getTime();
		 //tempTime = 0;
         tempNetU = 0;
      }
      tempNetU += double(chosenContent[i - 1].getVMC());
	  //tempTime = chosenContent[i - 1].getTime();
   }
   //cout << "optimal round is: " << optimalRound << endl;
}


void splitChosenContent(vector<Content> chosenContent, vector<Content> &Dj,
   int optRound,int sources) {
   for (auto i = 0; i < chosenContent.size(); ++i) {
      if (chosenContent[i].getRound() == optRound) {
         Dj.push_back(chosenContent[i]);
         int j = i + 1;
         while (chosenContent[j].getRound() == 0) {
            Dj.push_back(chosenContent[j]);
            ++j;
         }
         break;
      }
   }
   for (auto s = 0; s < Dj.size(); ++s) {
      Dj[s].setSource(sources);
   }
}

bool sourceIsInVec(vector<int> &optSourceVec, int source) {
   for (auto i = 0; i < optSourceVec.size(); ++i) {
      if (source == optSourceVec[i]) {
         return true;
      }
   }
   return false;
}

//void changeD0InDifferSource(vector<Content> &D0,int source) {
//   srand((int)time(NULL));
//   int vmc = 0;
//   int tempV, tempC,newTime;
//   for (auto i = 0; i < D0.size(); ++i) {
//      tempV = rand() % 100 + 1;
//      //Sleep(200);
//      tempC = rand() % 50 + 1;
//      vmc = tempV - tempC + 1;
//      //Sleep(200);
//      newTime = rand() % 50 + 1;
//      D0[i].setTime(newTime);
//      D0[i].setVMC(vmc);
//      D_0[source][i] = vmc;
//      timeOfD0[source][i] = newTime;
//   }
//}

//void outputD0(vector<Content> &inputD0,vector<Content> Dj,int s) {
//	//inputD0, candidateSet,source
//   string path = PATH + "data.txt";
//   ofstream outFile(path, ofstream::app);
//   double result;
//   bool flag = false;
//   for (auto i = 0; i != inputD0.size(); ++i) {
//	   for (auto j = 0; j != Dj.size(); ++j) {
//		   if (inputD0[i].getNo() == Dj[j].getNo()) {
//			   flag = true;
//			   break;
//		   }
//	   }
//	   if (!flag) {
//		   inputD0[i].setVMC(-50);
//		   inputD0[i].setTime(100);
//	   }
//	   flag = false;
//   }
//   for (auto k = 0; k != inputD0.size(); ++k) {
//	   if (inputD0[k].getTime() < BStime[k] && inputD0[k].getTime() < 100) {
//		   result = inputD0[k].getVMC() - ALPHA * (BStime[k] - inputD0[k].getTime());
//	   }
//	   else if (inputD0[k].getTime() == 100) {
//		   result = -100;//���û��ѡ�ϵ�����
//	   }
//	   else if(inputD0[k].getTime() >= BStime[k]){
//		   result = inputD0[k].getVMC();//���������ݵ�aoi����
//	   }
//	   outFile << result << " ";
//   }
//   
//   outFile << " " << rj[s - 1] << endl;
//}
//void outputData(vector<Content> D0,int source) {
//	string path1 = PATH + "rowData.txt";
//	ofstream outFile1(path1, ofstream::app);
//	string path2 = PATH + "timeData.txt";
//	ofstream outFile2(path2, ofstream::app);
//	double result;
//	for (auto i = 0; i != D0.size(); ++i) {
//		if (D0[i].getTime() < BStime[i]) {
//			result = D0[i].getVMC() - ALPHA * (BStime[i] - D0[i].getTime());
//		}
//		else {
//			result = D0[i].getVMC();
//		}
//		outFile1 << result << " ";
//	}
//	outFile1 << endl;
//	for (auto t = 0; t != D0.size(); ++t) {
//
//		outFile2 << D0[t].getTime() << " ";
//	}
//	outFile2 << endl;
//}

void recoverD0(vector<Content> &D0, int source) {
   for (auto i = 0; i < D0.size(); ++i) {
      D0[i].setVMC(D_0[source-1][D0[i].getNo()-1]);
      D0[i].setTime(timeOfD0[source-1][D0[i].getNo()-1]);
      D0[i].setSource(source);
   }
}
void recoverCandiSet(vector<Content> &candidateSet, int source) {
   //candidateSet.clear();
   for (int i = 0,j=0; i < CONTENTS; ++i) {
      //cout << candiNoSet[source - 1][i] << " ";
      if (candiNoSet[source - 1][i] == 0) {
         continue;
      }
      Content c;
      c.iniObj(candiNoSet[source - 1][i], candiTimeSet[source - 1][i],
         candiVMCSet[source - 1][i], 0, source);
      candidateSet.push_back(c);
      //delete c;
   }
}
void deleteCandiSet(vector<Content> &candidateContent,vector<Content> &Dj) {
	//cout << "in the deletecandiset..." << endl;
	for (auto i = 0; i < candidateContent.size(); ++i) {
		for (auto j = 0; j < Dj.size(); ++j) {
			if (Dj[j].getNo() == candidateContent[i].getNo()) {
				candidateContent.erase(candidateContent.begin() + i);
				--i;
				break;
			}
		}
	}
}

//void deleteCandiSet(vector<Content> &Dj) {
//	cout << "in the deletecandiset..." << endl;
//   const auto DjSize = Dj.size();
//   for (int i = 0; i < SOURCES; ++i) {
//      for (int j = 0; j < CONTENTS; ++j) {
//         for (int t = 0; t < DjSize; ++t) {
//			 //cout <<"source is: "<<i<<" content is: "<<j
//				 //<<" candiset is: "<< candiNoSet[i][j] << endl;
//            if (candiNoSet[i][j] != Dj[t].getNo()) {
//               continue;
//            }
//            else {
//               candiNoSet[i][j] = 0;
//               candiTimeSet[i][j] = 0;
//               //candiVMCSet[i][j] = 0;
//               break;
//            }
//         }
//      }
//   }
//}

void algorithmTwo(vector<Content> &D0, vector<Content> &candidateContent,
   vector<Content> &chosenContent, vector<Content> &Dj, vector<int> &optSourceVec,
   int &optSource, double &tempMaxUti,double &totalMaxUti) {

	int optRound;
	double maxUti;
   bool flagD0 = false;
   int maxUpLoadContent = 0;
   auto rounds = 0;
   sumVMC = 0;
   sumT = 0;
   vector<Content> inputD0;
   vector<Content> tempDj;
   vector<vector<Content>> overallCandi;
   
   do {
      
      createSet(D0, Dj);
	  //cout << endl;
	  cout << "-----" << endl;
      cout << "new round..." << endl;
      
      if (D0.empty())
         break;
      Dj.clear();
	  tempMaxUti = 0;
	  for (int s = 0; s < ns; ++s) {
		  cout << "\n source is: " << s << endl;
		  optRound = 0;
		  maxUti = 0;
		  sumVMC = 0;
		  sumT = 0;
		  candidateContent.clear();
		  chosenContent.clear();
		  if (sourceIsInVec(optSourceVec, s)) {
			  continue;
		  }
		  //cout << "create candidate set:" << endl;
		  if (flagD0 == false) {//��һ������
			  createInterSet(candidateContent, Time, node, vmc, s);
			  overallCandi.push_back(candidateContent);
		  }
		  else {
			  candidateContent = overallCandi[s];
			  deleteCandiSet(candidateContent, tempDj);
			  overallCandi[s] = candidateContent;
		  }
		  
		  if (candidateContent.empty())
			  continue;
		  //if (flagD0 == false) {//��һ�����ɣ���ѡ���̶���rj�̶���D0�̶�
			 // //cout << "create D0..." << endl;
			 // //changeD0InDifferSource(D0, s - 1);
			 // //interContent.clear();
			 // createInterSet(D0, candidateContent, s);
			 // //����
			 // rounds = candidateContent.size();
			 // //�������rj ȡ[1,rounds]�е���
			 // maxUpLoadContent = (rand() % rounds) + 1;
			 // rj[s - 1] = maxUpLoadContent;
			 // cout << "rj is: " << maxUpLoadContent << endl;

		  //}
		  //else {
			 // cout << "recover D0..." << endl;
			 // recoverD0(D0, s);
			 // cout << "recover candiSet..." << endl;
			 // recoverCandiSet(candidateContent, s);
			 // rounds = candidateContent.size();

			 // maxUpLoadContent = rj[s - 1];

		  //}
		  /*cout << "D0 is: " << endl;
		  print(D0);*/
		  //inputD0.clear();
		  //outputData(D0,s);
		  //inputD0 = D0;
		  rounds = candidateContent.size();
		  //maxUpLoadContent = (rand() % rounds) + 1;
		  //maxUpLoadContent = rounds;
		  //rj.push_back(maxUpLoadContent);
		  //cout << "rj is: " << maxUpLoadContent << endl;
		  
		  //�㷨1��ʼ
		  algorithmOne(candidateContent, chosenContent, rj[s], rounds, s, cs);
		 /* cout << "candiset is: " << endl;
		  print(candidateContent);*/
		  //outputD0(inputD0,candidateContent, s);
		  /*cout << "chosen set is: " << endl;
		  print(chosenContent);*/
		  bestRound(chosenContent, optRound, maxUti);


		  //cout << "maxUtil is: " << maxUti << endl;
		  //���Dj
		  //splitChosenContent(chosenContent, Dj, optRound);
		  if (tempMaxUti < maxUti) {
			  tempMaxUti = maxUti;
			  
			  optSource = s;
			  //��������ŵĽ���chosenContent�����������ݿ�ѹ��
			  Dj.clear();
			  splitChosenContent(chosenContent, Dj, optRound, s);
		  }
		  cout << "totalUtil is: " << tempMaxUti << endl;
		  
		  
		  //Sleep(5000);

	  }
	  cout << "Dj is: " << endl;
	  print(Dj);
	  if (!Dj.empty()) {
		  sumT = Dj[0].getTime();
		  for (auto i = 0; i != Dj.size(); ++i) {
			  sumVMC += Dj[i].getVMC();
		  }
	  }
      flagD0 = true;
	  tempDj.clear();
	  tempDj = Dj;
      //deleteCandiSet(D0,Dj);
      if (tempMaxUti <= 0) {
         cout << "utility less than 0, breaking..." << endl;
         break;
      }
      else {
         optSourceVec.push_back(optSource);
      }
	  totalMaxUti += tempMaxUti;
	  totalVMC += sumVMC;
	  totalT += sumT;
	  cout << "vmc is:" << totalVMC << endl;
	  cout << "T is: " << totalT << endl;
      printInt(optSourceVec);
	  
   } while (!D0.empty()||optSourceVec.size() != ns);
}

//����������Ҫÿ�����ĸ��°���ʱ�䣬vmc
void readPara(vector<int> &kn, vector<vector<int>> &tni,
	vector<vector<int>> &vmc,vector<vector<int>> &node, string index) {
	//string path = PATH + "10times_20users_backup.txt";
	string path = DIR + to_string(ns) + "_" + to_string(cs) + "_" + to_string(cacnt) + "/" + index + ".txt";

	int tempTime = 0;
   ifstream in(path.c_str(), ios::in);
   if(!in.is_open())
	{
		cout << "can not open this file" << endl;
		exit(0);
	}
	// rj = kn; ???????????
   tni.resize(ns), vmc.resize(ns), node.resize(ns);
   while(!in.eof()){
      int D = 0, tmpr = 0;
      in >> D >> tmpr;
      kn.emplace_back(D);
      rj.emplace_back(tmpr);
      for(int i = 0; i < D; ++i){
         int cid, t, _vmc, used, sn;
         if(in.eof()){
            cout<< "(2) Error while read file." << endl;
            in.close();
            exit(0);
         }
         in >> cid >> t >> _vmc >> used >> sn;
         tni[sn].emplace_back(t);
         vmc[sn].emplace_back(_vmc);
         node[sn].emplace_back(cid);
      }
   }
   in.close();
   cout<<"Data is load."<<endl;
}

int main(int argc, char *argv[])
{

   freopen("Greedy.txt", "w", stdout);
   if(argc < 5){
      cout << "Please give parameters ns(the set size of SNs), cs(the set size of Content) and alpha." << endl;
      return 0;
   }
   ns = stoi(string(argv[1])), cs = stoi(string(argv[2])), ALPHA = stod(string(argv[4]));
   cacnt = stoi(string(argv[3]));
   //srand((int)time(NULL));
   vector<Content> D_0, candidateContent, Dj;

   int maxUpLoadContent;//Ҳ����rj
   vector<int> maxUploadVec;
   
   int optRound, maxUti,optSource;

   double totalMaxUti = 0;
   double tempMaxUti = 0;
   vector<Content> chosenContent;
   vector<int> optSourceVec;
   vector<int> kn;
   string index = "";
   double sumUti = 0;

   for (int i = 1; i <= cacnt; ++i) {
	   D_0.clear();
	   candidateContent.clear();
	   Dj.clear();
	   chosenContent.clear();
	   optSourceVec.clear();
	   kn.clear();
	   Time.clear();
	   vmc.clear();
	   node.clear();
	   optSource = -1;
	   totalMaxUti = 0;
	   tempMaxUti = 0;
	   cout << "----" << endl;
	   index = to_string(i);
	   cout << index << endl;
	   readPara(kn, Time, vmc, node, index);
	   algorithmTwo(D_0, candidateContent, chosenContent,
		   Dj, optSourceVec, optSource, tempMaxUti, totalMaxUti);

	   cout << "total utility is: " << totalMaxUti << endl;
	   sumUti += totalMaxUti;
	   
	   cout << "VMC is:" << totalVMC << endl;
	   cout << "T is:" << totalT << endl;
   }
   
   
   cout << "total is:" << (totalVMC -ALPHA*totalT)/cacnt << endl;
   cout << "VMC is:" << totalVMC/cacnt << endl;
   cout << "T is:" << totalT/cacnt << endl;
   cout<<endl<<endl;
   ofstream out((string("../Results/") + to_string(ns) + string("_") + to_string(cs) + "_" + to_string(cacnt) + "_" + to_string(ALPHA) + "_Greedy.txt").c_str(), ios::out);
   if(!out.is_open()){
      cout << "(3) Error while opening file." << endl;
      exit(0);
   }
   out << (totalVMC -ALPHA*totalT) / cacnt << " " << time(0) <<endl;
   out.close();
   return 0;
}