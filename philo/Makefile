NAME = philo

SRCS = philo.c parsing.c utils.c set_value.c routine.c free.c check_philo.c

OBJS = ${SRCS:.c=.o}

INCLUDE = -I ./include/

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g3
# CFLAGS = -Werror -Wextra -Wall -fsanitize=thread

RM = rm -rf

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS} Makefile ./include/philo.h
			${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -lpthread -o ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
