#include "parsehex.h"

/* * IPOS3数据比例系数 -----------------------
*
* args   : IPOS3FrameData_t *frameData   I  IPOS3串口数据
*          IPOS3Data_t      *data        O  IPOS3解析数据
*
* return : NONE
*
* note   : 比例系数转换
*
*-------------------------------------------*/
void IPOS3Process58(const IPOS3FrameData58_t *frameData,IPOS3Data58_t* data){
    data->Att[0] = (*(short*)(frameData->data.Att[0]))*(360.0/32768.0)/180*PI;
    data->Att[1] = (*(short*)(frameData->data.Att[1]))*(360.0/32768.0)/180*PI;
    data->Att[2] = (*(short*)(frameData->data.Att[2]))*(360.0/32768.0)/180*PI;

    data->Gyr[0] = (*(short*)(frameData->data.Gyr[0]))*(360.0/32768.0);
    data->Gyr[1] = (*(short*)(frameData->data.Gyr[1]))*(360.0/32768.0);
    data->Gyr[2] = (*(short*)(frameData->data.Gyr[2]))*(360.0/32768.0);

    data->Acc[0] = (*(short*)(frameData->data.Acc[0]))*(12.0/32768.0);
    data->Acc[1] = (*(short*)(frameData->data.Acc[0]))*(12.0/32768.0);
    data->Acc[2] = (*(short*)(frameData->data.Acc[0]))*(12.0/32768.0);

    data->Pos[0] = (*(int*)(frameData->data.Pos[0]))/1e7/180*PI;
    data->Pos[1] = (*(int*)(frameData->data.Pos[1]))/1e7/180*PI;
    data->Pos[2] = (*(int*)(frameData->data.Pos[2]))/1e3;

    data->Vel[0] = (*(short*)(frameData->data.Vel[0]))*(100.0/32768.0);
    data->Vel[1] = (*(short*)(frameData->data.Vel[1]))*(100.0/32768.0);
    data->Vel[2] = (*(short*)(frameData->data.Vel[2]))*(100.0/32768.0);

    data->Flag    = frameData->data.Flag;
    data->Week    = (*(unsigned short*)(frameData->data.Week));
    data->StaNum  = frameData->data.StaNum;
    data->RTKTime = frameData->data.RTKTime;
    data->ODVel   = (*(short*)(frameData->data.ODVel))/100.0f;
    data->UtcSec  = (*(unsigned int*)(frameData->data.UtcSec))/4e3;
    data->DataType= frameData->data.DataType;


    switch (frameData->data.DataType){
    case 0:
    case 1:
    case 2:
        data->Data[0] = exp((*(short*)frameData->data.Data[0])/100.0f);
        data->Data[1] = exp((*(short*)frameData->data.Data[1])/100.0f);
        data->Data[2] = exp((*(short*)frameData->data.Data[2])/100.0f);

        break;
    case 22:

        break;
    case 23:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1])*1e-4;
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    case 34:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1]);
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    case 35:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1]);
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    default:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1]);
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    }
}

