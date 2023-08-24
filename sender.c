#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define MaxVelicinaPoruke 2000

int main() {
    const char *pipeName = "/tmp/chat_pipe";
    sem_t *semSender, *semReceiver;

    // Definisanje i inicijalizacija semafora
    semSender = sem_open("/chat_sem_sender", O_CREAT, 0644, 1);
    semReceiver = sem_open("/chat_sem_receiver", O_CREAT, 0644, 1);
    if (semSender == SEM_FAILED || semReceiver == SEM_FAILED) {
        perror("Greska kod inicijalizacije semafora");
        exit(EXIT_FAILURE);
    }

    // Kreiranje named pajpa (FIFO)
    mkfifo(pipeName, 0644);

    // Otvaranje pajpa
    int pipe_fd = open(pipeName, O_WRONLY);
    if (pipe_fd == -1) {
        perror("Greska kod otvaranja pajpa");
        exit(EXIT_FAILURE);
    }

    char message[MaxVelicinaPoruke];

    while (1) {
        // Input korisnika
        printf("Upisi poruku: ");
        fgets(message, MaxVelicinaPoruke, stdin);

        
        sem_wait(semSender);

        // Pise se poruka u pajp
        write(pipe_fd, message, strlen(message) + 1);

        
        sem_post(semReceiver);
    }

    close(pipe_fd);
    sem_close(semSender);
    sem_close(semReceiver);
    return 0;
}
