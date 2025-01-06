CC=cc
CC_FLAGS= -Wall -Wextra -Werror
NAME=pipex.a
INC_DIR=include
SRC_DIR=src
LIBFT_DIR=libft
SRC_FILES=pipex.c
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

all: $(NAME)
	make -C $(LIBFT_DIR)
	cc $(CC_FLAGS) src/pipex.c pipex.a $(LIBFT_DIR)/libft.a $(LIBFT_DIR)/src/ft_printf/libftprintf.a -o pipex -g

$(NAME): $(OBJS)
	ar rcs $@ $^

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
