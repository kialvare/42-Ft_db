# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcheung <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/14 13:19:11 by kcheung           #+#    #+#              #
#    Updated: 2017/04/07 10:45:50 by kcheung          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = ../libft/srcs/
SRC_NAME =	ft_printf.c \
			parseflags.c \
			handle_d.c \
			handle_o.c \
			handle_u.c \
			handle_x.c \
			handle_c.c \
			handle_wc.c \
			handle_s.c \
			handle_ws.c \
			handle_none.c \
			handle_p.c \
			setup_handlers.c \
			print_format_nbr.c \
			helper.c
SRCS = $(addprefix $(DIR),$(SRC_NAME))

LIBFT_FUNC =	memalloc \
			 	strchr \
				putnstr \
				isdigit \
				isalpha \
				putstr \
				putchar \
				itoa \
				strlen \
				putnstr \
				strnew \
				bzero \
				memset \
				wcslen \
				putnwstr \
				putwstr \
				putwchar \
				putwchar_fd \
				putchar_fd \
				tolower \
				maxint 

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:%.c=%.o))
OBJS += $(foreach func, $(LIBFT_FUNC),$(addprefix $(OBJ_DIR)libft_obj/,ft_$(func).o))

LIBFT_DIR = ./libft/
LIB = $(LIBFT_DIR)/libft.a

INC_DIR = ./includes/
INC = -I$(LIBFT_DIR)$(INC_DIR) -I$(INC_DIR) 

NOC=\033[0m
OKC=\033[94;1m
ERC=\033[31m

all: obj $(NAME)

obj:
	@mkdir -p $@
	@mkdir -p $@/libft_obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)*.h
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

obj/libft_obj/%.o: $(LIBFT_DIR)$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	
$(NAME): $(OBJS) $(LIB)
	@ar -rc $(NAME) $?
	@ranlib $(NAME)

$(LIB):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f  $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Cleaning" [$(NAME)] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Delete" [$(NAME)] "..." $(OK)

re: clean fclean all
