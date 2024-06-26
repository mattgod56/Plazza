##
## EPITECH PROJECT, 2024
## Plazza
## File description:
## Makefile
##

CC =	g++

SRC =	$(addsuffix .cpp, 		\
			$(addprefix src/,	\
					Process		\
					MessageQueue\
					Kitchen		\
					Cook		\
					main		\
					Reception	\
				)				\
			)					\

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS	=	-iquote./include

CXXFLAGS	=	-Wall -Wextra

NAME	=	plazza

RM =	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

vg	: CXXFLAGS += -g3
vg	: $(NAME)

clean	:
	$(RM) $(OBJ)

fclean :	clean
	$(RM) $(NAME)

re   :	fclean all

.PHONY	: all vg clean fclean re
