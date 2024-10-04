#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define TMP_FILE "/tmp/fopi01_secure.lock"

struct flock lock;

void lockRoutine (int i){
    if (i == 1) {
        lock.l_type = F_WRLCK;
    } else {
        lock.l_type = F_RDLCK;
    }

    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

}
void checkInstance(int file){
    if (fcntl(file, F_SETLKW, &lock) == 0) {
        printf("Lock get!");
    } else {
        perror("Failed to get Lock");
        exit(EXIT_FAILURE);
    }
}

void releaseLock(int file){
    lock.l_type = F_UNLCK;
    if (fcntl(file, F_SETLKW, &lock) == -1) {
        perror("Lock return failed");
        exit(EXIT_FAILURE);
    }
    printf("Lock Released!");
}

int main (void) {
    int i;
    int file = open(TMP_FILE, O_CREAT | O_RDWR, 0666);
    if (file < 0) {
        perror("Lock File Failure");
        return EXIT_FAILURE;
    } 

    lock.l_type = F_WRLCK;
    if (fcntl(file, F_GETLK, &lock) == -1) {
        perror ("Lock information failure");
        close (file);
        return EXIT_FAILURE;
    }

    if (lock.l_type == F_UNLCK) {
        i = 1;
    }

    lockRoutine(i);


    printf("Press <RETURN> to get lock ");
    getchar();
    checkInstance(file);
    

    printf("\nPress <RETURN> to return lock ");
    getchar();
    releaseLock(file);
    
    close(file);
    return 0;
}
