#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "../lib/libft/include/libft.h"
# include "../lib/ft_printf/include/ft_printf.h"

typedef	struct s_cmd
{
	char	*cmd;
	char	**args;
	struct s_cmd	*next;
}	t_cmd;

size_t	get_file_len(const char *file_name);
void	get_file_content(const char *file_name, char *str);
int     is_empty(char *str);
t_cmd   *compose_cmd(char *cmd);
int     is_path(char *str);
size_t  cmd_len(char *cmd);
int     command_pos(char *str);
char    **build_empty_args(char *empty_str);

#endif
