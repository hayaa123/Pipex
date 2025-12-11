NAME = pipex
CC= cc
CFLAGS= -Wall -Werror -Wextra -I./libft -g3
LIB =pipex.a
BONUS_LIB= bounu_pipex.a
LIBFT_DIR= ./libft/
SRC = utils.c prepare.c error1.c error2.c clear.c utils2.c
BONUS_SRC = utils_bonus.c prepare_bonus.c error1_bonus.c error2_bonus.c clear_bonus.c utils2_bonus.c
LIBFT_SRC = \
$(LIBFT_DIR)ft_isalpha.c $(LIBFT_DIR)ft_isdigit.c $(LIBFT_DIR)ft_isalnum.c $(LIBFT_DIR)ft_isascii.c $(LIBFT_DIR)ft_isprint.c $(LIBFT_DIR)ft_strlen.c \
$(LIBFT_DIR)ft_memset.c $(LIBFT_DIR)ft_bzero.c $(LIBFT_DIR)ft_memcpy.c $(LIBFT_DIR)ft_memmove.c $(LIBFT_DIR)ft_toupper.c $(LIBFT_DIR)ft_tolower.c \
$(LIBFT_DIR)ft_strlcpy.c $(LIBFT_DIR)ft_strlcat.c $(LIBFT_DIR)ft_strchr.c $(LIBFT_DIR)ft_strrchr.c $(LIBFT_DIR)ft_strncmp.c $(LIBFT_DIR)ft_memchr.c \
$(LIBFT_DIR)ft_memcmp.c $(LIBFT_DIR)ft_strnstr.c $(LIBFT_DIR)ft_atoi.c $(LIBFT_DIR)ft_calloc.c $(LIBFT_DIR)ft_strdup.c $(LIBFT_DIR)ft_substr.c \
$(LIBFT_DIR)ft_strjoin.c $(LIBFT_DIR)ft_strtrim.c $(LIBFT_DIR)ft_split.c $(LIBFT_DIR)ft_itoa.c $(LIBFT_DIR)ft_strmapi.c $(LIBFT_DIR)ft_striteri.c \
$(LIBFT_DIR)ft_putchar_fd.c $(LIBFT_DIR)ft_putstr_fd.c $(LIBFT_DIR)ft_putendl_fd.c $(LIBFT_DIR)ft_putnbr_fd.c \
$(LIBFT_DIR)print_string.c $(LIBFT_DIR)print_pointer.c $(LIBFT_DIR)print_number.c $(LIBFT_DIR)print_unsigned.c $(LIBFT_DIR)print_hexa.c $(LIBFT_DIR)ft_printf.c

LIBFT_OBJ := $(LIBFT_SRC:.c=.o)
OBJ := $(SRC:.c=.o) 
BONUS_OBJ := $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) main.c
	$(CC) main.c $(CFLAGS) -L. $(LIB) -I./libft -o $(NAME)

bonus: .bonus_done

.bonus_done: $(BONUS_LIB) main_bonus.c
	$(CC) main_bonus.c $(CFLAGS) -L. $(BONUS_LIB) -I./libft -o $(NAME)
	touch .bonus_done

$(BONUS_LIB): $(BONUS_OBJ) $(LIBFT_OBJ)
	ar rcs $(BONUS_LIB) $(LIBFT_OBJ) $(BONUS_OBJ)

$(LIB): $(LIBFT_OBJ) $(OBJ)
	ar rcs $(LIB) $(LIBFT_OBJ) $(OBJ)

clean:
	rm -f $(LIBFT_OBJ) $(OBJ) $(LIB) $(BONUS_OBJ) $(BONUS_LIB)

fclean: clean
	rm -f $(NAME) .bonus_done

re: fclean all

.PHONY: clean fclean all re