#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
//#include <boost/fusion/algorithm/transformation/join.hpp>
//#include <boost/fusion/include/join.hpp>
#include<vector>
#include <queue>   
#include <thread>
#include <mutex>
#define MAX_THREADS 24 
using namespace std;
using namespace boost;
std::mutex m;
int ile;
void wczytajGraf(vector<vector<int> > &graf){
  int size;
  cin >> size;
  for (int i = 0; i < size; i++) {
    int m;
    cin >> m;
    vector<int> edges;
    for (int j = 0; j<m;j++) {
      int e;
      cin >>e;
      edges.push_back(e);
    }
    graf.push_back(edges);
  }
}
void wypiszGraf(vector<vector<int> > *graf){
  m.lock();
  cout<<graf->size()<<"\n";
  for(int i = 0;i<graf->size();i++){
    cout<<(*graf)[i].size()<<"\n";
    for(int j=0; j<(*graf)[i].size();j++){
      cout<<(*graf)[i][j]<<" ";
    }
    cout<<"\n";
  }
  m.unlock();
}

typedef adjacency_list<vecS,
        vecS,
        undirectedS,
        property<vertex_index_t, int>
        > gr;


        vector<vector<int> > pod = {{1,2,3,4},{1,2,3,5},{1,2,3,6},{1,2,3,7},{1,2,3,8},{1,2,3},{1,2,4,5},{1,2,4,6},{1,2,4,7},{1,2,4,8},{1,2,4},{1,2,5,6},{1,2,5,7},{1,2,5,8},{1,2,5},{1,2,6,7},{1,2,6,8},{1,2,6},{1,2,7,8},{1,2,7},{1,2,8},{1,2},{1,3,4,5},{1,3,4,6},{1,3,4,7},{1,3,4,8},{1,3,4},{1,3,5,6},{1,3,5,7},{1,3,5,8},{1,3,5},{1,3,6,7},{1,3,6,8},{1,3,6},{1,3,7,8},{1,3,7},{1,3,8},{1,3},{1,4,5,6},{1,4,5,7},{1,4,5,8},{1,4,5},{1,4,6,7},{1,4,6,8},{1,4,6},{1,4,7,8},{1,4,7},{1,4,8},{1,4},{1,5,6,7},{1,5,6,8},{1,5,6},{1,5,7,8},{1,5,7},{1,5,8},{1,5},{1,6,7,8},{1,6,7},{1,6,8},{1,6},{1,7,8},{1,7},{1,8},{1},{2,3,4,5},{2,3,4,6},{2,3,4,7},{2,3,4,8},{2,3,4},{2,3,5,6},{2,3,5,7},{2,3,5,8},{2,3,5},{2,3,6,7},{2,3,6,8},{2,3,6},{2,3,7,8},{2,3,7},{2,3,8},{2,3},{2,4,5,6},{2,4,5,7},{2,4,5,8},{2,4,5},{2,4,6,7},{2,4,6,8},{2,4,6},{2,4,7,8},{2,4,7},{2,4,8},{2,4},{2,5,6,7},{2,5,6,8},{2,5,6},{2,5,7,8},{2,5,7},{2,5,8},{2,5},{2,6,7,8},{2,6,7},{2,6,8},{2,6},{2,7,8},{2,7},{2,8},{3,4,5,6},{3,4,5,7},{3,4,5,8},{3,4,5},{3,4,6,7},{3,4,6,8},{3,4,6},{3,4,7,8},{3,4,7},{3,4,8},{3,4},{3,5,6,7},{3,5,6,8},{3,5,6},{3,5,7,8},{3,5,7},{3,5,8},{3,5},{3,6,7,8},{3,6,7},{3,6,8},{3,6},{3,7,8},{3,7},{3,8},{4,5,6,7},{4,5,6,8},{4,5,6},{4,5,7,8},{4,5,7},{4,5,8},{4,5},{4,6,7,8},{4,6,7},{4,6,8},{4,6},{4,7,8},{4,7},{4,8},{5,6,7,8},{5,6,7},{5,6,8},{5,6},{5,7,8},{5,7},{5,8},{6,7,8},{6,7},{6,8},{7,8}};                                                                        
vector<vector<int> > doOtoczki = {{5,6},{5,7},{5,8},{5},{6,7},{6,8},{6},{7,8},{7},{8},{}};
vector<vector<int> > otoczkaa = {{1,4},{1,2},{2,3},{3,4}};

