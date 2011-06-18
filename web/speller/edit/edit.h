#ifndef EDIT_H
#define EDTI_H

#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

// edit operation with position
inline void edit(const string &input, const size_t position, vector<string> &result) {
  string cand;
  const string alphabet = " abcdefghijklmnopqrstuvwxyz";
  // end of string
  if (position == input.length()) {
    // insert
    for (size_t j = 0; j < alphabet.length(); j++) {
      cand = input + alphabet[j];
      result.push_back(cand);
    }
    return;
  }

  // replace
  for (size_t j = 0; j < alphabet.length(); j++) {
    cand = input;
    cand[position] = alphabet[j];
    result.push_back(cand);
  }
  // insert
  for (size_t j = 0; j < alphabet.length(); j++) {
    cand = input.substr(0, position) + alphabet[j] + input.substr(position);
    result.push_back(cand);
  }
  cand = input.substr(0, position) + input.substr(position+1);
  result.push_back(cand);
}

// edit operation
inline void edit(const string &input, vector<string> &result) {
  string cand;
  const string alphabet = " abcdefghijklmnopqrstuvwxyz";
  // replace
  for (size_t i = 0; i < input.length(); i++) {
    for (size_t j = 0; j < alphabet.length(); j++) {
      cand = input;
      cand[i] = alphabet[j];
      result.push_back(cand);
    }
  }
  // insert
  for (size_t i = 0; i < input.length() + 1; i++) {
    for (size_t j = 0; j < alphabet.length(); j++) {
      cand = input.substr(0, i) + alphabet[j] + input.substr(i);
      result.push_back(cand);
    }
  }
  // delete
  for (size_t i = 0; i < input.length(); i++) {
    cand = input.substr(0, i) + input.substr(i+1);
    result.push_back(cand);
  }
}

// transpose operation
inline void transpose(const string &input, vector<string> &result) {
  for (size_t i = 0; i < input.length(); i++) {
    for (size_t j = i+1; j < input.length(); j++) {
      string temp = input;
      swap(temp[i], temp[j]);
      result.push_back(temp);
    }
  }
}

//urldecode
inline string urldecode(const string &url) {
  string buffer = "";

  for (size_t i = 0; i < url.length(); i++) {
    size_t j = i ;
    char ch = url.at(j);
    if (ch == '%'){
      char tmpstr[] = "0x0__";
      int chnum;
      tmpstr[3] = url.at(j+1);
      tmpstr[4] = url.at(j+2);
      chnum = strtol(tmpstr, NULL, 16);
      buffer += chnum;
      i += 2;
    } else if (ch == '+') {
      buffer += ' ';
    } else {
      buffer += ch;
    }
  }
  return buffer;
}

//split
inline vector<string> split(const string &input, char delim){
  vector<string> result;
  istringstream iss(input);
  string temp;

  while(getline(iss, temp, delim))
    result.push_back(temp);
  return result;
}

//parse_query
inline string parse_query(const string &query) {
  vector<string> result = split(query, '&');
  for (size_t i = 0; i < result.size(); i++) {
    vector<string> param = split(result[i], '=');
    if (param[0] == "q")
      return param[1];
  }
  return "";
}
// run spell generator
inline void run(const string &query, const int limit) {
  int c = 0;
  int actual_limit = limit / query.length();
  cout << query << "\t1\n";
  c ++;

  // output edit1 candidates
  vector<string> result;
  edit(query, result);
  for (size_t i = 0; i < result.size(); i++) {
    cout << result[i] << "\t0\n";
    if (++c >= actual_limit)
      return;
  }
  // output transpose candidates
  vector<string> transposed;
  transpose(query, transposed);
  for (size_t i = 0; i < transposed.size(); i++) {
    cout << transposed[i] << "\t0\n";
    if (++c >= actual_limit)
      return;
  }

  // output edit2 candidates
  for (size_t i = 0; i <= query.length(); i++) {
    vector<string> result1;
    edit(query, i, result1);
    for (size_t j = 0; j < result1.size(); j++) {
      size_t start = i + 1 + result1[j].length() - query.length();
      for (size_t k = start; k <= result1[j].length(); k++) {
        vector<string> result2;
        edit(result1[j], k, result2);
        for (size_t l = 0; l < result2.size(); l++) {
          cout << result2[l] << "\t0\n";
          if (++c >= actual_limit)
            return;
        }
      }
    }
  }
}

#endif
