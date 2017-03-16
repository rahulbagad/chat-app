#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSZ     27

main()
{
    int shmid,i;
    key_t key;
    char *shm, *s;
    key = 1000;
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
	*shm = '!';
	while(*shm!='*')
	{		
		char a[100];
		printf("mesaage to send (*to end):");
		gets(a);
		if(a[0]!='*'){
			s = shm+1;
			for (i=0;i<strlen(a);i++)
				 *s++ = a[i];
			*s = NULL;
			*shm = '@';

			while(*shm!='#'&&*shm!='*')
				sleep(1);

			if(*shm!='*'){
				printf("client:");
				for (s = shm+1; *s != NULL; s++)
					putchar(*s);
				putchar('\n');
			}else
			printf("connection closed by client");
		}
		else
			*shm = '*';
	}
	shmid = shmdt(shm);

    exit(0);
}
