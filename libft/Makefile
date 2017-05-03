NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I./includes

SRC_PATH = ./srcs/
SRC_NAME =	ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_lstadd.c \
			ft_lstat.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstprint.c \
			ft_lstpush_end.c \
			ft_lstsize.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_word_count.c \
			ft_realloc.c \
			get_next_line.c \
			ft_bubble_sort.c \
			ft_putnstr.c \
			ft_insertsort_int.c \
			ft_htoi.c \
			ft_wcslen.c \
			ft_putwchar.c \
			ft_putwchar_fd.c \
			ft_putwstr.c \
			ft_putwstr_fd.c \
			ft_putnwstr.c \
			ft_strsplitstr.c \
			ft_maxint.c
			
PRINTF_DIR = ./printf/
PRINTF_SRC_PATH = ./srcs/
PRINTF_SRC_NAME =	ft_printf.c \
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

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC_NAME:%.c=%.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ += $(addprefix $(OBJ_PATH)printf_obj/,$(PRINTF_SRC_NAME:%.c=%.o))

INC_PATH = ./includes/
PF_INC_PATH = $(PRINTF_DIR)/includes/
INC = -I $(INC_PATH) -I $(PF_INC_PATH)
# INC = $(addprefix -I,$(INC_PATH))

NOC=\033[0m
OKC=\033[94;1m
ERC=\033[31m
WAC=\033[33m

all: obj $(NAME)

obj:
	@mkdir -p $@
	@mkdir -p $@/printf_obj

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

obj/printf_obj/%.o: $(PRINTF_DIR)$(PRINTF_SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME): $(OBJ)
	@echo "$(OKC)\nLIBFT:\t\tCreating the library / \c"
	@ar -rc $(NAME) $?
	@echo "$(OKC)Generating the index$(NOC)"
	@ranlib $(NAME)
	@echo "$(OKC)LIBFT:\t\tLIBFT ready$(NOC)"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(WAC)LIBFT:\t\tRemoving OBJ path: ./includes/libft/obj/$(NOC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(WAC)LIBFT:\t\tRemoving Libft.a$(NOC)"

re: fclean all
.PHONY: clean fclean
