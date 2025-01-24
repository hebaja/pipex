CC=cc
CC_FLAGS= -Wall -Wextra -Werror
NAME=libpipex.a
INC_DIR=include
SRC_DIR=src
SRC_FILES=pipex.c compose_cmd.c pipex_utils.c cmd_utils.c fd_utils.c file_content_utils.c files_utils.c lst_cmd_utils.c
LIB_DIR=lib
LIBFT=$(LIB_DIR)/libft/libft.a
LIBFT_PRINTF=$(LIB_DIR)/ft_printf/libftprintf.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS=$(SRCS:.c=.o)

all: $(NAME) $(LIBFT) $(LIBFT_PRINTF)
	cc $(CC_FLAGS) -L. -lpipex -Llib/libft/ -lft -Llib/ft_printf/ -lftprintf -o pipex -g

$(LIBFT):
	make -C lib/libft/

$(LIBFT_PRINTF):
	make -C lib/ft_printf

$(NAME): $(OBJS) $(LIBFT) $(LIBFT_PRINTF)
	ar rcs $@ $(OBJS) $(LIBFT) $(LIBFT_PRINTF)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	make -C $(LIB_DIR)/libft clean
	make -C $(LIB_DIR)/ft_printf clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIB_DIR)/libft fclean
	make -C $(LIB_DIR)/ft_printf fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
