#include <iostream>
using namespace std;

const size_t N = 4, D = 2, K = 2;
double data[N][D] = {{0,0}, {1,1}, {10,10}, {9,11}};

double distance(double *a, double *b) {
  double result = 0.0;
  for (size_t i = 0; i < D; i++) {
    result += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return result;
}

int main() {
  double center[K][D] = {{0,0}, {10,10}};
  size_t cluster[N] = {0, 0, 0, 0};
  while (true) {
    // update cluster
    bool update = false;
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < K; j++) {
        if (distance(data[i], center[j]) < distance(data[i], center[cluster[i]])) {
          cluster[i] = j;
          update = true;
        }
      }
    }
    if (!update) break;
    // update center
    for (size_t i = 0; i < K; i++) {
      for (size_t j = 0; j < D; j++) {
        center[i][j] = 0.0;
      }
      size_t num = 0;
      for (size_t j = 0; j < N; j++) {
        if (cluster[j] == i) {
          for (size_t d = 0; d < D; d++) {
            center[j][d] += data[i][d];
          }
          num ++;
        }
      }
      for (size_t d = 0; d < D; d++) {
        center[i][d] /= (double)num;
      }
    }
  }
  // output cluster number
  for (int i = 0; i < N; i++) {
    cout << i << ": " << cluster[i] << endl;
  }
  return 0;
}