bool checkPlanar(vector<vector<int> > *graf, int blue, int red)
{

  // This program illustrates a simple use of boyer_myrvold_planar_embedding
  // as a simple yes/no test for planarity.

  gr K(blue+red+1);
  for(int i = 0; i<graf->size();i++){
    for (int j = 0; j<(*graf)[i].size();j++){
      add_edge(i, (*graf)[i][j]+blue-1, K);
      //cout<<"edge "<<i<<" "<<graf[i][j]+blue-1<<"\n";
    }
  }
  add_edge(0,blue+red, K);
  add_edge(1,blue+red, K);
  add_edge(2,blue+red, K);
  add_edge(3,blue+red, K);
  add_edge(blue,blue+red, K);
  add_edge(blue+1,blue+red, K);
  add_edge(blue+2,blue+red, K);
  add_edge(blue+3,blue+red, K);
  if (boyer_myrvold_planarity_test(K))
    return true;
  else
  {//cout<<"not planar\n";
    return false;
  }}
vector<vector<int> > *changeGraf(vector<vector<int> > *graf,int blue, int red){
  vector<vector<int> > *res = new vector<vector<int> >();
  for(int i = 0;i<graf->size();i++){
    vector<int> tmp;
    for(int j=0; j<(*graf)[i].size();j++){
      tmp.push_back((*graf)[i][j]+blue-1);
    }
    res->push_back(tmp);
  }
  for (int i = 0; i<red; i++){
    vector<int> tmp;
    res->push_back(tmp);
  }
  for (int j = 0;j<graf->size();j++){
    for(int z =0; z<(*graf)[j].size();z++){
      (*res)[blue+(*graf)[j][z]-1].push_back(j);
    }
  }
  return res;
}
bool visited[20];
int minPath(int start, int end, vector<vector<int> > *graf){
  queue<pair<int,int> >q;
  q.push(make_pair(start,0));
  visited[start] = true;
  while(!q.empty()){
    pair<int,int> p = q.front();
    q.pop();
    visited[p.first]=true;
    if(p.first==end) return p.second;
    for(int i=0;i<graf[p.first].size();i++){
      if (!visited[(*graf)[p.first][i]]){
        q.push(make_pair((*graf)[p.first][i],p.second+1));
      }
    }
  }
  return 100;


}
bool checkPath(vector<vector<int> > *graf, int blue, int red, int otoczka){
  for (int i =0; i<red; i++){
    vector<vector<int> > *graf2 = changeGraf(graf,blue,red);
    for (int j = 0; j<20;j++) visited[j]=false;
    int path1 = minPath(0,i+blue,graf2);
    for (int j = 0; j<20;j++) visited[j]=false;
    int path2 = minPath(i+blue,otoczka/2,graf2);
    delete graf2;
    if (path1+path2>4){
      return false;}
  }
  return true;
}

bool properOtoczka(vector<vector<int> > &g, int blue, int red, int otoczka) {
  if ((g[0][0]==1) && (g[0][1]==4) && (g[1][0]==1) && (g[1][1]==2) && 
      (g[2][0]==2)&&(g[2][1]==3)&&(g[3][0]==3)&&(g[3][1]==4))return true;
  return false;
}

bool allRed(vector<vector<int> > *graf, int blue, int red) {
  set<int> s;
  for(int i = 0;i<graf->size();i++){
    for(int j =0; j<(*graf)[i].size();j++){
      s.insert((*graf)[i][j]);
      if (s.size()==red) {
        return true;
      }}

  }
  return false;
}
bool podzbior(vector<int> &v1, vector<int>&v2){
  int j = 0;
  for(int i = 0; i<v1.size();i++){
    if (j>=v2.size()) return false;
    while (v2[j]<v1[i]) j++;
    if (j>=v2.size()) return false;
    if (v2[j]==v1[i]) j++;
    else {

      return false;}

  }
  return true;
}
bool rule1(vector<vector<int> > *graf, int blue, int red, int otoczka) {

  for(int i = 0; i < graf->size();i++){
    for(int j = i+1; j<graf->size();j++){
      if (podzbior((*graf)[i],(*graf)[j])||podzbior((*graf)[j],(*graf)[i]))  {
        return false;
      }
    }
  }
  return true;
} 
bool rule12(vector<vector<int> > *graf, int blue, int red, int otoczka) {
  vector<vector<int> > *g2 = changeGraf(graf,blue,red);

  for(int i = 0; i < g2->size();i++){
    for(int j = i+1; j<g2->size();j++){
      if (podzbior((*g2)[i],(*g2)[j])||podzbior((*g2)[j],(*g2)[i]))  {
        delete g2;
        return false;
      }
    }
  }
  delete g2;
  return true;
}


