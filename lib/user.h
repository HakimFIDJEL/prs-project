#ifndef USER_H
#define USER_H

#define MAX_USERS 10
#define CONNECTION_TIMER 30

#include <sys/types.h>

// Structure de données
typedef struct {
    pid_t pid;
    int score;
    char lastAnswer;
    int isConnected;
    int hasAnswered;
} User;

void initUsers();
int getUserIndex(pid_t pid);
void connectUser(pid_t pid);
void disconnectUser(pid_t pid);
void answerUser(pid_t pid, char answer);
void displayScores();
void addPoint(pid_t pid);
void Answered(pid_t pid);
int hasAnswered(pid_t pid);
void resetHasAnswered();

#endif