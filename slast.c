#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void showtime(long time){
    char  *cp;
    cp = ctime(&time);
    printf("%12.12s", cp+4);
}

int show_info(struct utmp *wtbufp){
    if(wtbufp->ut_type == BOOT_TIME || wtbufp->ut_type == USER_PROCESS){
        printf("%s ", wtbufp->ut_user);
        if(!strcmp(wtbufp->ut_line, "~")){
            printf("system boot ");
        }
        else{
            printf("%s ", wtbufp->ut_line);
        }
        printf("%s ", wtbufp->ut_host);
        showtime((long)wtbufp->ut_tv.tv_sec);
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
        exit(1);
    }
    if(argc == 1){
        while(fseek(fp, -2 * reclen, SEEK_CUR) != -1){
            fread(&current_record, reclen, 1, fp);
            show_info(&current_record);
        }
    }
    else{
        int i = atoi(argv[1]);
        while(fseek(fp, -2 * reclen, SEEK_CUR) != -1 && i > 0){
            fread(&current_record, reclen, 1, fp);
            if(show_info(&current_record)){
                i--;
            }
        }
    }    

    fclose(fp);
    return 0;
}