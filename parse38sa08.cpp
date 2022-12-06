#include "parse38sa08.h"
/* 提取A08一行数据 ------------------------------------------------------
* args   : char*     buff        I    数据行
*          A08Data_t A08Data     IO   数据
*
* return : 0-NONE，1-success
*
* note   :  20   21~23    24~26    33-34-32    43~45    146-148   149-151   157~1
*          time  POSpos   Vnpos     Attpos    AttDiff    POSRef   VnRef     Attpos
*-----------------------------------------------------------------*/
int parseA08Data(const char *buff, A08Data_t *A08Data){
    int index[MAXSPLITCHAR];
//    printf("%s\n",buff);

    if(splitNumPos(buff,index,'\t')){
        A08Data->time       = str2num(buff,index[18]+1,index[19]);

        A08Data->PosPos[0]  = str2num(buff,index[19]+1,index[20]);
        A08Data->PosPos[1]  = str2num(buff,index[20]+1,index[21]);
        A08Data->PosPos[2]  = str2num(buff,index[21]+1,index[22]);

        A08Data->VnPos [0]  = str2num(buff,index[22]+1,index[23]);
        A08Data->VnPos [1]  = str2num(buff,index[23]+1,index[24]);
        A08Data->VnPos [2]  = str2num(buff,index[24]+1,index[25]);

        A08Data->AttPos[2]  = str2num(buff,index[30]+1,index[31]);
        A08Data->AttPos[0]  = str2num(buff,index[31]+1,index[32]);
        A08Data->AttPos[1]  = str2num(buff,index[32]+1,index[33]);

        A08Data->AttDiff [0]  = str2num(buff,index[61]+1,index[62]);
        A08Data->AttDiff [1]  = str2num(buff,index[62]+1,index[63]);
        A08Data->AttDiff [2]  = str2num(buff,index[63]+1,index[64]);

        A08Data->PosRef[0]  = str2num(buff,index[144]+1,index[145]);
        A08Data->PosRef[1]  = str2num(buff,index[145]+1,index[146]);
        A08Data->PosRef[2]  = str2num(buff,index[146]+1,index[127]);

        A08Data->VnRef [0]  = str2num(buff,index[147]+1,index[148]);
        A08Data->VnRef [1]  = str2num(buff,index[148]+1,index[149]);
        A08Data->VnRef [2]  = str2num(buff,index[149]+1,index[150]);

        A08Data->AttRef[2]  = str2num(buff,index[155]+1,index[156]);
        A08Data->AttRef[0]  = str2num(buff,index[156]+1,index[157]);
        A08Data->AttRef[1]  = str2num(buff,index[157]+1,index[158]);
    }else{
        return 0;
    }
    if (A08Data->time<100) return 0;
    return 1;
}

/* 提取A08数据 ------------------------------------------------------
* args   : char*    DirIn       I    文件路径
*          char*    fileName    I    输入文件文件名
*          NEMA0183 data        IO   数据
*
* return : 0-NONE，-2-error
*
* note   :
*-----------------------------------------------------------------*/
int parseOutA08Data(const char* DirIn, const char* fileName){
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
    char buff[MAXLENLEN];
    A08Data_t A08Data = {0};

    while (fgets(buff,MAXLENLEN,fpIn)) {
        if(parseA08Data(buff,&A08Data)){
            fprintf(fpOut,"%15.12f %15.12f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f ",
                    A08Data.PosRef[0],A08Data.PosRef[1],A08Data.PosRef[2],
                    A08Data.VnRef[0] ,A08Data.VnRef[1] ,A08Data.VnRef[2],
                    A08Data.AttRef[0] ,A08Data.AttRef[1] ,A08Data.AttRef[2]);

            fprintf(fpOut,"%15.12f %15.12f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f ",
                    A08Data.PosPos[0],A08Data.PosPos[1],A08Data.PosPos[2],
                    A08Data.VnPos[0] ,A08Data.VnPos[1] ,A08Data.VnPos[2],
                    A08Data.AttPos[0] ,A08Data.AttPos[1] ,A08Data.AttPos[2]);

            fprintf(fpOut,"%6.3f %6.3f %6.3f %6.3f\n",
                    A08Data.AttDiff[0],A08Data.AttDiff[1],A08Data.AttDiff[2],
                    A08Data.time);
        }
    }
    fclose(fpIn);
    fclose(fpOut);
    return 1;
}

