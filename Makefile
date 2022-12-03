COMPILER	=	gcc
CFLAGS		=	#-Wall -Wextra -Werror
DEBUG		=	-g3
OPT			=	-o3

LIBRARY		=	-lc

NAME		=	philo

DIR_INC		=	inc
HEADERS		=	philo.h
CHEADER		=	$(addprefix -I,$(DIR_INC))
LIST_HEADER	=	$(addprefix $(DIR_INC)/,$(HEADERS))

DIR_SRC 	=	src
SRC			=	main.c					\
				ee_atoi.c				\
				ee_error.c				\
				philo_func.c

DIR_OBJ		=	obj
OBJ			=	$(addprefix $(DIR_OBJ)/,$(SRC:.c=.o))

all: $(DIR_OBJ) $(NAME)

clean: 
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(DIR_OBJ):
	mkdir -p $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(LIST_HEADER) Makefile
	$(COMPILER) $(CFLAGS) $(DEBUG) $(CHEADER) $< -c -o $@

$(NAME): $(OBJ) $(LIST_HEADER) Makefile
	$(COMPILER) $(OBJ) $(LIBRARY) -o $@


.PHONY: all clean fclean re