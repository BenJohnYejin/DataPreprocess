#include "fuctioncmn.h"

/*---字符串转数字 ------------------------------------------
* args   : char*      s          I   解析字符串
*          int        i          I   序号
*          int        n          I   个数
*
* return : 解析后数字
*
* note   :
*----------------------------------------------------------------*/
double str2num(const char *s, int i, int n){
    double value;
    char str[4096],*p=str;

    if (i<0||(int)strlen(s)<i||(int)sizeof(str)-1<n) return 0.0;
    for (s+=i;*s&&--n>=0;s++) *p++=*s=='d'||*s=='D'?'E':*s;
    *p='\0';
    return sscanf(str,"%lf",&value)==1?value:0.0;
}

/*---deg to rad ------------------------------------------
* args   : double  deg  ddmm.mmmm
*
* return : double  rad
*
* note   :
*----------------------------------------------------------------*/
double deg2rad(const double deg){
    double tmp = deg;
    double rad = floor(tmp/100);
    tmp = tmp - rad*100;
    rad += tmp/60;
    rad *= PI/180;
    return rad;
}

/*---获取一句中的分隔符个数------------------------------------------
* args   : char*       buf      I   解析字符串
*          int*        index    O   序号
*
* return : 分隔个数
*
* note   :
*----------------------------------------------------------------*/
int splitNumPos(const char* buf,int* index,const char splitChar){
    int cx = 0;
    int cy = 0;
    while(1)
    {
//        if(*buf<' '||*buf>'z' || *buf == '\n') break;//遇到'*'或者非法字符，退出
        if(*buf == '\n') break;
        if(*buf == splitChar ){
            index[cx] = cy;
            cx++;
        }
        buf++;
        cy++;
    }
    return cx;
}

/*---删除结束时空格，换行，以及制表符------------------------------------------
* args   : char*       buf      I   解析字符串
*
* return : 最后有效字符位置
*
* note   :
*----------------------------------------------------------------*/
int strim(char *s){
    int n;
     for(n = strlen(s)-1; n >= 0; n--)
      {
         if( ' ' != s[n] && '\t' != s[n] && '\n' != s[n])
            break;
      }
     s[n+1] = '\0';
     return n;
}
/* --------------------------------------
 *
 * args   : char*   path        I    文件路径
 *          char*   strBack     I    文件包含的标识字符串
 *          char**  fileList    O    文件列表
 *
 * return : int 文件数目
 *
 * note   :
*---------------------------------------------*/
int filesearch(const char *path, const char *strBack, char fileList[100][256]){
    struct _finddata_t filefind;
    char* curr = (char*)"\\*.*";
    char final[1024];
    strcpy(final,path);
    strcat(final,curr);
    int done = 0, i = 0, handle;

    if((handle = _findfirst(final, &filefind)) != -1)
    {
        while(!(done = _findnext(handle, &filefind)))
        {
            if(strcmp(filefind.name, "..") == 0)
                continue;
            if((_A_SUBDIR != filefind.attrib))
            {
                if( strstr(filefind.name, strBack) )
                {
                    strcpy(fileList[i],filefind.name);
                    i++;
                }
            }
        }
        _findclose(handle);
    }
    return i;
}

