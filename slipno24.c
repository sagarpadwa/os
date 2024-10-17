/*
Q.1 Write a C program to demonstrate the use of semaphores in process synchronization. 
Create two processes, one of which increments a shared variable while the other decrements it. 
Use semaphores to synchronize access to the shared variable.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define N 10 // Number of iterations

int shared_var = 0;
sem_t semaphore;

void *increment(void *arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semaphore);
        shared_var++;
        printf("Incremented: %d\n", shared_var);
        sem_post(&semaphore);
        sleep(1); // Sleep to simulate work
    }
    return NULL;
}

void *decrement(void *arg) {
    for (int i = 0; i < N; i++) {
        sem_wait(&semaphore);
        shared_var--;
        printf("Decremented: %d\n", shared_var);
        sem_post(&semaphore);
        sleep(1); // Sleep to simulate work
    }
    return NULL;
}

int main() {
    pthread_t inc_thread, dec_thread;
    sem_init(&semaphore, 0, 1); // Initialize semaphore

    pthread_create(&inc_thread, NULL, increment, NULL);
    pthread_create(&dec_thread, NULL, decrement, NULL);

    pthread_join(inc_thread, NULL);
    pthread_join(dec_thread, NULL);

    sem_destroy(&semaphore); // Cleanup semaphore
    return 0;
}



/*
Q.2 Write a C program to demonstrate the use of message queues in inter-process communication. 
Create a message queue and allow one process to send messages to another process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 512

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    key = ftok("progfile", 65); // Generate unique key
    msgid = msgget(key, 0666 | IPC_CREAT); // Create message queue

    if (fork() == 0) {
        // Child process
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from child!");
        msgsnd(msgid, &message, sizeof(message), 0); // Send message
        printf("Child sent: %s\n", message.msg_text);
    } else {
        // Parent process
        msgrcv(msgid, &message, sizeof(message), 1, 0); // Receive message
        printf("Parent received: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL); // Destroy message queue
    }

    return 0;
}
