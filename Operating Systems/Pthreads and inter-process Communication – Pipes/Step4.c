#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fds[2];
    pipe(fds);

    if (fork() == 0) {
        close(fds[0]);
        dup2(fds[1], 1);
        close(fds[1]);
        execlp("cat", "cat", "/etc/passwd", (char *)0);
        perror("execlp failed");
        exit(1);
    }
    else if (fork() == 0) {
        close(fds[1]);
        dup2(fds[0], 0);
        close(fds[0]);
        execlp("grep", "grep", "root", (char *)0);
        perror("execlp failed");
        exit(1);
    }
    else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }

    return 0;
}

