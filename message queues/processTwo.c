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
	key_t key;
	message_buf  rbuf,sbuf;
	size_t buf_length;
	/*
	* Get the message queue id for the
	* "name" 1234, which was created by
	* the server.
	*/
	key = 1234;

	if ((msqid = msgget(key, 0666)) < 0) {
		perror("msgget");
		exit(1);
	}


	while(1){
		
		if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
			perror("msgrcv");
			exit(1);
		}else
			printf("\nProcess 1:%s", rbuf.mtext);
		
		
		
		sbuf.mtype = 2;
		printf("\nEnter Message '***' to close connection:");
		gets(&sbuf.mtext);
		if(strcmp(sbuf.mtext,"***")==0){
			strcpy(sbuf.mtext,"Connection closed by Other Process");
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
			printf("Process 2:%s", sbuf.mtext);
	

	}
	
	exit(0);
}
