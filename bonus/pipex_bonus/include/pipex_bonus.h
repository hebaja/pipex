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

typedef struct s_fds
{
	int	**cmd_fd;
	int	cmd_fd_rows;
	int	out_fd;
}	t_fds;

size_t	get_file_len(const char *file_name);
size_t	cmd_len(char *cmd);
size_t	get_cmd_quant(char **argv);
t_fds	*init_t_fds(int rows, char *out_filename);
void	init_pipex(char *filename, char **argv, char **path);
void	close_init_fds(t_fds *fds, int size);
void	close_unused_fds(t_fds *fds, int count);
void	clear_fds(t_fds *fds);
void	lst_cmd_clear(t_cmd **lst_cmd);
void	print_args(char **args);
void	clear_all(t_cmd *head, t_fds *fds, char *file_content);
void	clean_path(char **paths);
void	init_here_doc(char **argv, char **path);
void	clear_fds(t_fds *fds);
void    close_init_fds(t_fds *fds, int size);
void    close_unused_fds(t_fds *fds, int count);
char	*get_file_content(const char *file_name);
char	**build_empty_args(char *empty_str);
char    *remove_quotes(const char *str);
char    *catch_option(char *str);
char	**fetch_path(char **envp);
char	*init_infile_content(char *in_filename);
int		is_empty(char *str);
int		compose_cmd(char *cmd, t_cmd **lst_cmd, char **path);
int		is_path(char *str);
int		command_pos(char *str);
int		init_pipes(t_fds *fds);
int		file_exists(char *file_name);
int		write_to_outfile(t_fds *fds, t_cmd **lst_cmd, int cmd_quant);
int		fetch_file_content(int **fd, char *file_content);
int		exec_pipex(t_fds *fds, t_cmd **lst_cmd, char *file_content, int cmd_quant);
t_cmd   *fill_non_empty_cmd(char *built_cmd, char *cmd);
t_cmd   *fill_empty_cmd(char *cmd);
t_cmd	*lst_cmd_last(t_cmd *head);
t_cmd	*build_lst_cmd(char **argv, t_fds *fds, char *file_content, char **path);

#endif