/* * IPOS3数据比例系数 -----------------------
*
* args   : IPOS3FrameData_t *frameData   I  IPOS3串口数据
*          IPOS3Data_t      *data        O  IPOS3解析数据
*
* return : NONE
*
* note   : 比例系数转换
*
*-------------------------------------------*/
void IPOS3Process76(const IPOS3FrameData76_t *frameData,IPOS3Data76_t* data){
    data->Att[0] = (*(short*)(frameData->data.Att[0]))*(360.0/32768.0)/180*PI;
    data->Att[1] = (*(short*)(frameData->data.Att[1]))*(360.0/32768.0)/180*PI;
    data->Att[2] = (*(short*)(frameData->data.Att[2]))*(360.0/32768.0)/180*PI;

    data->Gyr[0] = (*(short*)(frameData->data.Gyr[0]))*(360.0/32768.0);
    data->Gyr[1] = (*(short*)(frameData->data.Gyr[1]))*(360.0/32768.0);
    data->Gyr[2] = (*(short*)(frameData->data.Gyr[2]))*(360.0/32768.0);

    data->Acc[0] = (*(short*)(frameData->data.Acc[0]))*(12.0/32768.0);
    data->Acc[1] = (*(short*)(frameData->data.Acc[0]))*(12.0/32768.0);
    data->Acc[2] = (*(short*)(frameData->data.Acc[0]))*(12.0/32768.0);

    data->Pos[0] = (*(int*)(frameData->data.Pos[0]))/1e7/180*PI;
    data->Pos[1] = (*(int*)(frameData->data.Pos[1]))/1e7/180*PI;
    data->Pos[2] = (*(int*)(frameData->data.Pos[2]))/1e3;

    data->Vel[0] = (*(short*)(frameData->data.Vel[0]))*(100.0/32768.0);
    data->Vel[1] = (*(short*)(frameData->data.Vel[1]))*(100.0/32768.0);
    data->Vel[2] = (*(short*)(frameData->data.Vel[2]))*(100.0/32768.0);

    data->Flag    = frameData->data.Flag;
    data->Week    = (*(unsigned short*)(frameData->data.Week));
    data->StaNum  = frameData->data.StaNum;
    data->RTKTime = frameData->data.RTKTime;
    data->ODVel   = (*(short*)(frameData->data.ODVel))/100.0f;
    data->UtcSec  = (*(unsigned int*)(frameData->data.UtcSec))/4e3;
    data->DataType= frameData->data.DataType;

    switch (frameData->data.DataType){
    case 0:
        data->stdATT[0] = exp((*(short*)frameData->data.Data[0])/100.0f);
        data->stdATT[1] = exp((*(short*)frameData->data.Data[1])/100.0f);
        data->stdATT[2] = exp((*(short*)frameData->data.Data[2])/100.0f);
        data->twistCov[6*3+3] = data->stdATT[0];
        data->twistCov[6*4+4] = data->stdATT[1];
        data->twistCov[6*5+5] = data->stdATT[2];

        data->Data[0] = data->stdATT[0];
        data->Data[1] = data->stdATT[1];
        data->Data[2] = data->stdATT[2];
        break;
    case 1:
        data->stdVEL[0] = exp((*(short*)frameData->data.Data[0])/100.0f);
        data->stdVEL[1] = exp((*(short*)frameData->data.Data[1])/100.0f);
        data->stdVEL[2] = exp((*(short*)frameData->data.Data[2])/100.0f);
        data->twistCov[6*0+0] = data->stdVEL[0];
        data->twistCov[6*1+1] = data->stdVEL[1];
        data->twistCov[6*2+2] = data->stdVEL[2];

        data->Data[0] = data->stdVEL[0];
        data->Data[1] = data->stdVEL[1];
        data->Data[2] = data->stdVEL[2];
        break;
    case 2:
        data->stdPOS[0] = exp((*(short*)frameData->data.Data[0])/100.0f);
        data->stdPOS[1] = exp((*(short*)frameData->data.Data[1])/100.0f);
        data->stdPOS[2] = exp((*(short*)frameData->data.Data[2])/100.0f);
        data->twistCov[3*0+0] = data->stdPOS[0];
        data->twistCov[3*1+1] = data->stdPOS[1];
        data->twistCov[3*2+2] = data->stdPOS[2];

        data->Data[0] = data->stdPOS[0];
        data->Data[1] = data->stdPOS[1];
        data->Data[2] = data->stdPOS[2];
        break;
    case 22:

        break;
    case 23:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1])*1e-4;
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    case 34:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1]);
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    case 35:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1]);
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    default:
        data->Data[0] = (*(short*)frameData->data.Data[0]);
        data->Data[1] = (*(short*)frameData->data.Data[1]);
        data->Data[2] = (*(short*)frameData->data.Data[2]);
        break;
    }

    data->Gyr0[0] = (*(short*)(frameData->data.Gyr0[0]))*(360.0/32768.0);
    data->Gyr0[1] = (*(short*)(frameData->data.Gyr0[1]))*(360.0/32768.0);
    data->Gyr0[2] = (*(short*)(frameData->data.Gyr0[2]))*(360.0/32768.0);

    data->Acc0[0] = (*(short*)(frameData->data.Acc0[0]))*(12.0/32768.0);
    data->Acc0[1] = (*(short*)(frameData->data.Acc0[0]))*(12.0/32768.0);
    data->Acc0[2] = (*(short*)(frameData->data.Acc0[0]))*(12.0/32768.0);

    char tmp = frameData->data.DataType0;
    int DataType0 = 0;
    data->GNSSFlag   = (tmp & 0x0F);
    DataType0        = (tmp & 0xF0)/16;

    data->DataType0  =  DataType0;
    switch (DataType0){
    case 0:
        data->POSGNSS[0] = (*(int*)frameData->data.Data0)*1e-7;
        data->Data[3] = data->POSGNSS[0];
        break;
    case 1:
        data->POSGNSS[1] = (*(int*)frameData->data.Data0)*1e-7;
        data->Data[3] = data->POSGNSS[1];
        break;
    case 2:
        data->POSGNSS[2] = (*(int*)frameData->data.Data0)*1e-3;
        data->Data[3] = data->POSGNSS[2];
        break;
    case 3:
        data->VELGNSS[0] = (*(float*)frameData->data.Data0);
        data->Data[3] = data->VELGNSS[0];
        break;
    case 4:
        data->VELGNSS[1] = (*(float*)frameData->data.Data0);
        data->Data[3] = data->VELGNSS[1];
        break;
    case 5:
        data->VELGNSS[2] = (*(float*)frameData->data.Data0);
        data->Data[3] = data->VELGNSS[2];
        break;
    case 6:
        data->stdPOSGNSS[0] = (*(float*)frameData->data.Data0);
        data->Data[3] = data->stdPOSGNSS[0];
        break;
    case 7:
        data->stdPOSGNSS[1] = (*(float*)frameData->data.Data0);
        data->Data[3] = data->stdPOSGNSS[1];
        break;
    case 8:
        data->stdPOSGNSS[2] = (*(float*)frameData->data.Data0);
        data->Data[3] = data->stdPOSGNSS[2];
        break;
    case 9:
        data->yawGNSS = (*(float*)frameData->data.Data0);
        data->Data[3] = data->yawGNSS;
        break;
    case 10:
        data->hoop = (*(float*)frameData->data.Data0);
        data->Data[3] = data->hoop;
        break;
    case 11:
        data->yawRMS = (*(float*)frameData->data.Data0);
        data->Data[3] = data->yawRMS;
        break;
    default:

        break;
    }

}
/* 解析0183数据 ------------------------------------------------------
* args   : IPOS3Data   IPOS3Data_      IO   所有数据
*          IPOS3Data_t data            I    单个数据
*
* return : 0-NONE，-1-error，1-success
*
* note   : 结构体累加
*-----------------------------------------------------------------------------*/
static int addIPOS3Data(IPOS3Data *IPOS3Data_,const IPOS3Data58_t* data){
    IPOS3Data58_t *dataNew;
    if (IPOS3Data_->n >= IPOS3Data_->nmax){
        IPOS3Data_->nmax += 1024;
        if (!(dataNew = (IPOS3Data58_t*)realloc(IPOS3Data_->data,sizeof(IPOS3Data58_t)*IPOS3Data_->nmax) )){
            free(IPOS3Data_->data);IPOS3Data_->data = NULL;IPOS3Data_->n = IPOS3Data_->nmax = 0;
            return 0;
        }
        IPOS3Data_->data = dataNew;
    }
    IPOS3Data_->data[IPOS3Data_->n++] = *data;
    return 1;
}
/* 解析0183数据 ------------------------------------------------------
* args   : char*     Dir
*          char*     fileName     I    输入文件文件名
*          IPOS3Data *IPOS3Data_  IO   数据
*          char*     lastLabel    I    文件名后缀
*
* return : 0-NONE，-2-error
*
* note   :
*-----------------------------------------------------------------------------*/
int decodeIPOS3Data(const char *DirIn, const char *fileNameIn, IPOS3Data *IPOS3Data_){
    if (!fileNameIn) return 0;
    char fileName[256] = "\0" ;
    sprintf(fileName,"%s%s",DirIn,fileNameIn);
    FILE *fp;
    if (!(fp=fopen(fileName,"rb")))
        return 0;

    char buff[IPOS3LENGTH58] ;
    IPOS3FrameData58_t IPOS3FrameData_={0};
    IPOS3Data58_t      IPOS3Datat_    ={0};

    long buffBias = 0;long i = 0;
    fseek(fp,0,SEEK_END);
    long totalSize = ftell(fp);
    fseek(fp,buffBias,SEEK_SET);
    while( ftell(fp) < totalSize ){
        fread(buff, sizeof(IPOS3FrameData_), 1, fp);
        if((char)0xBD == buff[0] && (char)0xDB == buff[1] && (char)0x0B == buff[2]){
            memcpy(&IPOS3FrameData_,&buff,IPOS3LENGTH58);
            buffBias+=IPOS3LENGTH58;
            IPOS3Process58(&IPOS3FrameData_,&IPOS3Datat_);
            if(!addIPOS3Data(IPOS3Data_,&IPOS3Datat_))
                return 0;
        }else
            buffBias+=1;
        fseek(fp,buffBias,SEEK_SET);
    }
    fclose(fp);
    return 1;
}

