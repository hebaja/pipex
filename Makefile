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
LIBFT=libft/libft.a
SRCS=$(addprefix $(SRC_DIR)/, $(SRC_FILES))
BONUS_SRCS=$(addprefix $(SRC_DIR)/, $(BONUS_SRC_FILES))
OBJS=$(SRCS:.c=.o)
BONUS_OBJS=$(BONUS_SRCS:.c=.o)

all: $(NAME) $(LIBFT)
	cc $(CC_FLAGS) -L. -lpipex -Llibft/ -lft -o pipex

$(LIBFT):
	make -C libft/

$(NAME): $(OBJS) $(LIBFT)
	ar rcs $@ $(OBJS) $(LIBFT)

bonus: clean_a $(BONUS_OBJS) $(LIBFT)
	ar rcs $(NAME) $(BONUS_OBJS) $(LIBFT)
	cc $(CC_FLAGS) -L. -lpipex -Llibft/ -lft -o pipex

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

_bonus.c_bonus.o:
	$(CC) $(CC_FLAGS) -c $< -o $@

clean_a:
	rm -f $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -f pipex

re: fclean all

.PHONY: all clean fclean re
