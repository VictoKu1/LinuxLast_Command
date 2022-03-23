#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void showtime(long time){
    char  *cp;
    cp = ctime(&time);
    printf("%12.12s", cp+4);
}

void show_info(struct utmp *wtbufp){
    if(wtbufp->ut_type == BOOT_TIME || wtbufp->ut_type == USER_PROCESS){
        printf("user: %s ", wtbufp->ut_user);
        printf("host: %s ", wtbufp->ut_host);
        printf("exit: %d ", wtbufp->ut_exit.e_termination);
        // switch (wtbufp->ut_type)
        // {
        // case BOOT_TIME:
        //     printf("system boot");
        //     break;
        
        // default:
        //     printf("line: %s", wtbufp->ut_line);
        //     break;
        // }
        printf("add_v6: %ls ", wtbufp->ut_addr_v6);
        printf("line: %s ", wtbufp->ut_line);
        printf("id: %s ", wtbufp->ut_id);
        printf("pid: %d ", wtbufp->ut_pid);
        printf("session: %d ", wtbufp->ut_session);
        printf("type: %d ", wtbufp->ut_type);
        // printf("%d ", wtbufp->ut_tv.tv_sec);
        showtime((long)wtbufp->ut_tv.tv_sec);
        printf("\n");
    }
    
}


int main(int argc, char const *argv[])
{
    struct utmp current_record;
    int wtmpfd, utmpfd;
    int reclen = sizeof(current_record);

    if((wtmpfd = open(WTMP_FILE, O_RDONLY)) == -1){
        perror(WTMP_FILE);
        exit(1);
    }
    while (read(wtmpfd, &current_record,reclen) == reclen)
    {
        show_info(&current_record);
    }
    close(wtmpfd);
    return 0;
}