/* 输出为DAT信息 ------------------------------------------------------
* args   : char*     fileNameOut I    输入文件文件名
*          IPOS3Data *data       I    数据
*
* return : 0-NONE，-1-error
*
* note   :
* */
int outIPOS3Data58(const char *DirOut, const char *fileNameOut, const IPOS3Data *data){
    if (!fileNameOut) return 0;
    char fileName[256] = "\0" ;
    sprintf(fileName,"%s%s",DirOut,fileNameOut);
    FILE *fp;
    if (!(fp=fopen(fileName,"w")))
        return 0;
    for (int j=0;j<data->n;j++){
        //NavInFo
//        data->data[j].Pos[2] /=10000;
//        fprintf(fp,"%6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %11.8f %11.8f %6.3f %4.f %7.3f\n",
//                data->data[j].Att[0],data->data[j].Att[1],data->data[j].Att[2],
//                data->data[j].Vel[0],data->data[j].Vel[1],data->data[j].Vel[2],
//                data->data[j].Pos[0],data->data[j].Pos[1],data->data[j].Pos[2],
//                data->data[j].Week,data->data[j].UtcSec);

        //NavInFo
        fprintf(fp,"%6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %15.12f %15.12f %8.5f ",
                data->data[j].Att[0],data->data[j].Att[1],data->data[j].Att[2],
                data->data[j].Vel[0],data->data[j].Vel[1],data->data[j].Vel[2],
                data->data[j].Pos[0],data->data[j].Pos[1],data->data[j].Pos[2]);
        //IMUInFo
        fprintf(fp,"%11.8f %11.8f %11.8f %11.8f %11.8f %11.8f %11.8f ",
                data->data[j].Acc[0],data->data[j].Acc[1],data->data[j].Acc[2],
                data->data[j].Gyr[0],data->data[j].Gyr[1],data->data[j].Gyr[2],
                data->data[j].ODVel);
        //FlagInFo
        fprintf(fp,"%2.f %2.f %8.3f %8.3f %8.3f %2.f %4.f %7.3f \n",
                data->data[j].Flag,data->data[j].DataType,
                data->data[j].Data[0],data->data[j].Data[1],data->data[j].Data[2],
                data->data[j].StaNum,
                data->data[j].Week,data->data[j].UtcSec);
    }
    fclose(fp);
    return 1;
}

