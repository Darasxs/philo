# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 13:48:26 by dpaluszk          #+#    #+#              #
#    Updated: 2024/11/25 17:28:23 by dpaluszk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c error_handling.c initialization.c handling_threads.c philo_actions.c \
	cleanup.c helper_functions.c

OBJECTS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -pthread -g

CC = cc

all: $(NAME)

%.o: %.c philosophers.h
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJECTS}
	${CC} ${FLAGS} -o ${NAME} ${OBJECTS}

clean:
	rm -rf ${OBJECTS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re