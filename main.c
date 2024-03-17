#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>

#include "./lib/quiz.h"
#include "./lib/user.h"
#include "./lib/sem.h"

#define SIG_CONNEXION SIGUSR1
#define SIG_DECONNEXION SIGUSR2
#define SIG_REPONSE_A SIGINT
#define SIG_REPONSE_B SIGQUIT
#define SIG_REPONSE_C SIGHUP
#define SIG_REPONSE_D SIGTERM



struct itimerval timer;
int nbrUser   = 0;
int nbrAnswer = 0;
int currentQuestion = 0;
bool answered = false;
char answer;


// Fonctions
void signal_handler(int sig, siginfo_t *siginfo, void *context);
void Kahoot(int nbrUser);

int main(void)
{
    initUsers();
    initQuestions();
    initUserSemaphores();
    initGameSemaphore();

    // Gestion des signaux
    struct sigaction act;
    memset(&act, 0, sizeof(act));
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
    printf("\n\n/======= Bienvenue sur le serveur Kahoot =======/\n");
    printf("Processus ID : %d [pour les signaux]\n\n", pid);
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

    return 0;
}

void signal_handler(int sig, siginfo_t *siginfo, void *context) {
    
    // Gestion de la fermeture du processus
    if(siginfo->si_pid == 0 && sig != SIGALRM)
    {
        printf("\n\n/======= Fermeture du serveur Kahoot =======/\n\n");

        destroyUserSemaphores();
        destroyGameSemaphore();
        exit(0);
    }

    // Gestion des signaux
    if(sig == SIG_CONNEXION)
    {
        if(nbrUser <= MAX_USERS)
        {
            lockGameSemaphore();

            connectUser(siginfo->si_pid);
            nbrUser++;

            unlockGameSemaphore();

            printf("%d Utilisateur(s) connecté(s)\n", nbrUser);

            if(nbrUser == 1)
            {
                timer.it_value.tv_sec = CONNECTION_TIMER;
                timer.it_value.tv_usec = 0;

                timer.it_interval.tv_sec = 0;
                timer.it_interval.tv_usec = 0;

                printf("\n\n/== La partie commence dans %d secondes ==/\n\n", CONNECTION_TIMER);
                
                setitimer(ITIMER_REAL, &timer, NULL);
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

                answered = true;
                answer = 'A';

                
            break;
            case SIG_REPONSE_B:
                
                answered = true;
                answer = 'B';

            break;
            case SIG_REPONSE_C:
                
                answered = true;
                answer = 'C';

            break;
            case SIG_REPONSE_D:
                
                answered = true;
                answer = 'D';

            break;
            case SIGALRM : 
                Kahoot(nbrUser);
            break;
            default: 
                printf("Signal inconnu envoyé par le processus %ld\n", (long)siginfo->si_pid);
            break;
        }

        if(answer)
        {
            answered = false;

            if(hasAnswered(siginfo->si_pid))
            {
                printf("Le processus %ld a déjà répondu\n", (long)siginfo->si_pid);
            }
            else 
            {
                
                // On bloque le sémaphore de l'utilisateur pour rajouter une protection de données
                lockUserSemaphore(getUserIndex(siginfo->si_pid));

                Answered(siginfo->si_pid);

                printf("Le processus %ld a répondu la réponse %c\n", (long)siginfo->si_pid, answer);

                // On définit sa réponse
                answerUser(siginfo->si_pid, answer);

                // On vérifie si la réponse est correcte
                if(checkAnswer(currentQuestion, answer))
                {addPoint(siginfo->si_pid);}

                // On incrémente le nombre de réponses
                nbrAnswer++;
            }

        }
        
        
    }
}


void Kahoot(int nbrUser)
{
    lockGameSemaphore();

    printf("\n\n/== La partie commence ==/\n\n");

    for(int i = 0; i < MAX_QUESTIONS; i++)
    {
        printf("/== Question %d ==/\n", i+1);
        nbrAnswer = 0;
        
        // Si on est le fils on affiche la question
        pid_t pid = fork();
        if(pid == 0)
        {
            displayQuestion(i);
            exit(0);
        }
        else
        {
            // Si on est le père, on attend soit la fin du timer du fils, soit que tous les utilisateurs aient répondu
            int status;
            do
            {
                waitpid(pid, &status, 0);
                sleep(1);
            } while((!WIFEXITED(status) || WIFSIGNALED(status)) && nbrAnswer < nbrUser);

            if(nbrAnswer < nbrUser)
            {
                printf("\n\n/== Temps écoulé ==/\n\n");
            }

            kill(pid, SIGKILL);
        }

        printf("\n /== %d utilisateurs ont répondu à la question ==/\n", nbrAnswer);

        displayScores();
        unlockUserSemaphores();
        resetHasAnswered();

        currentQuestion++;
    }

    unlockGameSemaphore();
    printf("\n\n/== La partie est terminée ==/\n\n");

    printf("\n\n/== Scores finaux ==/\n\n");
    displayScores();
}
