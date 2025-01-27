CC=cc
CC_FLAGS= -Wall -Wextra -Werror
NAME=libftprintf.a
INC_DIR=include
SRC_DIR=src
HEADER_FILE=ft_printf.h
SRC_FILES=ft_printf.c ft_putchar_len.c ft_putstr_len.c ft_strlen.c ft_putnbr_base_len.c ft_putptr_base_len.c print_type.c
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $@ $^

.c.o:
	$(CC) $(CC_FLAGS) -c $< -I $(INC_DIR) -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
