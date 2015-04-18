##
## Makefile for monlongserpent in /home/buchse_a/Projects/
##
## Made by Antoine Buchser
## Login   <buchse_a@epitech.net>
##
## Started on  Fri Feb  6 11:34:26 2015 Antoine Buchser
## Last update Wed Feb 11 13:40:14 2015 Antoine Buchser
##

CC		  =  g++

NAME		  =  plazza

RM		  =  rm -f
MKDIR		  =  mkdir -p

SRCS_DIR	  =  src
SRCS		  =  main.cpp \
		     Mutex.cpp \
		     ScopedLock.cpp \
		     Thread.cpp \
		     NamedPipe.cpp \
		     Process.cpp \
		     CondVar.cpp \
		     ThreadPool.cpp \
		     StringHelper.cpp \
		     \
		     App.cpp \
		     APizza.cpp \
		     Cook.cpp \
		     Kitchen.cpp \
		     KitchenFactory.cpp \
		     Reception.cpp \
		     Clock.cpp \
		     \
		     Margarita.cpp

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCS_DIR	  =  inc
INCS		  =  Exception.hpp \
		     Mutex.hpp \
		     ScopedLock.hpp \
		     Thread.hpp \
		     NamedPipe.hpp \
	 	     ITask.hpp \
	 	     Process.hpp \
		     CondVar.hpp \
		     ThreadPool.hpp \
		     StringHelper.hpp \
		     \
		     App.hpp \
		     APizza.hpp \
		     Cook.hpp \
		     Kitchen.hpp \
		     KitchenFactory.hpp \
		     Reception.hpp \
		     Clock.hpp \
		     \
		     Margarita.hpp

DEPS		  =  $(patsubst %,$(INCS_DIR)/%,$(INCS))

CFLAGS		  += -I./inc -lpthread
CFLAGS		  += -std=c++11 -Wall -Wextra -W -Werror -fPIC

CFLAGS		  += -g


#######################
## COMPILATION RULES ##
#######################

all:		     $(NAME)

$(NAME):	     $(OBJS)
		     $(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o:     $(SRCS_DIR)/%.cpp $(DEPS)
		     @$(MKDIR) $(OBJS_DIR)
		     $(CC) $(CFLAGS) -c -o $@ $<


################
## MISC RULES ##
################

clean:
		     $(RM) -r $(OBJS_DIR)

fclean:		     clean
		     $(RM) $(NAME)

re:		     fclean all

.PHONY: re fclean clean all
