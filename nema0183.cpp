#include "nema0183.h"

/*---解析GGA------------------------------------------
* args   : char*       buff      I   解析字符串
*          NEMA0183_t* data      O   数据
*
* return : 1-sucess 0-fail
*
* note   : 2       3   5   7     6  10&12
*         Second  lat lon flag  DOP  hgt
*----------------------------------------------------------------*/
static int GGAParse(const char *buff, NEMA0183_t* data){
    int index[MAXSPLITCHAR];
    double tmp = 0;
    if(splitNumPos(buff,index,',')){
        data->weeksec      = str2num(buff,index[0]+1,index[1]);

        double lat = str2num(buff,index[1]+1,index[2]);
        double lon = str2num(buff,index[3]+1,index[4]);

        data->latitude     = deg2rad(lat);
        data->longitude    = deg2rad(lon);
        data->altitude     = str2num(buff,index[8]+1,index[9]) + str2num(buff,index[10]+1,index[11]);

        tmp = str2num(buff,index[5]+1,index[6]);

        if(tmp < 0.99) {
            data->flagGNSS = 0;
        }

        if(tmp == 5)
            data->flagGNSS = 3;
        else if(tmp == 4)
            data->flagGNSS = 1;
        else if(tmp == 1)
            data->flagGNSS = 5;
        else if(tmp == 5)
            data->flagGNSS = 3;
        else if(tmp == 2)
            data->flagGNSS = 4;

        data->staNum       = str2num(buff,index[6]+1,index[7]);
        data->dop          = str2num(buff,index[7]+1,index[8]);
        return 1;
    }else return 0;
}

/*---解析VEL------------------------------------------
* args   : char*       buff      I   解析字符串
*          NEMA0183_t* data      O   数据
*
* return : 1-sucess 0-fail
*
* note   :  6     7     14    15     16      10
*          week second velH  velV  yawTrj   Statue
*----------------------------------------------------------------*/
static int BESTVELParse(const char *buff, NEMA0183_t* data){
    int index[MAXSPLITCHAR];
    if(splitNumPos(buff,index,',')){
        data->week    = str2num(buff,index[4]+1,index[5]);
        data->weeksec = str2num(buff,index[5]+1,index[6]);

        if (strstr(buff,"INSUFFICIENT_OBS")){
            return 2;
        }
        double velH   = str2num(buff,index[12]+1,index[13]);
        data->yawtrj  = str2num(buff,index[13]+1,index[14])/180*PI;
        data->velU    = str2num(buff,index[14]+1,index[15]);

        data->velE    = velH * cos(data->yawtrj);
        data->velN    = velH * sin(data->yawtrj);
        return 2;
    }else return 0;
}

/*---解析ZDA------------------------------------------
* args   : char*       buff      I   解析字符串
*          NEMA0183_t* data      O   数据
*
* return : 2,3,4,5
*
* note   : yymmdd.ss
*----------------------------------------------------------------*/
static int ZDAParse(const char *buff, NEMA0183_t* data){
    int index[MAXSPLITCHAR];
    if(splitNumPos(buff,index,',')){
//        data->time.year    = str2num(buff,index[0]+1,index[1]);
//        data->time.month   = str2num(buff,index[1]+1,index[2]);
//        data->time.day     = str2num(buff,index[2]+1,index[3]);
//        data->time.utcsec  = str2num(buff,index[3]+1,index[4]);
        return 1;
    }else return 0;
}

/*---解析GST------------------------------------------
* args   : char*       buff      I   解析字符串
*          NEMA0183_t* data      O   数据
*
* return : 1-sucess 0-fail
*
* note   : 2        7        8          9
*        Second stdPOSLat stdPOSLon stdPOSAlt
*
*----------------------------------------------------------------*/
static int GSTParse(const char *buff, NEMA0183_t* data){
    int index[MAXSPLITCHAR];
    if(splitNumPos(buff,index,',')){
        data->weeksec      = str2num(buff,index[0]+1,index[1]);
        data->posLatStd    = str2num(buff,index[5]+1,index[6]);
        data->posLonStd    = str2num(buff,index[6]+1,index[7]);
        data->posAltStd    = str2num(buff,index[7]+1,index[8]);
        return 4;
    }else return 0;
}