/* --------------------------------------
 *
 * args   : char*       buff        I     配置文件中的一行
 *
 * return : 后半段参数
 *
 * note   :
*---------------------------------------------*/
char* decodeIni(const char *buff){
    int index;
    char data[256] = "\0";
//    if(splitNumPos(buff,&index,' ')){
//        strcpy(data,buff+index);
//    }
    if(splitNumPos(buff,&index,',')){
        strcpy(data,buff+index+1);
    }
//    if(splitNumPos(buff,&index,';')){
//        strcpy(data,buff+index);
//    }
//    if(splitNumPos(buff,&index,'\t')){
//        strcpy(data,buff+index);
//    }
//    if(splitNumPos(buff,&index,':')){
//        strcpy(data,buff+index);
//    }
    strim(data);
    return data;
}
/* --------------------------------------
 *
 * args   : char*        DirIn        I    文件路径
 *          char*        fileName     I    文件包含的标识字符串
 *          process_opt  opt          O    配置
 *
 * return : 0 - fail  1 - successed
 *
 * note   :
*---------------------------------------------*/
int readIni(const char *DirIn, const char *fileName, process_opt *opt){
    char final[256] = "\0";
    FILE *fpIn;
    strcat(final,DirIn);
    strcat(final,fileName);

    if (!(fpIn=fopen(final,"r")))
        return 0;

    char buff[MAXLEN];
    while (fgets(buff,MAXLEN,fpIn)) {
        /*GNSS opt*/
        if (strstr(buff,"GNSSflag")) {
            opt->GNSSOPT.GNSSFlag = str2num(decodeIni(buff),0,1);
            continue;
        }
        if (strstr(buff,"GNSSdir")){
            strcpy(opt->GNSSOPT.dirGNSSNema, decodeIni(buff));
            continue;
        }
        if (strstr(buff,"GNSSlastLabel")){
            strcpy(opt->GNSSOPT.lastLabel , decodeIni(buff));
            continue;
        }
        if (strstr(buff,"GNSSExtension")){
            strcpy(opt->GNSSOPT.strBack , decodeIni(buff));
            continue;
        }

        /*Hex opt*/
        if (strstr(buff,"Hexflag")){
            opt->HEXOPT.HEXFlag = str2num(decodeIni(buff),0,1);
            continue;
        }
        if (strstr(buff,"Hexdir")){
            strcpy(opt->HEXOPT.dirHEX , decodeIni(buff));
            continue;
        }
        if (strstr(buff,"HexExtension")){
            strcpy(opt->HEXOPT.strBack , decodeIni(buff));
            continue;
        }

        /*A08 opt*/
        if (strstr(buff,"A08flag")){
            opt->A0838OPT.A08Flag = str2num(decodeIni(buff),0,1);
            continue;
        }
        if (strstr(buff,"A08dir")){
            strcpy(opt->A0838OPT.dirA08 , decodeIni(buff));
            continue;
        }
        if (strstr(buff,"A08Extension")){
            strcpy(opt->A0838OPT.strBack , decodeIni(buff));
            continue;
        }

    }
    fclose(fpIn);
    return 1;

}

/* ------根据配置进行文件读取-----------------
 *
 * args   :  process_opt  *opt          O    配置
 *
 * return :  0 - fail  1 - successed
 *
 * note   :
*---------------------------------------------*/
int parseOutData(const process_opt *opt){
    char fileList[100][256];
    int fileNum=0,Count = 0;

    //GNSS parse
    if(opt->GNSSOPT.GNSSFlag){
        if(Count = fileNum=filesearch((char*)opt->GNSSOPT.dirGNSSNema,(char*)opt->GNSSOPT.strBack,fileList)){
            while (Count){
                decodeOutNEMA0183(opt->GNSSOPT.dirGNSSNema,fileList[fileNum - Count],opt->GNSSOPT.lastLabel);
                Count--;
            }
            printf("GNSS file parse!\n");

        }else{
            printf("GNSS file not found!\n");
        }
    }else{
        printf("No GNSS mission!\n");
    }
    //Hex parse
    if(opt->HEXOPT.HEXFlag){
        if(Count = fileNum=filesearch((char*)opt->HEXOPT.dirHEX,(char*)opt->HEXOPT.strBack,fileList)){
            while (Count){
                decodeOutIPOS3Data76(opt->HEXOPT.dirHEX,fileList[fileNum - Count]);
                Count--;
            }
            printf("Hex file parse!\n");

        }else{
            printf("Hex file not found!\n");
        }
    }else{
        printf("No Hex mission!\n");
    }
    //A08 38S parse
    if(opt->A0838OPT.A08Flag){
        if(Count = fileNum=filesearch((char*)opt->A0838OPT.dirA08,(char*)opt->A0838OPT.strBack,fileList)){
            while (Count){
                parseOutA08Data(opt->A0838OPT.dirA08,fileList[fileNum - Count]);
                Count--;
            }
            printf("A08 parse!\n");

        }else{
            printf("A08 file not found!\n");
        }
    }else{
        printf("No A08 mission!\n");
    }

    return 1;
}


