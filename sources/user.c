#include "../lib/user.h"
#include <stdio.h>
#include <string.h>


User users[MAX_USERS];


// Gestion des utilisateurs
void initUsers()
{
    for(int i = 0; i < MAX_USERS; i++)
    {
        users[i].pid = -1;
        users[i].score = 0;
        users[i].lastAnswer = '\0';
        users[i].isConnected = 0;
    }
}

// Retourne l'index de l'utilisateur dont le pid est passé en argument
int getUserIndex(pid_t pid)
{
    for(int i = 0; i < MAX_USERS; i++)
    {
        if(users[i].pid == pid)
        {
            return i;
        }
    }
    return -1;
}

// Gère la connexion d'un utilisateur
void connectUser(pid_t pid)
{
    int index = getUserIndex(-1);
    if(index != -1)
    {
        printf("--Connexion du processus %ld--\n", (long)pid);
        users[index].pid = pid;
        users[index].isConnected = 1;
    }
}

// Gère la déconnexion d'un utilisateur
void disconnectUser(pid_t pid)
{
    int index = getUserIndex(pid);
    if(index != -1)
    {
        printf("--Déconnexion du processus %ld--\n", (long)pid);
        users[index].pid = -1;
        users[index].score = 0;
        users[index].lastAnswer = '\0';
        users[index].isConnected = 0;
    }
}

// Gère la réponse d'un utilisateur
void answerUser(pid_t pid, char answer)
{
    int index = getUserIndex(pid);
    if(index != -1)
    {
        users[index].lastAnswer = answer;
    }
}