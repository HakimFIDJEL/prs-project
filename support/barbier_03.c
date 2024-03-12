#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define MAX_PLACE 3

pthread_t *clients;
pthread_t barbier_t;
sem_t salle_attente;
sem_t fauteil;
sem_t bonjour;
sem_t aurevoir;
int id_client = 0;
int nbr_client = 0;
int nbr_client_in = 0;

void *client(void *arg);
void *barbier(void *arg);

int main(void) 
{
    pthread_create(&barbier_t, NULL, barbier, NULL);
    
    clients = malloc(100 * sizeof(pthread_t));

    sem_init(&salle_attente, 0, MAX_PLACE);
    sem_init(&fauteil, 0, 0);
    sem_init(&bonjour, 0, 0);
    sem_init(&aurevoir, 0, 0);

    
    

    printf("Appuyez sur entrée pour créer un client\n");
    while(1)
    {   
        getchar();        
        pthread_create(&clients[nbr_client], NULL, client, (void *)(size_t)nbr_client);

        nbr_client++;
        nbr_client_in++;
    }

    // Attend que chaque thread termine
    for (int i = 0; i < MAX_PLACE; i++) 
    {
        pthread_join(clients[i], NULL);
    }


    free(clients);
    sem_destroy(&salle_attente);
    sem_destroy(&fauteil);
    sem_destroy(&bonjour);
    sem_destroy(&aurevoir);
    return 0; 
}

void *client(void *arg) {

    int id_client = (int)(size_t)arg;

        printf("--Un client attend--\n");

    sem_wait(&salle_attente);

        printf("Le client %d rentre et dit 'Bonjour Mr le barbier !'\n", id_client);

    if(nbr_client_in <= 1)
    {
        printf("Le barbier se réveille\n");
    }

    sem_post(&bonjour);
    sem_wait(&fauteil);

    printf("Le client %d est pris en charge\n", id_client);

    sem_wait(&aurevoir);
    sem_post(&salle_attente);

    printf("--Client %d part--\n\n", id_client);

    clients[id_client] = 0;
    nbr_client_in--;
    

    return NULL;
}


void *barbier(void *arg)
{
    while(1)
    {
        sem_wait(&bonjour);
        sem_post(&fauteil);
        sleep(3);
        sem_post(&aurevoir);
        printf("Le barbier dit 'Au revoir !'\n");

        if(nbr_client_in == 1)
        {
            printf("Le barbier dort\n");
            sleep(0.1);
            printf("\nAppuyez sur entrée pour créer un client\n");
            
        }

    }
}