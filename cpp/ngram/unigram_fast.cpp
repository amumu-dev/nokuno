#include <tr1/unordered_map>
#include <string>
#include <iostream>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

using namespace std;
using namespace std::tr1;

struct myeq : std::binary_function<pair<int , int> , pair<int , int> , bool>{
    char * buf;
    myeq(char * b) : buf(b) {}
    bool operator() (const pair<int , int> & x , const pair<int , int> & y) const{
        char * s = buf + x.first;
        char * t = buf + y.first;
        char * se = buf + x.second; // *se == '\n'
        for( ; *s == *t && s != se ; ++s , ++t)
            ;
        // *s != *t or (*s == '\n' => *t == '\n')
        return *s == *t;
    }
};

struct myhash : std::unary_function<pair<int , int> , size_t>{
    char * buf;
    myhash(char * b) : buf(b) {}
    size_t operator()(const pair<int , int> & p) const{
        size_t h = 0;
        for(int i = p.first ; i < p.second ; ++i){
            h = h * 31 + buf[i];
        }
        return h;
    }
};

int main(){
    struct stat st;
    char * fileName = "jawiki_unigram_raw.txt";
    if(stat(fileName , &st)){
        perror("stat");
        return 1;
    }
    int fd = open(fileName  , O_RDONLY);
    char * buffer = new char[st.st_size];
    if(read(fd , buffer , st.st_size) != st.st_size){
        return 1;
    }
    int prev = 0;
    myhash h(buffer);
    myeq   e(buffer);
    unordered_map<pair<int , int> , int  , myhash , myeq> m(3 , h , e);
    for(size_t i = 0 ; i < st.st_size ; ++i){
        if(buffer[i] == '\n'){
            pair<int , int> p(prev , i);
            unordered_map< pair<int , int> , int  , myhash , myeq>::iterator it = m.find(p); 
            if(it != m.end()){
                it->second++;
            }else{
                m.insert(pair<pair<int,int> , int>(p , 1));
            }
            prev = i + 1;
        }
    }
    unordered_map<pair<int , int> , int>::iterator it;
    for(it = m.begin(); it != m.end(); ++it){
        string s(buffer + it->first.first , buffer + it->first.second);
        cout << s << " " << it->second << endl;
    }
    return 0;
}
