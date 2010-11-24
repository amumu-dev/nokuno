#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

// SRM 204 Level One
class Medici {
    public:
        int winner(int fame[], int fortune[], int secrets[], size_t size, bool debug = false) {
            int score[size];
            for (int i=0; i<size; i++) {
                score[i] = fame[i];
                if (score[i] > fortune[i])
                    score[i] = fortune[i];
                if (score[i] > secrets[i])
                    score[i] = secrets[i];
                if (debug)
                    cout << score[i] << endl;
            }
            int maximum = 0;
            int result = 0;
            bool draw = false;
            for (int i=0; i<size; i++) {
                if (score[i] > maximum) {
                    result = i;
                    maximum = score[i];
                    draw = false;
                } else if (score[i] == maximum) {
                    draw = true;
                }
            }
            if (draw)
                return -1;
            return result;
        }
};
int main() {
    Medici obj;
    {// Test 0
        int fame[] = { 20, 30, 50 };
        int fortune[] = { 60, 80, 40 };
        int secrets[] = { 40, 30, 50 };

        int result = obj.winner(fame, fortune, secrets, sizeof(fame)/sizeof(int));
        assert(result == 2);
    }
    {// Test 1
        int fame[] = { 0, 100, 100, 100 };
        int fortune[] = { 100,   0, 100,  50 };
        int secrets[] = {  50,  50,  50, 100 };

        int result = obj.winner(fame, fortune, secrets, sizeof(fame)/sizeof(int));
        assert(result == -1);
    }
    {// Test 2
        int fame[] = { 1, 0 };
        int fortune[] = { 1, 99 };
        int secrets[] = { 1, 99 }; 

        int result = obj.winner(fame, fortune, secrets, sizeof(fame)/sizeof(int));
        assert(result == 0);
    }
    {// Test 3
        int fame[] = { 39, 42, 57 };
        int fortune[] = { 42, 39, 57 };
        int secrets[] = { 57, 39, 42 };

        int result = obj.winner(fame, fortune, secrets, sizeof(fame)/sizeof(int));
        assert(result == 2);
    }
    {// Test 4
        int fame[] =    { 3, 98, 0, 71, 81, 85, 99, 58, 93, 79, 100, 98, 73, 83, 52, 100, 37, 93, 39, 27 };
        int fortune[] = { 96, 34, 45, 20, 72, 71, 7, 18, 47, 35, 54, 51, 52, 21, 49, 20, 44, 72, 90, 93 };
        int secrets[] = { 15, 72, 50, 84, 41, 49, 35, 71, 20, 29, 73, 18, 35, 61, 70, 34, 59, 68, 90, 18 };

        int result = obj.winner(fame, fortune, secrets, sizeof(fame)/sizeof(int));
        assert(result == 17);
    }
    return 0;
}
