##
## EPITECH PROJECT, 2024
## gomoku
## File description:
## Makefile
##

SRC	=	main.cpp	\
		src/Core.cpp	\
		src/ManagerConnection.cpp	\
		src/Board.cpp	\
		src/Player.cpp	\
		src/Matrix.cpp	\
		src/MonteCarlo.cpp	\
		src/Thread/Promise.cpp	\
		src/Thread/ConditionVariable.cpp	\
		src/Thread/Mutex.cpp	\
		src/Thread/ScopeLock.cpp	\
		src/Thread/SafeQueue.cpp	\
		src/Thread/ThreadPool.cpp

# NAME	=	pbrain-player1.exe

OBJ	=	$(SRC:.cpp=.o)

CC	=	g++

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

CPPFLAGS	=	-Iinclude

all	:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o pbrain-gomoku-ai
	$(CC) $(CFLAGS) $(OBJ) -o pbrain-player1.exe
	$(CC) $(CFLAGS) $(OBJ) -o pbrain-player2.exe

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) pbrain-gomoku-ai
	$(RM) pbrain-player1.exe
	$(RM) pbrain-player2.exe
	$(RM) output*

re	:	fclean all

.PHONY	:	all clean fclean re