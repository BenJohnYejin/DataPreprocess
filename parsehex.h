#ifndef PARSEHEX_H
#define PARSEHEX_H

#include "./fuctioncmn.h"

#define IPOS3LENGTH58 58   /*IPOS3数据帧大小*/
#define IPOS3LENGTH76 76   /*IPOS3数据帧大小*/

typedef union{           /*IPOS3数据帧*/
    struct{
        char    Header[3];  /*00-02*/
        char    Att[3][2];
        char    Gyr[3][2];
        char    Acc[3][2];  /*03-20*/
        char    Pos[3][4];
        char    Vel[3][2];  /*21-38*/
        char    Flag;       /*39*/
        char    Week[2];    /*40-41*/
        char    StaNum;
        char    RTKTime;
        char    ODVel[2];   /*42-45*/
        char    Data[3][2]; /*46-51*/
        char    UtcSec[4];  /*52-55*/
        char    DataType;
        char    Check;      /*56-57*/
    }data;
    char byte[IPOS3LENGTH58];
}IPOS3FrameData58_t;

typedef union{           /*IPOS3数据帧*/
    struct{
        char    Header[3];  /*00-02*/
        char    Att[3][2];
        char    Gyr[3][2];
        char    Acc[3][2];  /*03-20*/
        char    Pos[3][4];
        char    Vel[3][2];  /*21-38*/
        char    Flag;       /*39*/
        char    Week[2];    /*40-41*/
        char    StaNum;
        char    RTKTime;
        char    ODVel[2];   /*42-45*/
        char    Data[3][2]; /*46-51*/
        char    UtcSec[4];  /*52-55*/
        char    DataType;
        char    Check;      /*56-57*/
      /*============58Bytes================*/
        char    Gyr0[3][2];
        char    Acc0[3][2]; /*00-11*/
        char    DataType0;  /*12*/
        char    Data0[4];   /*13-16*/
        char    check0;     /*17*/
      /*============18Bytes================*/
    }data;
    char byte[IPOS3LENGTH76];
}IPOS3FrameData76_t;

typedef struct{          /*IPOS3数据帧*/
    double  Att[3];
    double  Gyr[3];
    double  Acc[3];
    double  Pos[3];
    double  Vel[3];
    double  Flag;
    double  Week;
    double  StaNum;
    double  RTKTime;
    double  ODVel;
    double  Data[3];
    double  UtcSec;
    double  DataType;
}IPOS3Data58_t;

typedef struct{          /*IPOS3数据帧*/
    double  Att[3];
    double  Gyr[3];
    double  Acc[3];
    double  Pos[3];
    double  Vel[3];
    double  Flag;
    double  Week;
    double  StaNum;
    double  RTKTime;
    double  ODVel;

    double  Data[4];
    double  stdPOS[3];
    double  stdVEL[3];
    double  stdATT[3];

    double  UtcSec;
    double  DataType;

    double  Gyr0[3];
    double  Acc0[3];
    double  POSGNSS[3];
    double  VELGNSS[3];
    double  stdPOSGNSS[3];
    double  yawGNSS;
    double  hoop;
    double  yawRMS;
    double  GNSSFlag;
    double  DataType0;

    double  twistCov[36];
    double  posCov[9];
}IPOS3Data76_t;

typedef struct{          /*IPOS3数据*/
    int n,nmax;          /*帧数，已分配大小*/
    IPOS3Data58_t *data;   /*数据帧*/
}IPOS3Data;

void IPOS3Process58(const IPOS3FrameData58_t *frameData,IPOS3Data58_t* data);
void IPOS3Process76(const IPOS3FrameData76_t *frameData,IPOS3Data76_t* data);
int decodeIPOS3Data(const char* DirIn, const char* fileName, IPOS3Data* IPOS3Data_);
int outIPOS3Data58(const char* DirOut,const char* fileName,const IPOS3Data* data,const int opt);
int decodeOutIPOS3Data76(const char *DirIn, const char *fileName);

#endif // PARSEHEX_H
