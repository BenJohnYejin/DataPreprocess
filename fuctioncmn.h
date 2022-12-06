#ifndef FUCTIONCMN_H
#define FUCTIONCMN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <io.h>

#define MAXLEN       1024                /*the char num of line*/
#define MAXSPLITCHAR 256                 /*max split char num aline*/
#define PI           3.14159265358979    /*const pi value*/

/*GNSS Nema opt*/
typedef struct{
    uint8_t GNSSFlag;                /*GNSS Flag*/
    char    dirGNSSNema[256];        /*dir*/
    char    lastLabel[25];           /*last label*/
    char    strBack[10];             /*file extension*/
}GNSSNema_opt;

/*HEX opt*/
typedef struct{
    uint8_t HEXFlag;                 /*HEX Flag*/
    char    dirHEX[256];             /*dir*/
    char    strBack[10];             /*file extension*/
}HEX_opt;

/*A08 opt*/
typedef struct{
    uint8_t A08Flag;                 /*A08 Flag*/
    char    dirA08[256];             /*dir*/
    char    strBack[10];             /*file extension*/
}A08_opt;

/*control opt*/
typedef struct{
    GNSSNema_opt GNSSOPT;  /*parse GNSS */
    HEX_opt      HEXOPT;   /*parse HEX*/
    A08_opt      A0838OPT; /*parse 38S*/
}process_opt;


/*some base function to reslove str*/
/*str to number*/
double str2num(const char *s, int i, int n);
/*deg to radius*/
double deg2rad(const double deg);
/*get split char's num in char buff*/
int    splitNumPos(const char* buf, int* index, const char splitChar);
/*get file num with strback in the path*/
int    filesearch(const char* path, const char* strBack, char fileList[100][256]);/*查找特定后缀名文件，置入fileList中*/
/*trim the last char*/
int    strim(char* s);
/*decode the ini file line*/
char*  decodeIni(const char* buff);

/*parse signal data*/
extern int decodeOutNEMA0183(const char *DirIn, const char *fileName, const char *lastLabel);
extern int decodeOutIPOS3Data(const char* DirIn, const char* fileName);
extern int decodeOutIPOS3Data76(const char* DirIn, const char* fileName);
extern int parseOutA08Data(const char* DirIn, const char* fileName);/*38S A08 file*/

/*read ini*/
extern int readIni(const char* DirIn, const char* fileName, process_opt *opt);
/*parse data*/
extern int parseOutData(const process_opt *opt);

#endif // FUCTIONCMN_H
