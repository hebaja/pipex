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
// t_cmd   *compose_cmd(char *cmd);
int   compose_cmd(char *cmd, t_cmd **lst_cmd);
int     is_path(char *str);
size_t  cmd_len(char *cmd);
int     command_pos(char *str);
char    **build_empty_args(char *empty_str);
void    close_fds(int **fd, int all);
int     **init_fd(int rows, int cols);
int     init_pipes(int **fd, int rows);
void    clear_fd(int **fd, int rows);
int     file_exists(char *file_name);
int     init_files(char *filename_in, char *filename_out, char **file_content, int *out_fd);
int	write_to_outfile(int **fd, int out_fd);
int	fetch_file_content(int **fd, char *file_content);
void    lst_cmd_clear(t_cmd **lst_cmd);
void    print_args(char **args);
int     do_command(int **fd, t_cmd *lst_cmd, int count, char *file_content);
int    exec_pipex(int **fd, t_cmd **lst_cmd, char *file_content, int out_fd);

#endif
