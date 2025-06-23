/**
 * @file slast.c
 * @brief A simplified implementation of the 'last' command for Linux
 * 
 * This program reads the wtmp file and displays login/logout records.
 * It can optionally limit the number of records displayed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    /* Windows compatibility */
    #include <io.h>
    #include <fcntl.h>
    #define SEEK_SET 0
    #define SEEK_END 2
    #define SEEK_CUR 1
    
    /* Define utmp structure for Windows */
    #define UT_LINESIZE 32
    #define UT_NAMESIZE 32
    #define UT_HOSTSIZE 256
    
    struct utmp {
        char ut_user[UT_NAMESIZE];
        char ut_id[4];
        char ut_line[UT_LINESIZE];
        char ut_host[UT_HOSTSIZE];
        long ut_tv[2];  /* tv_sec, tv_usec */
        int ut_type;
        int ut_pid;
        char ut_session;
        char ut_pad[5];
    };
    
    /* Define utmp types */
    #define BOOT_TIME 2
    #define USER_PROCESS 7
#else
    /* Linux includes */
    #include <utmp.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

#define WTMP_FILE "/var/log/wtmp"

void showtime(long time){
    char  *cp;
    cp = ctime(&time);
    if (cp) {
        printf("%12.12s", cp+4);
    }
}

int show_info(const struct utmp *wtbufp){
    if(wtbufp->ut_type == BOOT_TIME || wtbufp->ut_type == USER_PROCESS){
        printf("%s ", wtbufp->ut_user);
        if(!strcmp(wtbufp->ut_line, "~")){
            printf("system boot ");
        }
        else{
            printf("%s ", wtbufp->ut_line);
        }
        printf("%s ", wtbufp->ut_host);
        showtime((long)wtbufp->ut_tv[0]);  /* Use array index for Windows compatibility */
        printf("\n");
        return 1;
    }
    return 0;
}


int main(int argc, char const *argv[])
{
    struct utmp current_record;
    int reclen = sizeof(current_record);

    FILE* fp;
    if((fp = fopen(WTMP_FILE, "r")) == NULL){
        perror(WTMP_FILE);
        exit(1);
    }
    if(fseek(fp, reclen, SEEK_END) == -1){
        fclose(fp);
        exit(1);
    }
    if(argc == 1){
        while(fseek(fp, -2 * reclen, SEEK_CUR) != -1){
            if(fread(&current_record, reclen, 1, fp) == 1){
                show_info(&current_record);
            }
        }
    }
    else{
        int i = atoi(argv[1]);
        if(i <= 0){
            fprintf(stderr, "Invalid number: %s\n", argv[1]);
            fclose(fp);
            exit(1);
        }
        while(fseek(fp, -2 * reclen, SEEK_CUR) != -1 && i > 0){
            if(fread(&current_record, reclen, 1, fp) == 1){
                if(show_info(&current_record)){
                    i--;
                }
            }
        }
    }    

    fclose(fp);
    return 0;
}