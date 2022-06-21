CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

NAME		= philo
SRC			=	\
				ee_atoi			\
				ee_strlen		\
				ee_putnbr		\
				ee_putstr		\
				main			\
				say_philosopher

OBJ_DIR		=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/,$(SRC:=.o))

HEADER		=	philo.h			\
				color.h

.PHONY: all clean fclean re 

all:	$(OBJ_DIR)
	$(MAKE) -j $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -rf $(NAME)

re:		fclean all 

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CC) $^ -I. -g -o $@

