#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#define MSGSZ     128


/*
* Declare the message structure.
*/

typedef struct msgbuf {
	long    mtype;
	char    mtext[MSGSZ];
} message_buf;

main()
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf,rbuf;
	size_t buf_length;
	key = 1234;

	if ((msqid = msgget(key, msgflg )) < 0) {
		perror("msgget");
		exit(1);
	}
	
	while(1){
		
		sbuf.mtype = 1;
		printf("\nEnter Message '***' to close connection:");
		gets(&sbuf.mtext);
		
		if(strcmp(sbuf.mtext,"***")==0){
			strcpy(sbuf.mtext,"\nConnection closed by Other User");
			buf_length = strlen(sbuf.mtext) + 1 ;
			if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
				printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
				perror("msgsnd");
				exit(1);
			}
			printf("\nClosing Connection");
			break;
		}
		
		
		
		buf_length = strlen(sbuf.mtext) + 1 ;
		if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
			printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
			perror("msgsnd");
			exit(1);
		}else 
			printf("\nProcess 1:%s", sbuf.mtext);
	
		if (msgrcv(msqid, &rbuf, MSGSZ, 2, 0) < 0) {
			perror("msgrcv");
			exit(1);
		}else
			printf("\nProcess 2:%s", rbuf.mtext);
	}
	
	

	exit(0);
}
