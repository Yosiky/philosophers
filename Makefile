COMPILER	=	gcc
CFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-g3
OPT			=	-o3

NAME		=	philo

DIR_SRC 	=	src
SRC			=	main.c

DIR_OBJ		=	obj
OBJ			=	$(addprefix $(DIR_OBJ)/,$(SRC:.c=.o))

.PHONY: all clean fclean re

$(DIR_OBJ):
	mkdir -p $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c Makefile
	$(COMPILER) $(CFLAGS) $(DEBUG) $< -c -o $@

$(NAME): $(OBJ) Makefile
	$(COMPILER) $(OBJ) -o $@

all: $(DIR_OBJ)
	$(MAKE) $(NAME)

clean: 
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all