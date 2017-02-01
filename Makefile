##
## Makefile for Lib Creation in /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/lib/
##
## Made by Marwane Khsime
## Login   <marwane.khsime@epitech.eu@epitech.eu>
##
## Started on  Wed Feb  1 03:59:07 2017 Marwane Khsime
## Last update Wed Feb  1 04:58:16 2017 Marwane Khsime
##

CPPFLAGS	+= -c -W -Wall -Werror -std=c++11
CPPFLAGS	+= -I./include/

RM				= rm -rf

SRCDIR		= ./src/

SRC				= $(SRCDIR)C4001

OBJS			=	$(SRC:.cpp=.o)

NAME 			= libnanotekspice.a

$(NAME):	$(OBJS)
					ar rc $(NAME) $(OBJS)
					ranlib $(NAME)

all:	$(NAME)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
