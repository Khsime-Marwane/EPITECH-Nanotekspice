##
## Makefile for Lib Creation in /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/lib/
##
## Made by Marwane Khsime
## Login   <marwane.khsime@epitech.eu@epitech.eu>
##
## Started on  Wed Feb  1 03:59:07 2017 Marwane Khsime
## Last update Thu Feb  2 05:55:43 2017 Marwane
##

CPPFLAGS	+= -c -W -Wall -Werror -std=c++11
CPPFLAGS	+= -I./include/

RM			= rm -rf

SRCDIR		= ./src/

SRC			= $(SRCDIR)Parser.cpp

OBJS		= $(SRC:.cpp=.o)

NAME 		= libnanotekspice.a

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all

tests:
		./__tests__/./run.sh

.PHONY:		all clean fclean re
