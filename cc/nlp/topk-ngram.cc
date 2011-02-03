#include <iostream>                                                                                                                                                                                                     
#include <sstream>                                                                                                                                                                                                     
#include <unistd.h>
#include <szaru.h>                              
using namespace std;
using namespace SZaru;                                                       

//split
inline vector<string> split(const string &str, char delim){
  istringstream iss(str); string tmp; vector<string> res;
  while(getline(iss, tmp, delim)) res.push_back(tmp);
  return res;
}
int main(int argc, char *argv[]) {
  int result;
  int k = 1000000;
  int n = 5;
  bool all = false;

  //parse options
  while((result=getopt(argc,argv,"k:n:a"))!=-1){
    switch(result){
      case 'k':
        k = strtol(optarg, NULL, 0);
        break;
      case 'n':
        n = strtol(optarg, NULL, 0);
        break;
      case 'a':
        all = true;
        break;
    }
  }

  //Top-k estimate with SZaru.
  TopEstimator<int32_t> *topEst = TopEstimator<int32_t>::Create(k);                                         

  string line;
  while (getline(cin, line)) {
    vector<string> words = split(line, ' ');
    for (int i = 0; i < words.size(); i++) {
      string ngram;
      for (int j = 0; j < n && i + j < words.size(); j++) {
        ngram += words[i+j];
        if (all || j == n - 1)
          topEst->AddElem(ngram);
        ngram += ' ';
      }
    }
  }

  //Output estimated top-k elements in sorted order.
  vector< TopEstimator<int32_t>::Elem > topElems;                                                           
  topEst->Estimate(topElems);

  for (int i = 0; i < topElems.size(); i++) {
    cout << topElems[i].value << "\t" << topElems[i].weight << endl;
  }
  delete topEst;      
}
