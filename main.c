// Prs project

// Objectif : Clone Kahoot

// On lance le processus père qui va gérer les questions et réponses
// Les étudiants peuvent faire trois choses : grâce à des signaux envoyés au processus père
// - Se connecter       
// - Répondre à une question
// - Quitter

// Le père crée des processus fils par questions, le processus fils affiche la question et attend les réponses des étudiants
// Le processus père a une variable qui stocke le nombre de connecté, il sait donc combien de réponses il doit attendre
// Le processus père a une structure de données qui stocke les pid des étudiants connectés et leur réponse, il sait donc qui a répondu et quoi
// Le processus père a un timer qui permet de limiter le temps de réponse


// TODO : 
// Utiliser les sémaphores pour gérer le nombre de places restantes dans le tableau des utilisateurs, le remplir lorsque la partie commence

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#include "./lib/quiz.h"
#include "./lib/user.h"

#define SIG_CONNEXION SIGUSR1
#define SIG_DECONNEXION SIGUSR2
#define SIG_REPONSE_A SIGINT
#define SIG_REPONSE_B SIGQUIT
#define SIG_REPONSE_C SIGHUP
#define SIG_REPONSE_D SIGTERM




struct itimerval timer;
int nbrUser = 0;

// Fonctions
void signal_handler(int sig, siginfo_t *siginfo, void *context);



int main(void)
{
    initUsers();
    initQuestions();

    struct sigaction act;
    act.sa_sigaction = &signal_handler;
    act.sa_flags = SA_SIGINFO;

    sigaction(SIG_CONNEXION, &act, NULL);
    sigaction(SIG_DECONNEXION, &act, NULL);
    sigaction(SIG_REPONSE_A, &act, NULL);
    sigaction(SIG_REPONSE_B, &act, NULL);
    sigaction(SIG_REPONSE_C, &act, NULL);
    sigaction(SIG_REPONSE_D, &act, NULL);
    sigaction(SIGALRM, &act, NULL);


    int pid = getpid();
    printf("/======= Bienvenue sur le serveur Kahoot =======/\n");
    printf("Processus ID : %d\n\n", pid);
    printf("Commandes disponibles : \n");
    printf("- Connexion : SIGUSR1\n");
    printf("- Déconnexion : SIGUSR2\n");
    printf("- Réponse A : SIGINT\n");
    printf("- Réponse B : SIGQUIT\n");
    printf("- Réponse C : SIGHUP\n");
    printf("- Réponse D : SIGTERM\n\n");
    printf("En attente de connexion...\n\n");

    while(1)
    {
        pause();
    }

    printf("Fermeture du processus\n");

    return 0;
}

void signal_handler(int sig, siginfo_t *siginfo, void *context) {
    
    // Gestion de la fermeture du processus
    if(siginfo->si_pid == 0 && sig != SIGALRM)
    {
        printf("\n\nFermeture du processus\n");
        exit(0);
    }

    // Gestion des signaux
    if(sig == SIG_CONNEXION)
    {
        if(nbrUser <= MAX_USERS)
        {
            connectUser(siginfo->si_pid);
            nbrUser++;

            printf("%d Utilisateur(s) connecté(s)\n", nbrUser);

            // On lance le timer de notre partie
            if(nbrUser == 1)
            {
                

                timer.it_value.tv_sec = CONNECTION_TIMER;
                timer.it_value.tv_usec = 0;

                timer.it_interval.tv_sec = 0;
                timer.it_interval.tv_usec = 0;

                setitimer(ITIMER_REAL, &timer, NULL);

                printf("\n\n/== La partie commence dans %d secondes ==/\n\n", CONNECTION_TIMER);
                

                
            }
        }  
    }
    else if (sig == SIG_DECONNEXION)
    {
        disconnectUser(siginfo->si_pid);
        nbrUser--;
    }
    else 
    {
        switch(sig) 
        {
            case SIG_REPONSE_A:
                answerUser(siginfo->si_pid, 'A');
                printf("Réponse A\n");
                
            break;
            case SIG_REPONSE_B:
                answerUser(siginfo->si_pid, 'B');
                printf("Réponse B\n");
            break;
            case SIG_REPONSE_C:
                answerUser(siginfo->si_pid, 'C');
                printf("Réponse C\n");
            break;
            case SIG_REPONSE_D:
                answerUser(siginfo->si_pid, 'D');
                printf("Réponse D\n");
            break;
            case SIGALRM : 
                Kahoot(nbrUser);
            break;
            default: 
                printf("Signal inconnu envoyé par le processus %ld\n", (long)siginfo->si_pid);
            break;
        }
    }
}


