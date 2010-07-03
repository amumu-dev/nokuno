#include <stdio.h>

#define _16BIT         2
#define _32BIT         4
#define _64BIT         8
#define N_MODELS       5
#define N_TYPES        3

enum {
    TYPE_INT = 0,
    TYPE_LONG = 1,
    TYPE_POINTER = 2,
};

void datamodel()
{
    const char *modelstr[N_MODELS + 1] = {
        "LP32", "ILP32", "LP64", "LLP64", "ILP64", "unknown"
    };
    const int modelsize[N_MODELS][N_TYPES] = {
        { _16BIT, _32BIT, _32BIT },
        { _32BIT, _32BIT, _32BIT },
        { _32BIT, _64BIT, _64BIT },
        { _32BIT, _32BIT, _64BIT },
        { _64BIT, _64BIT, _64BIT },
    };

    int sizeofint, sizeoflong, sizeofpointer, model;

    sizeofint = sizeof(int);
    sizeoflong = sizeof(long);
    sizeofpointer = sizeof(void*);

    for( model = 0; model < N_MODELS; model++ )
    {
        if (
                sizeofint == modelsize[model][TYPE_INT] &&
                sizeoflong == modelsize[model][TYPE_LONG] &&
                sizeofpointer == modelsize[model][TYPE_POINTER]
           ) break;
    }

    printf(
            "sizeof(int) = %dbytes\n"
            "sizeof(long) = %dbytes\n"
            "sizeof(ptr) = %dbytes\n"
            "---------------------\n"
            "data model = %s\n"
            , sizeofint
            , sizeoflong
            , sizeofpointer
            , modelstr[model]
          );
}
int main() {
    datamodel();
    return 0;
}
