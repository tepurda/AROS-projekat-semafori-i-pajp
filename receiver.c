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

    // Otvaranje named pajpa
    int pipe_fd = open(pipeName, O_RDONLY);
    if (pipe_fd == -1) {
        perror("Greska otvaranja pajpa (citanje)");
        exit(EXIT_FAILURE);
    }

    // Inicijalizacija semafora
    semSender = sem_open("/chat_sem_sender", O_CREAT, 0644, 1);
    semReceiver = sem_open("/chat_sem_receiver", O_CREAT, 0644, 1);
    if (semSender == SEM_FAILED || semReceiver == SEM_FAILED) {
        perror("Greska kod inicijalizacije semafora");
        exit(EXIT_FAILURE);
    }

    char message[MaxVelicinaPoruke];

    while (1) {
        
        sem_wait(semReceiver);

        // Citanje poruke iz pajpa, ssize_t - signed size type
        ssize_t procitaniBajtovi = read(pipe_fd, message, MaxVelicinaPoruke);
        if (procitaniBajtovi > 0) {
            printf("Primljena poruka: %s", message);
        }

        
        sem_post(semSender);
    }

    close(pipe_fd);
    sem_close(semSender);
    sem_close(semReceiver);
    return 0;
}
