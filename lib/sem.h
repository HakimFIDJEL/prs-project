#ifndef SEM_H
#define SEM_H

#define MAX_USERS 10

void initUserSemaphores();
void lockUserSemaphore(int index);
void unlockUserSemaphores();
void destroyUserSemaphores();





#endif