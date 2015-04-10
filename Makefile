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
		     App.cpp \
		     Mutex.cpp

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCS_DIR	  =  inc
INCS		  =  Exception.hpp \
		     App.hpp \
		     Mutex.hpp

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
