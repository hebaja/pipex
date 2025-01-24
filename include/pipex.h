/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 01:56:58 by hebatist          #+#    #+#             */
/*   Updated: 2025/01/24 02:04:18 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "../lib/libft/include/libft.h"
# include "../lib/ft_printf/include/ft_printf.h"

typedef struct s_cmd
{
	int				pid;
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

size_t	get_file_len(const char *file_name);
size_t	cmd_len(char *cmd);
void	get_file_content(const char *file_name, char *str);
void	close_fds(int **fd, int all);
void	clear_fd(int **fd, int rows);
void	lst_cmd_clear(t_cmd **lst_cmd);
void	print_args(char **args);
void	clear_all(t_cmd *head, int **fd, char *file_content);
void	clean_paths(char **paths);
char	**build_empty_args(char *empty_str);
char	**build_paths(void);
int		is_empty(char *str);
int		compose_cmd(char *cmd, t_cmd **lst_cmd);
int		is_path(char *str);
int		command_pos(char *str);
int		**init_fd(int rows);
int		init_pipes(int **fd, int rows);
int		file_exists(char *file_name);
int		init_files(char *fname_in, char *fname_out, char **fcontent, int *fd);
int		write_to_outfile(int **fd, int out_fd, t_cmd **lst_cmd);
int		fetch_file_content(int **fd, char *file_content);
int		do_command(int **fd, t_cmd *lst_cmd, int count, char *file_content);
int		exec_pipex(int **fd, t_cmd **lst_cmd, char *file_content, int out_fd);

#endif