bool check(vector<vector<int> > *graf, int blue, int red, int otoczka) {
  if (rule12(graf,blue,red,otoczka) 
      &&allRed(graf,blue,red)&&checkPath(graf,blue,red,otoczka) &&
      checkPlanar(graf,blue,red)) 
    return true;
  else return false;
}	

vector<int> merger(vector<int> &a, vector<int> &b){
  vector<int> res = a;
  res.insert(res.end(),b.begin(),b.end());
  return res;
}

vector<vector<vector<int> > > tworzOtoczke(int blue, int red, int otoczka){
  vector<vector<vector<int> > > res;
  for(int i1 = 0;i1< doOtoczki.size();i1++){
    for(int i2 = 0;i2< doOtoczki.size();i2++){
      for(int i3 = 0;i3< doOtoczki.size();i3++){
        for(int i4 = 0;i4< doOtoczki.size();i4++){
          vector<vector<int> > *g;
          g->push_back(merger(otoczkaa[0],doOtoczki[i1]));
          g->push_back(merger(otoczkaa[1],doOtoczki[i2]));
          g->push_back(merger(otoczkaa[2],doOtoczki[i3]));
          g->push_back(merger(otoczkaa[3],doOtoczki[i4]));
          if (checkPlanar(g,blue,red))
            res.push_back(*g);
        }


      }
    }
  cerr<<"end OTOCZKi "<<res.size()<<"\n";
  }
  return res;

}
vector<vector<int> > *tworzKoniec(int blue, int red, int otoczka ,long long i,long long q,int dif){
  vector<vector<int> >* g = new vector<vector<int> >();

  int i1;
  i1=i;
  for(int q =0; q<dif;q++){
    g->push_back(pod[i1%pod.size()]);
      i1 = i1/pod.size();
    }
    if (g->size()>0)
      if (rule1(g,blue,red,otoczka)&&checkPlanar(g,blue,red)) {
        return g;
      }
    return new vector<vector <int> >();
}
void threadsEnd(){
  m.lock();
  cerr<<"end procesu"<<ile<<"\n";
  ile--;
  if (ile==0) cerr<<"KONIEC\n";
  else cerr <<"STILL "<<ile<<" threads\n";
  m.unlock();

}
void tworzGraf(int blue, int red, int otoczka,long long beg,long long end,long long q, int dif, vector<vector<vector<int> > > &otoczkaa){
  int t=0;
  vector<vector<int> > *koniec;
  for(long long i = beg;i< end;i++){
    koniec = tworzKoniec(blue,red,otoczka,i,q,dif);

    if (koniec->size()!=0) {
    for (int i = 0; i<otoczkaa.size();i++){
        vector<vector<int> > *g = new vector<vector<int > >(otoczkaa[i]);
        g->insert(g->end(), koniec->begin(), koniec->end());

      if (check(g,blue,red,otoczka)) {
        wypiszGraf(g);
        t++;
      }

    delete g;
    }
    }
    delete koniec;
  }

  threadsEnd();
}


int main(){
  long long beg=0;
  long long mn;
  long long i = 0;
  int blue;
  cin>>blue;
  int red = 8;
  int otoczka = 4;
  long long all=1;
  for(int i=0;i<blue-otoczka;i++)
    all*=pod.size();
  cerr<<all<<"\n";
  mn = (all/MAX_THREADS);
  cerr<<mn<<"\n";
  thread allThreads[MAX_THREADS];
  vector<vector<vector<int> > > const otoczkaa = tworzOtoczke(blue,red,otoczka);
  while (beg<all){
    allThreads[i] = thread(bind(tworzGraf,blue,red,otoczka,beg,min(beg+mn,all),i, blue-otoczka,otoczkaa));
    beg+=mn+1;
    i++;
  }
  cerr<<i<<" end\n";
  ile = i;
  for (int j=0;j<i;j++)
    allThreads[j].join();
}
