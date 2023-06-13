NAME = philo

SRCS = philo.c parsing.c utils.c

OBJS = ${SRCS:.c=.o}

INCLUDE = -I ./include/

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g3

RM = rm -rf

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
			${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -lpthread -o ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
