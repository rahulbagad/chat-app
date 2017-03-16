#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
{
    int shmid;
    key_t key;
    char *shm, *s;
    key = 5060; //key for data segment created by server, must be same as that of server
	
    //locate data segment using key and get its id
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget"); 
        exit(1);
    }


    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */
    s = shm;
	int i;
	while(*shm!='*')
	{
		while(*shm!='@')
			sleep(1);
			
		printf("server:");
		for (s = ++shm; *s != NULL; s++)
        	putchar(*s);
    	putchar('\n');
	
	
		char a[15];
		printf("write something or * to end\n");
		gets(a);
		if(a[0]!='*'){
			s=++shm;
			for (i=0;i<strlen(a);i++)
				 *s++ = a[i];
			*s = NULL;
			*shm = '#';
		}
		else
			*shm = '*';
	}

    

    exit(0);
}
