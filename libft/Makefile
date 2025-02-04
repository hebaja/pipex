CC=cc
CC_FLAGS= -Wall -Wextra -Werror
NAME=libft.a
INC_DIR=include
SRC_DIR=src
SRC_FILES=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_toupper.c \
		ft_tolower.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstiter.c ft_lstclear.c ft_lstmap.c get_next_line.c ft_printf.c  ft_putchar_len.c \
	       	ft_putnbr_base_len.c  ft_putptr_base_len.c  ft_putstr_len.c print_type.c
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $@ $^

.c.o: $(HEADER_FILE)
	$(CC) $(CC_FLAGS) -c $< -I $(INC_DIR) -o $@

all: $(NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
