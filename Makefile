# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 21:01:58 by ejafer            #+#    #+#              #
#   Updated: 2022/06/24 13:46:26 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

NAMES	=	main philosopher philo forks printstatus utils

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		= 	inc/

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(NAMES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(NAMES)))
D_FILES		=	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(NAMES)))

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -O3

MD			=	mkdir

all: ${NAME}

$(NAME): ${OBJ} Makefile
			$(CC) $(CFLAGS) $(OBJ) -o ${NAME}

$(OBJ_DIR):
			${MD} $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -I$(INC_DIR) -o $@ -MD

include $(wildcard $(D_FILES))

clean:
			rm -f ${OBJ} $(D_FILES)

fclean:	clean
			rm -f ${NAME}

re:	fclean all

.PHONY: re fclean clean bonus all