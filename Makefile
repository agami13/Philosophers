NAME = philo

SRC = srcs/parsing.c srcs/utils.c srcs/philo.c

OBG = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra

all	:	$(NAME)

$(NAME) : $(OBG)
		$(CC) $(CFLAGS) $(OBG) -o $(NAME)

%.o	 : %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBG)

fclean:
	rm -rf $(OBG) $(NAME)

re: fclean all

.PHONY: all clean fclean re