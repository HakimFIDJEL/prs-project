#ifndef QUIZ_H
#define QUIZ_H

#define MAX_QUESTIONS 3
#define MAX_CHOICES 4
#define QUESTION_LEN 256
#define CHOICE_LEN 50

#define ANSWER_TIMER 15
#define QUESTION_TIMER 30

typedef struct {
    char question[QUESTION_LEN];
    char choices[MAX_CHOICES][CHOICE_LEN];
    char correctAnswer;
} Question;

void initQuestions(void);
void displayQuestion(int questionIndex);
int checkAnswer(int questionIndex, char userAnswer);



#endif
