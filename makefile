all : main

main :
	rm -f main
	gcc main.c sources/quiz.c sources/user.c -o main

clean :
	rm -f main