/*---解析GGA------------------------------------------
* args   : char*       buff      I   解析字符串
*          NEMA0183_t* data      O   数据
*
* return : 1-sucess 0-fail
*
* note   : 6     7        12        13     16
*         Week  Second  baseLine   Yaw   Yawstd
*----------------------------------------------------------------*/
static int HEADINGParse(const char *buff, NEMA0183_t* data){

    int index[MAXSPLITCHAR];
    if(splitNumPos(buff,index,',')){
        data->week         = str2num(buff,index[4]+1,index[5]);
        data->weeksec      = str2num(buff,index[5]+1,index[6]);
        if (strstr(buff,"INSUFFICIENT_OBS")){
            return 8;
        }

        data->yawAn        = str2num(buff,index[11]+1,index[12])*PI/180;
        data->yawRms       = str2num(buff,index[14]+1,index[15]);
        return 8;
    }else return 0;
}

/* 解析0183数据 ------------------------------------------------------
* args   : char*      buff          I   解析字符串
*          NEMA0183_t NEMA数据       I   数据
*
* return : 0-NONE，-1-error，1-success
*
* note   : 单行解析，按顺序B:\yj\01_Code\97_MyCode\build-dataprocess解析
*----------------------------------------------------------------*/
static int decodeNEMA0183t(const char *buff,NEMA0183_t* data){

    if (strstr(buff,"GGA"))     return GGAParse(buff,data);
    if (strstr(buff,"BESTVEL")) return BESTVELParse(buff,data);
    if (strstr(buff,"ZDA"))     ZDAParse(buff,data);
    if (strstr(buff,"GST"))     return GSTParse(buff,data);
    if (strstr(buff,"HEADING")) return HEADINGParse(buff,data);
    return 0;
}

int decodeOutNEMA0183(const char *DirIn, const char *fileName, const char *lastLabel)
{
    if (!fileName) return 0;
    char fileNameIn[256] = "\0" ;
    sprintf(fileNameIn,"%s%s%s",DirIn,"//",fileName);
    FILE *fpIn,*fpOut;
    if (!(fpIn=fopen(fileNameIn,"r")))
        return 0;

    char* fileNameOut = fileNameIn;
    int ptr = strrchr(fileNameOut,'.') - fileNameOut;
    strcpy(&fileNameOut[ptr],".lat");
    if (!(fpOut=fopen(fileNameOut,"w")))
        return 0;

    char buff[MAXLEN];
    NEMA0183_t NemaDatat={0};
    int staSum = 0;
    int sta    = 0;
    while (fgets(buff,MAXLEN,fpIn)) {
        sta = decodeNEMA0183t(buff,&NemaDatat);
        staSum += sta;
        /*1+2+4+8 = 15,all data was parse*/
        /*heading was last lable*/
        if(sta == 8 && staSum >= 15){
            NEMA0183_t NeamCopy = NemaDatat;
            /*flag == 0, trjAngle >0.0001
             * all data clear but time*/
            if (NemaDatat.flagGNSS < 0.99 || NemaDatat.yawtrj < 0.0001){
                NemaDatat={0};
                NemaDatat.week    = NeamCopy.week;
                NemaDatat.weeksec = NeamCopy.weeksec;
            }
            fprintf(fpOut,"%4.f %8.3f %15.12f %15.12f %6.3f %6.3f %6.3f %6.3f ",
                    NemaDatat.week,NemaDatat.weeksec,
                    NemaDatat.latitude,NemaDatat.longitude,NemaDatat.altitude,
                    NemaDatat.velE,NemaDatat.velN,NemaDatat.velU);
            fprintf(fpOut,"%6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %1.f %6.3f %3.f\n",
                    NemaDatat.yawtrj,NemaDatat.yawAn,NemaDatat.yawRms,
                    NemaDatat.posLatStd,NemaDatat.posLonStd,NemaDatat.posAltStd,
                    NemaDatat.flagGNSS,NemaDatat.dop,NemaDatat.staNum);
            NemaDatat = {0};
            sta = 0;
        }
    }
    fclose(fpIn);
    fclose(fpOut);
    return 1;
}

