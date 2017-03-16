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
    key = 1000; //key for data segment created by server, must be same as that of server
   
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {	//locate data segment using key and get its id
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
		while(*shm!='@'&&*shm!='*')
			sleep(1);
		if(*shm!='*'){
			printf("server:");
			for (s = shm+1; *s != NULL; s++)
		    	putchar(*s);
			putchar('\n');

			char a[100];
			printf("message to send (* to end):");
			gets(a);
			if(a[0]!='*'){
				s=shm+1;
				for (i=0;i<strlen(a);i++)
					 *s++ = a[i];
				*s = NULL;
				*shm = '#';
			}
			else
				*shm = '*';
		}
		else
			printf("connection closed by server");
	}

    shmid = shmdt(shm);

    exit(0);
}
