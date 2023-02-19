NAME = ca
CC = gcc

$(NAME) : $(NAME).c
	$(CC) $(NAME).c -o $(NAME)

run: $(NAME)
	./ca  200 200 1 0.3 0.001 > out.txt