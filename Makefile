##
## Makefile for Lib Creation in /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/lib/
##
## Made by Marwane Khsime
## Login   <marwane.khsime@epitech.eu@epitech.eu>
##
## Started on  Wed Feb  1 03:59:07 2017 Marwane Khsime
## Last update Sat Feb 25 17:56:15 2017 Marwane
##

CPP				=	g++ -g3

CPPFLAGS		+=	-c -W -Wall -Wextra -Werror
CPPFLAGS		+=	-I./include/

RM				=	rm -rf

SRCDIR			=	./src

COMPONENTSDIR	=	$(SRCDIR)/Components
PARSERDIR		=	$(SRCDIR)/Parser
FACTORYDIR		=	$(SRCDIR)/Factory
GATEDIR			=	$(SRCDIR)/Gate
CLIDIR			=	$(SRCDIR)/Cli

SRC				=	$(SRCDIR)/main.cpp					\
					$(CLIDIR)/Cli.cpp					\
					$(COMPONENTSDIR)/AComponent.cpp		\
					$(COMPONENTSDIR)/C4001.cpp			\
					$(COMPONENTSDIR)/C4008.cpp			\
					$(COMPONENTSDIR)/C4069.cpp			\
					$(COMPONENTSDIR)/C4011.cpp			\
					$(COMPONENTSDIR)/C4030.cpp			\
					$(COMPONENTSDIR)/C4071.cpp			\
					$(COMPONENTSDIR)/C4081.cpp			\
					$(COMPONENTSDIR)/False.cpp			\
					$(COMPONENTSDIR)/Input.cpp			\
					$(COMPONENTSDIR)/Clock.cpp			\
					$(COMPONENTSDIR)/Output.cpp			\
					$(COMPONENTSDIR)/True.cpp			\
					$(FACTORYDIR)/Factory.cpp			\
					$(GATEDIR)/Gate.cpp					\
					$(PARSERDIR)/Parser.cpp				\
					$(PARSERDIR)/RegParse.cpp			\

OBJS			= 	$(SRC:.cpp=.o)

LIBNAME 		= 	libnanotekspice.a

PROJECTNAME		= 	nanotekspice

project: 			$(OBJS)
					$(CPP) $(OBJS) -o $(PROJECTNAME)
					ar rc $(LIBNAME) $(OBJS)
					ranlib $(LIBNAME)

all:				project

clean:
					$(RM) $(OBJS)

fclean: 			clean
					$(RM) $(LIBNAME) $(PROJECTNAME)

re:		 			fclean all

tests:
					./__tests__/./run.sh

.PHONY:				mall clean fclean re