int decodeOutIPOS3Data(const char *DirIn, const char *fileName){
    if (!fileName) return 0;
    char fileNameIn[256] = "\0" ;
    sprintf(fileNameIn,"%s%s",DirIn,fileName);
    FILE *fpIn,*fpOut;
    if (!(fpIn=fopen(fileNameIn,"rb")))
        return 0;

    char* fileNameOut = fileNameIn;
    int ptr = strrchr(fileNameOut,'.') - fileNameOut;
    strcpy(&fileNameOut[ptr],".dat");
    if (!(fpOut=fopen(fileNameOut,"w")))
        return 0;
    char buff[MAXLEN];
    IPOS3Data58_t IPOS3Datat={0};
    IPOS3FrameData58_t IPOS3FrameData_ = {0};

    long buffBias = 0;
    fseek(fpIn,0,SEEK_END);
    long totalSize = ftell(fpIn);
    fseek(fpIn,buffBias,SEEK_SET);
    while( ftell(fpIn) < totalSize ){
        fread(buff, sizeof(IPOS3FrameData_), 1, fpIn);
        if((char)0xBD == buff[0] && (char)0xDB == buff[1] && (char)0x0B == buff[2]){
            memcpy(&IPOS3FrameData_,&buff,IPOS3LENGTH58);
            buffBias+=IPOS3LENGTH58;

            IPOS3Process58(&IPOS3FrameData_,&IPOS3Datat);
            fprintf(fpOut,"%6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %15.12f %15.12f %8.5f ",
                    IPOS3Datat.Att[0],IPOS3Datat.Att[1],IPOS3Datat.Att[2],
                    IPOS3Datat.Vel[0],IPOS3Datat.Vel[1],IPOS3Datat.Vel[2],
                    IPOS3Datat.Pos[0],IPOS3Datat.Pos[1],IPOS3Datat.Pos[2]);
            //IMUInFo
            fprintf(fpOut,"%11.8f %11.8f %11.8f %11.8f %11.8f %11.8f %11.8f ",
                    IPOS3Datat.Acc[0],IPOS3Datat.Acc[1],IPOS3Datat.Acc[2],
                    IPOS3Datat.Gyr[0],IPOS3Datat.Gyr[1],IPOS3Datat.Gyr[2],
                    IPOS3Datat.ODVel);
            //FlagInFo
            fprintf(fpOut,"%2.f %2.f %8.3f %8.3f %8.3f %2.f %4.f %7.3f \n",
                    IPOS3Datat.Flag,IPOS3Datat.DataType,
                    IPOS3Datat.Data[0],IPOS3Datat.Data[1],IPOS3Datat.Data[2],
                    IPOS3Datat.StaNum,
                    IPOS3Datat.Week,IPOS3Datat.UtcSec);
        }else
            buffBias+=1;
        fseek(fpIn,buffBias,SEEK_SET);
    }

    fclose(fpIn);
    fclose(fpOut);
    return 1;
}


