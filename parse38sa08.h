#ifndef PARSE38SA08_H
#define PARSE38SA08_H

#include "./fuctioncmn.h"

#define MAXLENLEN 4096

typedef struct{
    double AttRef[3];   /*Att zj*/
    double VnRef[3];    /*Vn  zj*/
    double PosRef[3];   /*Pos zj*/
    double AttPos[3];   /*Att A08*/
    double VnPos[3];    /*Vn  A08*/
    double PosPos[3];   /*Pos A08*/
    double AttDiff[3];  /*zj - A08*/
    double time;        /*time pos*/
}A08Data_t;

int parseA08Data(const char *buff,A08Data_t *A08Data);
#endif // PARSE38SA08_H
