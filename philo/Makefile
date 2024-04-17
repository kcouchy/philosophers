# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 12:18:52 by kcouchma          #+#    #+#              #
#    Updated: 2024/04/17 12:17:15 by kcouchma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philo			\
		check_inputs	\
		inits			\
		utils			\
		monitor			\
		locks

SRC = $(addsuffix .c, $(SRCS))
OBJ = $(addsuffix .o, $(SRCS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread #-g -fsanitize=address

NAME = philo

all : $(NAME)

# -o Names the output file $(NAME) instead of a.out
$(NAME) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# -c suppress linking with ld(1) to produce a .o file for each source file
%.o : %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean
	make

.PHONY : all clean fclean re
