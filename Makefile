DEBUG=no

CXX		= g++

# compiling flags here
CXXFLAGS	= -W -Wall -Wextra -Werror -std=c++11 -I./include/

# if debug is set to yes, add -g3 flag
ifeq ($(DEBUG),yes)
	CXXFLAGS += -g3
endif

# name of the projet
NAME   = nanotekspice
# name of the library
LIBNAME = libnanotekspice.a

# use
COUNT=1
NBSOURCES= $(shell find src/ -type f -name '*.cpp' | wc -l)

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = .

# Sources, Includes and Objects
SOURCES  := $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/Cli/*.cpp $(SRCDIR)/Gate/*.cpp $(SRCDIR)/Components/*.cpp $(SRCDIR)/Components/Special/*.cpp $(SRCDIR)/Factory/*.cpp $(SRCDIR)/Parser/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
RM       = rm -rf

$(BINDIR)/$(NAME):	$(OBJECTS)
			@$(CXX) -o $@ $(CXXFLAGS) $(OBJECTS)
			@echo "\033[94mProject $(NAME) build successfully!\033[0m"
			@ar rc $(LIBNAME) $(OBJECTS)
			@ranlib $(LIBNAME)
			@chmod 755 $(LIBNAME)
			@echo "\033[94mLibrary $(LIBNAME) created successfully!\033[0m"

$(OBJECTS):		$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
			@mkdir -p $(dir $@)
			@$(CXX) $(CXXFLAGS) -c $< -o $@
			@echo "[\033[95m$(COUNT)\033[0m/\033[93m$(NBSOURCES)\033[0m][\033[92m$<\033[0m]"
			@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

.PHONY: 		clean

clean:
			@$(RM) $(OBJDIR)
			@echo "\033[93mCleanup complete!\033[0m"

.PHONY: 		fclean

fclean: 		clean
			@$(RM) $(BINDIR)/$(NAME) $(LIBNAME)
			@echo "\033[93mExecutable removed!\033[0m"

re:	fclean $(BINDIR)/$(NAME)
