#include "./fuctioncmn.h"

void printHelp(){
    printf("this is prase exe, the paras just for reading ini file.\n");
    printf("if no para, read the root config.ini file.\n");
    printf("if one para, set the fileName, the dir was root.\n");
    printf("if two para, set the dir and fileName. \n");
    printf("if others, printf the help. \n");
}

int main(int argc, char *argv[])
{
    process_opt opt = {{0}};
//    char fileName[1024] ;
//    int ptr = 0;

//    strcpy(fileName,argv[0]);

//    switch (argc){
//    case 1:
//        ptr = strrchr(fileName,'\\') - fileName;
//        strcpy(&fileName[ptr],"\\config.ini");
//        break;
//    case 2:
//        ptr = strrchr(fileName,'\\') - fileName;
//        char Name[256];
//        sprintf(Name,"%s%s","\\",argv[1]);
//        strcpy(&fileName[ptr],Name);
//        break;
//    case 3:
//        sprintf(fileName,"%s%s%s",argv[1],"\\",argv[2]);
//        break;
//    default:
//        printHelp();
//        break;
//    }

    char *fileName = "B://02_CodeC//09_QTcode//build-Process//debug//config.ini";
    if(!readIni("",fileName,&opt)) {
        printf("there is no ini file!\n");
        return 0;
    }
    return parseOutData(&opt);
}
