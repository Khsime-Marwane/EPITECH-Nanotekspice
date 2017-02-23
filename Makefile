##
## Makefile for Lib Creation in /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/lib/
##
## Made by Marwane Khsime
## Login   <marwane.khsime@epitech.eu@epitech.eu>
##
## Started on  Wed Feb  1 03:59:07 2017 Marwane Khsime
## Last update Thu Feb  2 05:55:43 2017 Marwane
##

CPP				= g++

CPPFLAGS		+= -c -W -Wall -Wextra -Werror -std=c++11
CPPFLAGS		+= -I./include/

RM				= rm -rf

SRCDIR			= ./src/

SRC				=	$(SRCDIR)AComponent.cpp \
					$(SRCDIR)C4001.cpp \
					$(SRCDIR)C4011.cpp \
					$(SRCDIR)C4030.cpp \
					$(SRCDIR)C4071.cpp \
					$(SRCDIR)C4081.cpp \
					$(SRCDIR)Cli.cpp \
					$(SRCDIR)Factory.cpp \
					$(SRCDIR)False.cpp \
					$(SRCDIR)Gate.cpp \
					$(SRCDIR)Input.cpp \
					$(SRCDIR)main.cpp \
					$(SRCDIR)Output.cpp \
					$(SRCDIR)Parser.cpp \
					$(SRCDIR)RegParse.cpp \
					$(SRCDIR)True.cpp

OBJS			= 	$(SRC:.cpp=.o)

LIBNAME 		= libnanotekspice.a

PROJECTNAME		= nanotekspice

project: 		$(OBJS)
				$(CPP) $(OBJS) -o $(PROJECTNAME)
				ar rc $(LIBNAME) $(OBJS)
				ranlib $(LIBNAME)

all:			project

clean:
				$(RM) $(OBJS)

fclean: 		clean
				$(RM) $(LIBNAME) $(PROJECTNAME)

re:		 		fclean all

tests:
				./__tests__/./run.sh

.PHONY:			all clean fclean re
