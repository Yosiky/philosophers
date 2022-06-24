CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

NAME		= philo
SRC			=	\
				ee_atoi			\
				ee_strlen		\
				ee_putnbr		\
				ee_putstr		\
				main			\
				say_philosopher	\
				print_message	\
				mutex

OBJ_DIR		=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/,$(SRC:=.o))

HEADER_DIR	=	inc
HEADER		=	philo.h			\
				color.h

HEAD		=	$(addprefix $(HEADER_DIR)/,$(HEADER))

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
	$(CC) $(CFLAGS) -I$(HEADER_DIR)  $< -c -o $@

$(NAME): $(OBJ) $(HEAD)
	$(CC) -g $(OBJ) -lpthread -o $@

