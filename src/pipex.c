#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	int	**fd;
	char	*file_content;
	t_cmd	*lst_cmd;
	int	out_fd;
	int	i;

	i = 1;
	lst_cmd = NULL;
	if (argc == 5)
	{
		fd = init_fd(3, 2);
		if (!init_pipes(fd, 3) || !init_files(argv[1], argv[4], &file_content, &out_fd))
		{
			clear_fd(fd, 3);
			exit(EXIT_FAILURE);
		}
		while (++i < 4)
			if (!compose_cmd(argv[i], &lst_cmd))
			{
				clear_fd(fd, 3);
				lst_cmd_clear(&lst_cmd);			
				free(file_content);
				exit(EXIT_FAILURE);
			}
				
		if (lst_cmd)
		{
			if (!exec_pipex(fd, &lst_cmd, file_content, out_fd))
			{
				// clear_fd(fd, 3);
				// lst_cmd_clear(&lst_cmd);	
				// free(file_content);
				// ft_printf("Could not execute command: %s", strerror(EIO));
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			clear_fd(fd, 3);
			lst_cmd_clear(&lst_cmd);			
			free(file_content);
			ft_printf("Could not execute command: %s", strerror(EIO));
			exit(EXIT_FAILURE);
		}
	}
	else
		ft_printf("Insufficient number of arguments");
	return (0);
}
