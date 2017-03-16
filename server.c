#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5060;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;
	int i;
	while(*shm!='*')
	{
		
		char a[15];
		printf("write something or * to end\n");
		gets(a);
		if(a[0]!='*'){
			s=++shm;
			for (i=0;i<strlen(a);i++)
				 *s++ = a[i];
			*s = NULL;
			*shm = '@';
			while(*shm!='#')
			{	
				printf(".");
				sleep(1);
			}
			printf("client:");
			for (s = ++shm; *s != NULL; s++)
		    	putchar(*s);
			putchar('\n');
		}
		else
			*shm = '*';
	}


    exit(0);
}
