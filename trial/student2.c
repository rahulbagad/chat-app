#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define MSGSZ     128

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


main()
{
    int msqid;
    key_t key;
    message_buf  rbuf;
    message_buf  sbuf;
    size_t buf_length;

    key = 1234;

    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    sbuf.mtype = 4;
    char a[128];
    while(1)
    {
    
	    if (msgrcv(msqid, &rbuf, MSGSZ, 2, 0) < 0) {
	        perror("msgrcv");
	        exit(1);
	    }

    	printf("server: %s\n", rbuf.mtext);

        printf("@client: ");
        gets(a);
        (void) strcpy(sbuf.mtext,a);

        
        buf_length = strlen(sbuf.mtext) + 1 ;

        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
            printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
            perror("msgsnd");
            exit(1);
        }
    }
    exit(0);
}