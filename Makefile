##
## Makefile for monlongserpent in /home/buchse_a/Projects/
##
## Made by Antoine Buchser
## Login   <buchse_a@epitech.net>
##
## Started on  Fri Feb  6 11:34:26 2015 Antoine Buchser
## Last update Mon Apr 20 15:18:23 2015 Thomas MORITZ
##

CXX		  =  g++

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
		     Margarita.cpp \
		     Regina.cpp \
		     Americana.cpp \
		     Fantasia.cpp \
		     \
		     Graphics.cpp \
		     QSFMLCanvas.cpp \
		     Canvas.cpp \
		     GUI.cpp

MOC_HEADERS	  =  GUI.hpp
MOC_SRCS	  =  $(MOC_HEADERS:.hpp=.moc.cpp)

OBJS_DIR	  =  obj
OBJS		  =  $(SRCS:%.cpp=$(OBJS_DIR)/%.o) $(MOC_SRCS:%.cpp=$(OBJS_DIR)/%.o)

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
		     Margarita.hpp \
		     Regina.hpp \
		     Americana.hpp \
		     Fantasia.hpp \
		     \
		     Graphics.hpp \
		     QSFMLCanvas.hpp \
		     Canvas.hpp \
		     GUI.hpp

DEPS		  =  $(patsubst %,$(INCS_DIR)/%,$(INCS))

CXXFLAGS	  += -I./inc -lpthread -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS	  += -I/usr/include/qt5/QtCore -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtWidgets -I/usr/include/qt5 -I/usr/include/qt5/*
CXXFLAGS	  += -lQt5Gui -lQt5Core -lQt5Widgets
CXXFLAGS	  += -std=c++11 -Wall -Wextra -W -Werror -fPIC

CXXFLAGS	  += -g

MOC_FLAGS	  =  -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
MOC_FLAGS	  += -I./inc -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore


#######################
## COMPILATION RULES ##
#######################

$(NAME):		$(OBJS)
			$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

all:			$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.cpp $(DEPS)
		        @$(MKDIR) $(OBJS_DIR)
			$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJS_DIR)/%.moc.cpp:	$(INCS_DIR)/%.hpp
			moc $(MOC_FLAGS) $< -o $@

################
## MISC RULES ##
################

clean:
		     $(RM) -r $(OBJS_DIR)

fclean:		     clean
		     $(RM) $(NAME)

re:		     fclean all

.PHONY: re fclean clean all
