#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

/* Main */
int main()
{
	/* This is Changed Line */
    char path[100];
    struct stat stats;

    printf("Enter source file path: ");
    scanf("%s", path);

    stat(path, &stats);

    struct tm dt;

    /* File Permissions */
    printf("\nFile Access:\n");
    if(stats.st_mode & R_OK)    printf("read ");
    if(stats.st_mode & W_OK)    printf("Write ");
    if(stats.st_mode & X_OK)    printf("Execute ");

    /* File Size */
    printf("\nFile size : %d\n", (int)stats.st_size);

    dt = *(gmtime(&stats.st_ctime));
    printf("\nCreation on: %d-%d-%d %d:%d:%d\n",dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                            dt.tm_hour, dt.tm_min, dt.tm_sec);


    dt = *(gmtime(&stats.st_mtime));
    printf("\nModification on: %d-%d-%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                                            dt.tm_hour, dt.tm_min, dt.tm_sec);
    
    
    int pid = fork();
    if(pid == -1)
    {
        return -1;
    }
    sleep(10);

    if(pid == 0 )
    {
        
        printf("Hello From Child.\n");


        
        execlp("ping", "ping","-c", "2", "google.com", NULL);
        printf("This line will not print.\n");
        exit(0);
    }

    printf("Hello From Parents.\n");

    sleep(1);
    waitpid(pid, NULL, 0);
    printf("Exiting From Program....\n\n");
    return 0;
}