int decodeOutIPOS3Data76(const char *DirIn, const char *fileName){
    if (!fileName) return 0;
    char fileNameIn[256] = "\0" ;
    sprintf(fileNameIn,"%s%s",DirIn,fileName);
    FILE *fpIn,*fpOut;
    if (!(fpIn=fopen(fileNameIn,"rb")))
        return 0;

    char* fileNameOut = fileNameIn;
    int ptr = strrchr(fileNameOut,'.') - fileNameOut;
    strcpy(&fileNameOut[ptr],".dat");
    if (!(fpOut=fopen(fileNameOut,"w")))
        return 0;
    char buff[MAXLEN] ;

    IPOS3Data76_t IPOS3Datat={0};
    IPOS3FrameData76_t IPOS3FrameData_ = {0};
    long buffBias = 0;
    fseek(fpIn,0,SEEK_END);
    long totalSize = ftell(fpIn);
    fseek(fpIn,buffBias,SEEK_SET);

    while( ftell(fpIn) < totalSize ){
        fread(buff,sizeof(char),IPOS3LENGTH76, fpIn);
        if((char)0xBD == buff[0] && (char)0xDB == buff[1] && (char)0x0B == buff[2]){
            memcpy(&IPOS3FrameData_,&buff,IPOS3LENGTH76);
            buffBias+=IPOS3LENGTH76;
            IPOS3Process76(&IPOS3FrameData_,&IPOS3Datat);
            fprintf(fpOut,"%6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %15.12f %15.12f %8.5f ",
                    IPOS3Datat.Att[0],IPOS3Datat.Att[1],IPOS3Datat.Att[2],
                    IPOS3Datat.Vel[0],IPOS3Datat.Vel[1],IPOS3Datat.Vel[2],
                    IPOS3Datat.Pos[0],IPOS3Datat.Pos[1],IPOS3Datat.Pos[2]);
            //IMUInFo
            fprintf(fpOut,"%11.8f %11.8f %11.8f %11.8f %11.8f %11.8f %11.8f ",
                    IPOS3Datat.Acc[0],IPOS3Datat.Acc[1],IPOS3Datat.Acc[2],
                    IPOS3Datat.Gyr[0],IPOS3Datat.Gyr[1],IPOS3Datat.Gyr[2],
                    IPOS3Datat.ODVel);
            //FlagInFo
            fprintf(fpOut,"%2.f %2.f %8.3f %8.3f %8.3f %2.f %4.f %7.3f ",
                    IPOS3Datat.Flag,IPOS3Datat.DataType,
                    IPOS3Datat.Data[0],IPOS3Datat.Data[1],IPOS3Datat.Data[2],
                    IPOS3Datat.StaNum,
                    IPOS3Datat.Week,IPOS3Datat.UtcSec);
            //IMU_GNSSInFo
            fprintf(fpOut,"%2.f %2.f %15.12f %11.8f %11.8f %11.8f %11.8f %11.8f %11.8f \n",
                    IPOS3Datat.GNSSFlag,IPOS3Datat.DataType0,
                    IPOS3Datat.Data[3],
                    IPOS3Datat.Acc[0],IPOS3Datat.Acc[1],IPOS3Datat.Acc[2],
                    IPOS3Datat.Gyr[0],IPOS3Datat.Gyr[1],IPOS3Datat.Gyr[2]);
        }else
            buffBias+=1;
        fseek(fpIn,buffBias,SEEK_SET);
    }

    fclose(fpIn);
    fclose(fpOut);
    return 1;
}

