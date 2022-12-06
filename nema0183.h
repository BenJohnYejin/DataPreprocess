#ifndef NEMA0183_H
#define NEMA0183_H

#include "./fuctioncmn.h"

typedef struct
{
    double week; 	    /*周*/
    double weeksec; 	/*秒*/

    double latitude;	/*纬度*/
    double longitude;	/*经度*/
    double altitude;	/*海拔高度*/

    double velE;		/*东速*/
    double velN;		/*北速*/
    double velU;		/*天速*/
    double yawtrj;      /*航迹角*/

    double yawAn;       /*双天线航向*/
    double yawRms;      /*航向RMS*/

    double staNum;      /*卫星个数*/

    double posLatStd;	/*东向位置std*/
    double posLonStd;	/*北向位置std*/
    double posAltStd;	/*天向位置std*/

    double flagGNSS;    /*GNSSFLAG*/
    double dop;			/*DOP*/
}NEMA0183_t;

typedef struct
{
    int n,nmax;
    NEMA0183_t* data;
}NEMA0183;

int decodeOutNEMA0183(const char *DirIn, const char *fileName, const char *lastLabel);
int decodeNEMA0183(const char* DirIn,const char* fileName,NEMA0183* data,const char* lastLabel);
int outLatNEMA(const char* DirOut,const char* fileName,const NEMA0183* data);
#endif // NEMA0183_H
