# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcheung <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/27 11:10:05 by kcheung           #+#    #+#              #
#    Updated: 2017/04/28 09:02:44 by kcheung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_db

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

#Libft Library
LIB_DIR = ./libft/
LIB_INC_DIR = ./libft/includes
LIB = $(LIB_DIR)/libft.a
LIB_LINK = -L $(LIB_DIR) -lft

SRC_DIR = ./srcs/
SRC_NAME = main2.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:%.c=%.o))

INC_DIR = ./includes/
INC = -I$(LIB_INC_DIR) -I$(INC_DIR)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: obj $(NAME) 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)*.h
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIB_LINK)
	@chmod 755 $@

$(LIB):
	@make -C $(LIB_DIR)

obj:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean
	@echo "Cleaning" [$(NAME)] "..." $(OK)
	@echo "Cleaning" [$(NAME_C)] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_C)
	@make -C $(LIB_DIR) fclean
	@echo "Delete" [$(NAME)] "..." $(OK)
	@echo "Delete" [$(NAME_C)] "..." $(OK)
re: fclean all

.PHONY: all, clean, fclean, re
