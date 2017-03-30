#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MSGSZ     128

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;

main()
{
    int msqid,sid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    message_buf rbuf;
    size_t buf_length;

    key = 1234;


    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }

    
    while(1)
    {
        char a[128];
        
        printf("student_id: ");
        scanf("%d",&sid);
        printf("@student%d: ",sid);
        sbuf.mtype = sid;
        gets(a);       
     
        (void) strcpy(sbuf.mtext,a);

        
        buf_length = strlen(sbuf.mtext) + 1 ;
        

        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
           printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
            perror("msgsnd");
            exit(1);
        }

        if (msgrcv(msqid, &rbuf, MSGSZ, 2, 0) < 0) {
            perror("msgrcv");
            exit(1);
        }
        printf("client: %s\n", rbuf.mtext);

    }  
    exit(0);
}
