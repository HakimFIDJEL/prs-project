#include "../lib/quiz.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

Question quizQuestions[MAX_QUESTIONS];

// Lancement de la boucle de jeu pendant #MAX_QUESTIONS fois
void Kahoot(int nbrUser)
{
    for(int i = 0; i < MAX_QUESTIONS; i++)
    {
        displayQuestion(i);
        sleep(QUESTION_TIMER);
    }

    // TODO : Afficher le classement
}

// Initialisation des questions
void initQuestions(void) 
{
    strcpy(quizQuestions[0].question, "Quelle est la capitale de la France ?");
    strcpy(quizQuestions[0].choices[0], "A) Marseille");
    strcpy(quizQuestions[0].choices[1], "B) Paris");
    strcpy(quizQuestions[0].choices[2], "C) Lyon");
    strcpy(quizQuestions[0].choices[3], "D) Toulouse");
    quizQuestions[0].correctAnswer = 'B';

}

// Crée un processus fils et affiche la question, en même temps lance un timer, displayQuestion se termine lorsque le nombre de gens ayant répondu est atteint ou que le timer est terminé
void displayQuestion(int questionIndex) 
{
    

    


    
}

// Vérifie la réponse à une question, return 1 si la réponse est correcte, 0 sinon
int checkAnswer(int questionIndex, char userAnswer) 
{
    // TODO
}