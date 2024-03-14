#include "../lib/sem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAX_USERS 10

sem_t userSemaphores[MAX_USERS];


// Initialise les sémaphores
void initUserSemaphores() 
{
    for (int i = 0; i < MAX_USERS; i++) {
        sem_init(&userSemaphores[i], 0, 1);
    }
}

// Prend en argument l'index de l'utilisateur et bloque le sémaphore
void lockUserSemaphore(int index) 
{
    sem_wait(&userSemaphores[index]);
}

// Débloque le sémaphore de l'utilisateur
void unlockUserSemaphore(int index)
{
    sem_post(&userSemaphores[index]);
}

// Débloque toutes les sémaphores
void unlockUserSemaphores() 
{
    for (int i = 0; i < MAX_USERS; i++) {
        sem_post(&userSemaphores[i]);
    }
}

// Détruit toutes les sémaphores
void destroyUserSemaphores() 
{
    for (int i = 0; i < MAX_USERS; i++) {
        sem_destroy(&userSemaphores[i]);
    }
}
