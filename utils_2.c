/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:58:18 by oayyoub           #+#    #+#             */
/*   Updated: 2025/01/04 22:54:56 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	fork_and_execute(t_pipe_data *data, char *cmd, char **env)
{
	pid_t	cpid;
	int		status;

	cpid = fork();
	if (cpid == -1)
		print_error("Error: (fork) no child process is created", NULL);
	if (cpid == 0)
	{
		if (dup2(data->input_fd, 0) == -1)
			print_error("Error: (dup2) input_fd", NULL);
		if (dup2(data->output_fd, 1) == -1)
			print_error("Error: (dup2) output_fd", NULL);
		execute_cmd(cmd, env);
	}
	else
	{
		(1) && (close(data->input_fd), close(data->output_fd));
		waitpid(cpid, &status, 0);
		if (data->is_last)
		{
			if (WIFEXITED(status))
				exit(WEXITSTATUS(status));
			else
				exit(127);
		}
	}
}

int	open_file(char *file, int flag)
{
	int	fd;

	if (flag == 0)
	{
		if (access(file, F_OK) == -1)
			return (ft_printf("no such file or directory: %s\n", file), -1);
		if (access(file, R_OK) == -1)
			return (ft_printf("permission denied: %s\n", file), -1);
		fd = open(file, O_RDONLY);
	}
	else
	{
		if (access(file, F_OK) != -1)
		{
			if (access(file, W_OK) == -1)
				exit ((ft_printf("permission denied: %s\n", file), 1));
			fd = open(file, O_WRONLY | O_TRUNC);
		}
		else
			fd = open(file, O_WRONLY | O_CREAT, 0644);
	}
	if (fd == -1)
		print_error("error opening file: %s", file);
	return (fd);
}

void	cat_and_execute(char **av, char **env)
{
	t_pipe_data data;
    int pipefd[2];
    int dummy_pipefd[2];
    int i;

    data.input_fd = open_file(av[1], 0);
    if (data.input_fd == -1)
    {
        // Create a dummy pipe to simulate the input
        if (pipe(dummy_pipefd) == -1)
            print_error("Error: (pipe)", NULL);
        data.input_fd = dummy_pipefd[0];
        close(dummy_pipefd[1]);
    }
	data.is_last = 0;
	i = 2;
	while (av[i + 2])
	{
		if (pipe(pipefd) == -1)
			print_error("Error: (pipe)", NULL);
		data.output_fd = pipefd[1];
		if (data.input_fd != -1)
			fork_and_execute(&data, av[i], env);
		close(pipefd[1]);
		data.input_fd = pipefd[0];
		i++;
	}
	data.output_fd = open_file(av[i + 1], 1);
	data.is_last = 1;
	fork_and_execute(&data, av[i], env);
	close_all(pipefd, data.input_fd, data.output_fd);
}