/* 解析0183数据 ------------------------------------------------------
* args   : NEMA0183   dataNema      IO   所有数据
*          NEMA0183_t data          I    单个数据
*
* return : 0-NONE，-1-error，1-success
*
* note   : 结构体累加
*-----------------------------------------------------------------------------*/
static int addNEMA0183(NEMA0183* dataNema,const NEMA0183_t* data){
    NEMA0183_t *dataNew;
    if (dataNema->n >= dataNema->nmax){
        dataNema->nmax += 1024;
        if (!(dataNew = (NEMA0183_t*)realloc(dataNema->data,sizeof(NEMA0183_t)*dataNema->nmax) )){
            free(dataNema->data);dataNema->data = NULL;dataNema->n = dataNema->nmax = 0;
            return 0;
        }
        dataNema->data = dataNew;
    }
    dataNema->data[dataNema->n++] = *data;
    return 1;
}
/* 解析0183数据 ------------------------------------------------------
* args   : char*    fileName    I    输入文件文件名
*          NEMA0183 data        IO   数据
*
* return : 0-NONE，-2-error
*
* note   :
*-----------------------------------------------------------------*/
int decodeNEMA0183(const char* DirIn,const char* fileNameIn,NEMA0183* data,const char* lastLabel){
    if (!fileNameIn) return 0;
    char fileName[256] = "\0" ;
    sprintf(fileName,"%s%s",DirIn,fileNameIn);
    FILE *fp;
    if (!(fp=fopen(fileName,"r")))
        return 0;

    char buff[MAXLEN];
    NEMA0183_t NemaDatat={0};

    while (fgets(buff,MAXLEN,fp)) {
        if(decodeNEMA0183t(buff,&NemaDatat) ){
            if(strstr(buff,lastLabel))
                if(!addNEMA0183(data,&NemaDatat)) return -2;
        }
    }
    fclose(fp);
    return 1;
}

/* 输出为LAT信息 ------------------------------------------------------
* args   : char*    fileNameOut I    输入文件文件名
*          NEMA0183 data        I    数据
*
* return : 0-NONE，-1-error
*
* note   :
* */
int outLatNEMA(const char* DirOut,const char* fileNameOut,const NEMA0183* data){
    if (!fileNameOut) return 0;
    char fileName[256] = "\0" ;
    sprintf(fileName,"%s%s",DirOut,fileNameOut);
    FILE *fp;
    if (!(fp=fopen(fileName,"w")))
        return 0;
    for (int j=0;j<data->n;j++){
//        data->data[j].latitude *= 180/PI;
//        data->data[j].longitude *= 180/PI;
//        data->data[j].yawtrj *= 180/PI;
//        data->data[j].yawAn *= 180/PI;
        fprintf(fp,"%4.f %8.3f %11.8f %11.8f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %1.f %6.3f %3.f\n",
                data->data[j].week,data->data[j].weeksec,
                data->data[j].latitude,data->data[j].longitude,data->data[j].altitude,
                data->data[j].velE,data->data[j].velN,data->data[j].velU,
                data->data[j].yawtrj,data->data[j].yawAn,data->data[j].yawRms,
                data->data[j].posLatStd,data->data[j].posLonStd,data->data[j].posAltStd,
                data->data[j].flagGNSS,data->data[j].dop,data->data[j].staNum);
    }
    fclose(fp);
    return 1;
}




