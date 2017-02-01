##
## Makefile for Lib Creation in /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/lib/
##
## Made by Marwane Khsime
## Login   <marwane.khsime@epitech.eu@epitech.eu>
##
## Started on  Wed Feb  1 03:59:07 2017 Marwane Khsime
## Last update Wed Feb  1 06:32:10 2017 Marwane Khsime
##

CPPFLAGS			+= -c -W -Wall -Werror -std=c++11
LIBNAME				= -L./../libnanotekspice.a -l./../libnanotekspice.a

CPP						= g++

RM						= rm -rf

SRCTESTDIR		= ./src/

SRC						= $(SRCTESTDIR)main.cpp

OBJS					=	$(SRC:.cpp=.o)

NAME 					= nanotekspice_test

$(NAME):			$(OBJS)
							make -C ./../
							$(CPP) $(OBJS) -o $(NAME) $(LDFLAGS)

all:					$(NAME)

clean:
							make clean -C ./../
							$(RM) $(OBJS)

fclean: 			clean
							make fclean -C ./../
							$(RM) $(NAME)

re: 					fclean all

.PHONY:				all clean fclean re
