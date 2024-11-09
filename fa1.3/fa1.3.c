# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pjpt = getpid();
    char buffer[5];

    char message[] = "MAPUA";

    pid_t jpt = fork();

    if (pipe(fd) < 0) {
        perror("Pipe Failure");
        exit(EXIT_FAILURE);
    }

    if (jpt < 0) {
        perror("Fork Failure");
        exit(EXIT_FAILURE);
    }  else if (jpt == 0) {
        printf ("child PID: %d", getpid());
        close(fd[0]);
        write(fd[1], message, 5);
        close(fd[1]);
    } else {
        printf("parent PID: %d", getppid());
        wait(NULL)
        close(fd[1]);
        read(fd[0], buffer, 5);
        buffer[5]='\0';
        printf("Recieved message: %s\n", buffer);

        close(fd[0]);
    }
    return 0;
}