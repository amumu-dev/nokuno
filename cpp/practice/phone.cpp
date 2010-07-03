#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#define SIZE 256
using namespace std;

/*
const char *table[] = {
	"",//"!\"#$%&'()*+,;<=>? 0",
	"",//"./@~-:_[\\]^`{|}1",
	"abc",//ABC",
	"def",//DEF3",
	"ghi",//GHI4",
	"jkl",//JKL5",
	"mno",//MNO6",
	"pqrs",//PQRS7",
	"tuv",//TUV8",
	"wxyz",//WXYZ9",
};
*/
const char *table[] = {
	"",
	"",
	"abcABC",
	"defDEF",
	"ghiGHI",
	"jklJKL",
	"mnoMNO",
	"pqrsPQRS",
	"tuvTUV",
	"wxyzWXYZ",
};

map<string,int> Load(char *file){
	map<string,int> result;
	FILE *fp = fopen(file,"r");
	char buffer[SIZE];
	while( fgets(buffer,SIZE,fp) != NULL ) {
		buffer[(int)strlen(buffer)-1] = '\0';
		result.insert(pair<string,int>(buffer,1));
		//printf("%s %d\n",buffer);
	}
	fclose(fp);
	return result;
}

vector<string> Phone(int *digets,int size,string word,int n,map<string,int> &dict) {
	if( n==0 ) {
		vector<string> result;
		if(dict.count(word.c_str())>0) {
			result.push_back(word);
		}
		return result;
	}
	string s = table[digets[size-n]];
	vector<string> result;
	for(int i=0; i<s.size(); i++){
		vector<string> temp = Phone(digets,size,word+s[i],n-1,dict);
		for(int j=0; j<temp.size(); j++){
			result.push_back(temp[j]);
		}
	}
	return result;
}

int main(){
	//int digits[] = {5,4,6,8,9};	//Linux
	int digits[] = {2,4,4};
	int n = sizeof(digits)/sizeof(int);
	map<string,int> dict = Load("linux.words");
	vector<string> result = Phone(digits,n,"",n,dict);
	for(int i=0; i<result.size(); i++) {
		printf("%s\n",result[i].c_str());
	}
	return 0;
}
