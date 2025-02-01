CC=cc
CC_FLAGS= -Wall -Wextra -Werror
NAME=libpipex.a
INC_DIR=include
SRC_DIR=src
SRC_FILES=cmd_args_utils.c cmd_utils.c compose_cmd.c compose_cmd_utils.c fd_utils.c file_content_utils.c files_utils.c \
		lst_cmd_utils.c paths_utils.c pipex.c pipex_utils.c
BONUS_SRC_FILES=close_fds_utils_bonus.c cmd_args_utils_bonus.c cmd_utils_bonus.c compose_cmd_bonus.c compose_cmd_utils_bonus.c \
		fd_utils_bonus.c file_content_utils_bonus.c files_utils_bonus.c here_doc_utils_bonus.c lst_cmd_utils_bonus.c \
		paths_utils_bonus.c pipex_bonus.c pipex_utils_bonus.c
LIB_DIR=lib
LIBFT=$(LIB_DIR)/libft/libft.a
LIBFT_PRINTF=$(LIB_DIR)/ft_printf/libftprintf.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
BONUS_SRCS=$(addprefix $(SRC_DIR)/, $(BONUS_SRC_FILES))
OBJS=$(SRCS:.c=.o)
BONUS_OBJS=$(BONUS_SRCS:.c=.o)

all: $(NAME) $(LIBFT) $(LIBFT_PRINTF)
	cc $(CC_FLAGS) -L. -lpipex -Llib/libft/ -lft -Llib/ft_printf/ -lftprintf -o pipex

$(LIBFT):
	make -C lib/libft/

$(LIBFT_PRINTF):
	make -C lib/ft_printf

$(NAME): $(OBJS) $(LIBFT) $(LIBFT_PRINTF)
	ar rcs $@ $(OBJS) $(LIBFT) $(LIBFT_PRINTF)

bonus: clean_a $(BONUS_OBJS) $(LIBFT) $(LIBFT_PRINTF)
	ar rcs $(NAME) $(BONUS_OBJS) $(LIBFT) $(LIBFT_PRINTF)
	cc $(CC_FLAGS) -L. -lpipex -Llib/libft/ -lft -Llib/ft_printf/ -lftprintf -o pipex

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

_bonus.c_bonus.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

clean_a:
	rm -f $(NAME)

clean:
	make -C $(LIB_DIR)/libft clean
	make -C $(LIB_DIR)/ft_printf clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make -C $(LIB_DIR)/libft fclean
	make -C $(LIB_DIR)/ft_printf fclean
	rm -f $(NAME)
	rm -f pipex

re: fclean all

.PHONY: all clean fclean re
