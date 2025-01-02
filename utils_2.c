/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:18 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/02 13:14:15 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_error(char *msg)
{
	ft_printf(msg);
	exit(1);
}

void	do_pipe(int input_fd, int output_fd, char *cmd, char **env)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
		print_error("Error: (fork) no child process is created\n");
	if (cpid == 0)
	{
		if (dup2(input_fd, 0) == -1)
			print_error("Error: (dup2) input_fd\n");
		if (dup2(output_fd, 1) == -1)
			print_error("Error: (dup2) output_fd\n");
		execute_cmd(cmd, env);
	}
	else
	{
		close(input_fd);
		close(output_fd);
		waitpid(cpid, NULL, 0);
	}
}

int	open_file(char *file, int flag)
{
	int	fd;

	if (!flag)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_printf("no such file or directory: %s\n", file);
		exit(0);
	}
	return (fd);
}

void	cat_and_execute(char **av, char **env)
{
	int		input_fd;
	int		output_fd;
	int		pipefd[2];
	int		i;

	input_fd = open_file(av[1], 0);
	i = 2;
	while (av[i + 2])
	{
		if (pipe(pipefd) == -1)
			print_error("Error: (pipe)\n");
		do_pipe(input_fd, pipefd[1], av[i], env);
		close(pipefd[1]);
		input_fd = pipefd[0];
		i++;
	}
	unlink(av[i + 1]);
	output_fd = open_file(av[i + 1], 1);
	do_pipe(input_fd, output_fd, av[i], env);
	close_all(pipefd, input_fd, output_fd);
}
