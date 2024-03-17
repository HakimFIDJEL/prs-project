#include "../lib/quiz.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

Question quizQuestions[MAX_QUESTIONS];


// Initialisation des questions
void initQuestions(void) {
    // Question 1
    strcpy(quizQuestions[0].question, "Quelle est la capitale de la France ?");
    strcpy(quizQuestions[0].choices[0], "A) Marseille");
    strcpy(quizQuestions[0].choices[1], "B) Paris");
    strcpy(quizQuestions[0].choices[2], "C) Lyon");
    strcpy(quizQuestions[0].choices[3], "D) Toulouse");
    quizQuestions[0].correctAnswer = 'B';

    // Question 2
    strcpy(quizQuestions[1].question, "Qui a peint la Joconde ?");
    strcpy(quizQuestions[1].choices[0], "A) Vincent Van Gogh");
    strcpy(quizQuestions[1].choices[1], "B) Pablo Picasso");
    strcpy(quizQuestions[1].choices[2], "C) Leonardo da Vinci");
    strcpy(quizQuestions[1].choices[3], "D) Claude Monet");
    quizQuestions[1].correctAnswer = 'C';

    // Question 3
    strcpy(quizQuestions[2].question, "Quel est l'océan le plus grand du monde ?");
    strcpy(quizQuestions[2].choices[0], "A) Atlantique");
    strcpy(quizQuestions[2].choices[1], "B) Indien");
    strcpy(quizQuestions[2].choices[2], "C) Pacifique");
    strcpy(quizQuestions[2].choices[3], "D) Arctique");
    quizQuestions[2].correctAnswer = 'C';

    // // Question 4
    // strcpy(quizQuestions[3].question, "Quelle année a vu le premier homme marcher sur la lune ?");
    // strcpy(quizQuestions[3].choices[0], "A) 1965");
    // strcpy(quizQuestions[3].choices[1], "B) 1969");
    // strcpy(quizQuestions[3].choices[2], "C) 1972");
    // strcpy(quizQuestions[3].choices[3], "D) 1975");
    // quizQuestions[3].correctAnswer = 'B';

    // // Question 5
    // strcpy(quizQuestions[4].question, "Quel pays est connu comme le 'pays du soleil levant' ?");
    // strcpy(quizQuestions[4].choices[0], "A) Chine");
    // strcpy(quizQuestions[4].choices[1], "B) Japon");
    // strcpy(quizQuestions[4].choices[2], "C) Corée du Sud");
    // strcpy(quizQuestions[4].choices[3], "D) Inde");
    // quizQuestions[4].correctAnswer = 'B';

    // // Question 6
    // strcpy(quizQuestions[5].question, "Quel est le plus long fleuve du monde ?");
    // strcpy(quizQuestions[5].choices[0], "A) Nil");
    // strcpy(quizQuestions[5].choices[1], "B) Amazon");
    // strcpy(quizQuestions[5].choices[2], "C) Yangtsé");
    // strcpy(quizQuestions[5].choices[3], "D) Mississippi");
    // quizQuestions[5].correctAnswer = 'B';

    // // Question 7
    // strcpy(quizQuestions[6].question, "Dans quel pays se trouve la ville de Timbuktu ?");
    // strcpy(quizQuestions[6].choices[0], "A) Mali");
    // strcpy(quizQuestions[6].choices[1], "B) Maroc");
    // strcpy(quizQuestions[6].choices[2], "C) Égypte");
    // strcpy(quizQuestions[6].choices[3], "D) Inde");
    // quizQuestions[6].correctAnswer = 'A';

    // // Question 8
    // strcpy(quizQuestions[7].question, "Qui a écrit 'Romeo et Juliette' ?");
    // strcpy(quizQuestions[7].choices[0], "A) William Shakespeare");
    // strcpy(quizQuestions[7].choices[1], "B) Charles Dickens");
    // strcpy(quizQuestions[7].choices[2], "C) Jane Austen");
    // strcpy(quizQuestions[7].choices[3], "D) Victor Hugo");
    // quizQuestions[7].correctAnswer = 'A';

    // // Question 9
    // strcpy(quizQuestions[8].question, "Quel élément chimique a pour symbole 'O' ?");
    // strcpy(quizQuestions[8].choices[0], "A) Or");
    // strcpy(quizQuestions[8].choices[1], "B) Osmium");
    // strcpy(quizQuestions[8].choices[2], "C) Oxygène");
    // strcpy(quizQuestions[8].choices[3], "D) Oganesson");
    // quizQuestions[8].correctAnswer = 'C';

    // // Question 10
    // strcpy(quizQuestions[9].question, "Quel est le numéro atomique de l'hydrogène ?");
    // strcpy(quizQuestions[9].choices[0], "A) 1");
    // strcpy(quizQuestions[9].choices[1], "B) 8");
    // strcpy(quizQuestions[9].choices[2], "C) 7");
    // strcpy(quizQuestions[9].choices[3], "D) 3");
    // quizQuestions[9].correctAnswer = 'A';
}

void displayQuestion(int questionIndex) 
{
    // On est le processus fils, on affiche la question et on lance un timer

    printf("%s\n", quizQuestions[questionIndex].question);
    for(int i = 0; i < 4; i++)
    {
        printf("%s\n", quizQuestions[questionIndex].choices[i]);
    }

    // Si le père n'a pas terminé l'enfant (que tous les participants n'ont pas répondu à temps, on passe à la question d'après)
    
    sleep(QUESTION_TIMER);
    exit(0);
}

// Vérifie la réponse à une question, return 1 si la réponse est correcte, 0 sinon
int checkAnswer(int questionIndex, char userAnswer) 
{
    return quizQuestions[questionIndex].correctAnswer == userAnswer;
}