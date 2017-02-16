##
## Makefile for Makefile in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_babel/src/Server
##
## Made by Thomas Billot
## Login   <mikaz3@epitech.net>
##
## Started on  Mon Oct 31 14:23:31 2016 Thomas Billot
## Last update Sun Nov 13 17:50:38 2016 Thomas Billot
##

CXX		= g++

RM		= rm -f

NAME		= babel


SRCS		= BabelServer.cpp		\
		  BoostCircularBuffer.cpp	\
		  BoostConnexionAcceptor.cpp	\
		  BoostSerializer.cpp		\
		  BoostSocket.cpp		\
		  Client.cpp			\
		  Main.cpp			\
		  SocketSelector.cpp		\
		  Message.cpp			\
		  CommandHandler.cpp		\

OBJS		= $(SRCS:.cpp=.o)

CXXFLAGS	= -W -Wall -Wextra -lboost_system
CXXFLAGS	+= -std=c++11 -g3

LDFLAGS		= -lboost_system -lboost_serialization -lboost_filesystem

all: $(NAME) $(NAME2)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
